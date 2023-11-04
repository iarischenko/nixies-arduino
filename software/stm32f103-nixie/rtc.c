#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rtc.h>

#include <stdio.h>

#include "libopencm3/stm32/f1/rtc.h"
#include "libopencm3/stm32/f1/bkp.h"
#include "system.h"

static uint32_t rtc_read_time_counter(void);

static bool *__get_rtc_context(void)
{
  static bool is_updated = false;
  return &is_updated;
}

bool *get_rtc_updated_flag(void)
{
  return __get_rtc_context();
}

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

  /* output PC13: 32K / 64 = 512 */
  BKP_RTCCR |= BKP_RTCCR_CCO;

  /* calibration value */ 
  /* https://www.st.com/resource/en/application_note/an2604-stm32f101xx-and-stm32f103xx-rtc-calibration-stmicroelectronics.pdf */

#ifndef RTC_CALIBRATION_VALUE
#error RTC_CALIBRATION_VALUE must be defined
#endif
  BKP_RTCCR |= (RTC_CALIBRATION_VALUE << BKP_RTCCR_CAL_LSB);
}

void get_system_time(struct tm *current_time)
{
  time_t count = 0;
  count = rtc_read_time_counter();
  /* printf("%s", ctime((const time_t *)&count)); */
  gmtime_r((const time_t *)&count, current_time);
}

void set_system_time(struct tm *new_time)
{
  time_t count = mktime(new_time);
  rtc_set_counter_val((uint32_t )count);
}

void rtc_isr(void)
{
  bool *is_updated = NULL;

  /* The interrupt flag isn't cleared by hardware, we have to do it. */
  rtc_clear_flag(RTC_SEC);

  is_updated = __get_rtc_context();
  *is_updated = true;
}

static uint32_t rtc_read_time_counter(void)
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

/*
void foo()
{
  rtc_set_counter_val(1);
}

#define RTC_LSB_MASK     ((uint32_t)0x0000FFFF)
static void rtc_set_counter(uint32_t counter)
{ 
  rtc_enter_config_mode();
  Set RTC COUNTER MSB word 
  RTC_CNTH = counter >> 16;
   Set RTC COUNTER LSB word 
  RTC_CNTL = counter & RTC_LSB_MASK;
  rtc_exit_config_mode();
}
*/
