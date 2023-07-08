#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/systick.h>

#include <PD_UFP.h>
#include <PD_UFP_Protocol.h>

#include "api.h"
#include "api-asm.h"


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

int main(void) {
    int i = 0;
    struct usb_pd_pps context = {};
    volatile int wait = 0;

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

    PD_init(&context, PD_POWER_OPTION_MAX_20V);
    //PD_init_PPS(&context, PPS_V(13.0), PPS_A(1), PD_POWER_OPTION_MAX_15V);

    while (1) {
        PD_run(&context);
        /* for (i = 0; i < 0x800000; i++) */
        /*    __asm__("nop"); */
    }

}
