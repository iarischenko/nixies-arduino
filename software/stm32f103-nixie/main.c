#include <stdlib.h>
#include <stdio.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/gpio.h>

#include <PD_UFP.h>
#include <PD_UFP_Protocol.h>

#include "api.h"
#include "api-asm.h"
#include "system.h"



/* Set up a timer to create 1mS ticks. */
static void systick_setup(void)
{
    /* 72MHz / 8 => 9000000 counts per second. */
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
    /* 9000000/9000 = 1000 overflows per second - every 1ms one interrupt */
    /* SysTick interrupt every N clock pulses: set reload to N-1 */
    systick_set_reload(8999);
    systick_interrupt_enable();
    /* Start counting. */
    systick_counter_enable();
}

uint32_t system_millis = 0;
/* Called when systick fires */
void sys_tick_handler(void);
void sys_tick_handler(void)
{
    system_millis++;
}

enum system_state *get_system_state(void)
{
    static enum system_state state = SHOW_CLOCK;
    return &state;
}

static struct tm *get_setup_tm(void)
{
    static struct tm date = { 0 };
    return &date;
}

void adjust_number(int i)
{
    struct tm *date = get_setup_tm();
    enum system_state *state = get_system_state();

    if ((*state) == SHOW_CLOCK)
    {
        return;
    }

    if ((*state) == SHOW_DIM_SEC)
    {
        if (i > 0 && date->tm_sec == 59)
        {
            date->tm_sec = 0;
        }
        else if (i < 0 && date->tm_sec == 0)
        {
            date->tm_sec = 59;
        }
        else
            date->tm_sec = date->tm_sec + i;
    }
    else if ((*state) == SHOW_DIM_MIN)
    {
        if (i > 0 && date->tm_min == 59)
        {
            date->tm_min = 0;
        }
        else if (i < 0 && date->tm_min == 0)
        {
            date->tm_min = 59;
        }
        else
            date->tm_min = date->tm_min + i;
    }
    else 
    {
        if (i > 0 && date->tm_hour == 23)
        {
            date->tm_hour = 0;
        }
        else if (i < 0 && date->tm_hour == 0)
        {
            date->tm_hour = 23;
        }
        else
            date->tm_hour = date->tm_hour + i;
    }
}

void step_to_next_state(void)
{
    enum system_state *state = get_system_state();
    struct tm *date = get_setup_tm();

    if (*state == SHOW_CLOCK)
    {
        get_system_time(date);
        *state = SHOW_DIM_SEC;
    }
    else if (*state >= SHOW_DIM_HOUR)
    {
        *state = SHOW_CLOCK;
        set_system_time(date);
    }
    else
    {
        enum system_state st = *state;
        st++;
        *state = st;
    }
}

#define CONVERT(a) a.tm_sec % 10, a.tm_sec / 10,\
                   a.tm_min % 10, a.tm_min / 10,\
                   a.tm_hour %10, a.tm_hour/ 10


#define CONVERTP(a) a->tm_sec % 10, a->tm_sec / 10,\
                   a->tm_min % 10, a->tm_min / 10,\
                   a->tm_hour %10, a->tm_hour/ 10


static void update_system_state(void )
{
    bool *is_time_updated = get_rtc_updated_flag();
    enum system_state *state = get_system_state();
    //int h_hour, l_hour, h_min, l_min, h_sec, l_sec;

    if (*is_time_updated && *state == SHOW_CLOCK)
    {
        struct tm date = { 0 };
        *is_time_updated = false;

        get_system_time(&date);

/*        h_hour = date.tm_hour / 10;
        l_hour = date.tm_hour % 10;
        h_min = date.tm_min / 10;
        l_min = date.tm_min % 10;
        h_sec = date.tm_sec / 10;
        l_sec = date.tm_sec % 10;
*/
        if (date.tm_sec == 0)
        {
            tubes_refresh();
        }
        set_tubes(CONVERT(date));
        //set_tubes(l_sec, h_sec, l_min,
        //          h_min, l_hour, h_hour);
    }
    else if (*state != SHOW_CLOCK)
    {
        struct tm *date = get_setup_tm();
        set_tubes(CONVERTP(date));
    }
}

int main(void) {
    int power_good = 0;
    int i = 0;
    struct usb_pd_pps context = {};
    volatile int wait = 0;

    /* debug wait for connection */
    while (wait)
    {
        for (i = 0; i < 0x8000; i++)
            __asm__("nop");
    }

    /* clock */
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
    /* millis */
    systick_setup();
    /* logs */
    usart1_setup();
    /* setup pec16 */
    setup_pec16();
    /* rtc sanity check */
    setup_rtc();
    /* */
    setup_tubes();

    /* max1771 enable : set to gdb */
    /* PA3 */
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO3);
    gpio_set(GPIOA, GPIO3);

    PD_init(&context, PD_POWER_OPTION_MAX_12V);
    //PD_init_PPS(&context, PPS_V(12.0), PPS_A(1), PD_POWER_OPTION_MAX_15V);

    while (1) {
        //PD_power_info_t p = { 0 };
        struct tm current_time = { 0 };
        bool *is_updated;
        PD_run(&context);
        static uint32_t prev_sec = 0;

        if (context.status_initialized)
        {   /* voltage must be 9V or higher */
            if (context.status_power == STATUS_POWER_TYP &&
                context.ready_voltage >=  9 * 20 /*(int )PD_V(9.0) */)
            {
                power_good  = 1;
            }
            else if (context.status_power == STATUS_POWER_PPS &&
                context.ready_voltage >= 9 * 50 /*(int )PPS_V(9.0) */)
            {
                power_good  = 1;
            }
            else
            {
                power_good = 0; 
            }
        }

        if (power_good)
        {
            gpio_clear(GPIOA, GPIO3);
        } else {
            gpio_set(GPIOA, GPIO3);
        }

        if (power_good)
        {
            update_system_state();
        }
        
/*
        if ((system_millis / 1000) > prev_sec )
        {
            static int i = 0;
            prev_sec = (system_millis / 1000);

            set_tubes(i, i, i, i, i, i);
            printf("set %d\n", i);

            i++;
            if (i > 9)
            {
                i = 0;
            }
        }
*/
        //uint8_t selected_power = PD_protocol_get_selected_power(&context.protocol);
        //PD_protocol_get_power_info(&context.protocol, selected_power, &p);        /* for (i = 0; i < 0x800000; i++) */
        /*    __asm__("nop"); */
    }

}
