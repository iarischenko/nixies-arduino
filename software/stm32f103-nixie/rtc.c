#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rtc.h>

#include <time.h>
#include <stdio.h>


static uint32_t rtc_read_time_couter(void);

void rtc_isr(void)
{
    time_t count = 0;

	/* The interrupt flag isn't cleared by hardware, we have to do it. */
	rtc_clear_flag(RTC_SEC);

    count = rtc_read_time_couter();
    printf("%s", ctime((const time_t *)&count));
}

void setup_rtc(void);
void setup_rtc(void)
{
	/*
	 * If the RTC is pre-configured just allow access, don't reconfigure.
	 * Otherwise enable it with the LSE as clock source and 0x7fff as
	 * prescale value.
	 */
	rtc_auto_awake(RCC_LSE, 0x7fff);

	/* Without this the RTC interrupt routine will never be called. */
    nvic_enable_irq(NVIC_RTC_IRQ);
    nvic_set_priority(NVIC_RTC_IRQ, 1);

	/* Enable the RTC interrupt to occur off the SEC flag. */
	rtc_interrupt_enable(RTC_SEC);

}

static uint32_t rtc_read_time_couter(void)
{
  uint16_t high1 = 0U, high2 = 0U, low = 0U;
  uint32_t timecounter = 0U;

  high1 = RTC_CNTH & 0xFFFFUL;
  low   = RTC_CNTL & 0xFFFFUL;
  high2 = RTC_CNTH & 0xFFFFUL;

  if (high1 != high2)
  {
    /* In this case the counter roll over during reading of CNTL and CNTH registers,
       read again CNTL register then return the counter value */
    timecounter = (((uint32_t) high2 << 16U) | (RTC_CNTL & 0xFFFFUL));
  }
  else
  {
    /* No counter roll over during reading of CNTL and CNTH registers, counter
       value is equal to first value of CNTL and CNTH */
    timecounter = (((uint32_t) high1 << 16U) | low);
  }

  return timecounter;
}

