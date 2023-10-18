#include <stdlib.h>
#include <stdio.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/gpio.h>

#include <PD_UFP.h>
#include <PD_UFP_Protocol.h>

#include "api.h"
#include "api-asm.h"

int power_good = 0;

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

extern void usart1_setup(void);
extern void setup_pec16(void);
extern void setup_rtc(void);
extern void setup_tubes(void);
extern void set_tubes(int digit1, int digit2, int digit3, int digit4, int digit5, int digit6);

int main(void) {
    int i = 0;
    struct usb_pd_pps context = {};
    volatile int wait = 0;

    /* debug */
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
        PD_run(&context);
        static uint32_t prev_sec = 0;

        if (context.status_initialized)
        {   /* voltage must be 12V or higher */
            if (context.status_power == STATUS_POWER_TYP &&
                context.ready_voltage >= 240)
            {
                power_good  = 1;
            }
            else if (context.status_power == STATUS_POWER_PPS &&
                context.ready_voltage >= 600)
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

        //uint8_t selected_power = PD_protocol_get_selected_power(&context.protocol);
        //PD_protocol_get_power_info(&context.protocol, selected_power, &p);        /* for (i = 0; i < 0x800000; i++) */
        /*    __asm__("nop"); */
    }

}
