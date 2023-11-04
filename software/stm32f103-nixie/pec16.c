/* based on exti_both.c example */

#include "libopencm3/stm32/f1/nvic.h"
#include <stdio.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/exti.h>
#include "system.h"

extern uint32_t system_millis;

#define PEC_A  PB11
#define PEC_B  PB10
#define PEC_SW PB5

#define A_PIN  11
#define B_PIN  10
#define SW_PIN 5

#define _CONCAT(x,y) x##y
#define CONCAT(x,y) _CONCAT(x,y)

#define A_GPIO CONCAT(GPIO, A_PIN)
#define B_GPIO CONCAT(GPIO, B_PIN)
#define SW_GPIO CONCAT(GPIO, SW_PIN)

#define PEC_PORT GPIOB

void setup_pec16(void)
{
  /* Enable AFIO clock. */
  rcc_periph_clock_enable(RCC_AFIO);
  /* Enable GPIOA clock. */
  rcc_periph_clock_enable(RCC_GPIOB);

  gpio_set_mode(PEC_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, SW_PIN);
  gpio_set_mode(PEC_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, A_PIN);
  gpio_set_mode(PEC_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, B_PIN);

  /* Enable EXTI0 interrupt. */
  nvic_enable_irq(NVIC_EXTI9_5_IRQ);
  nvic_enable_irq(NVIC_EXTI15_10_IRQ);

  /* Configure the EXTI subsystem. */
  exti_select_source(EXTI5, PEC_PORT);
  exti_select_source(EXTI10, PEC_PORT);
  exti_select_source(EXTI11, PEC_PORT);

  exti_set_trigger(EXTI5, EXTI_TRIGGER_BOTH);
  exti_set_trigger(EXTI10, EXTI_TRIGGER_BOTH);
  exti_set_trigger(EXTI11, EXTI_TRIGGER_BOTH);

  exti_enable_request(EXTI5);
  exti_enable_request(EXTI10);
  exti_enable_request(EXTI11);
}

static void set_count(int32_t state)
{
  static int32_t pos = 0;
  if (state == 4 || state == -4)
  {
    if (state == 4)
    {
      pos += 1;
      adjust_number(1);
    }
    else
    {
      pos -= 1;
      adjust_number(-1);
    }
    //pos = (state == 4) ? pos + 1 : pos - 1;
    printf("pos is %d\n", (int)pos);
  }
}
void exti9_5_isr(void)
{
  uint16_t sw = 0;

  exti_reset_request(EXTI_PR & (GPIO5));
  printf("SW\n");

  sw = gpio_get(PEC_PORT, SW_GPIO);

  if (sw)
  {
    step_to_next_state(); 
  }
}

#define PAUSE 5

void exti15_10_isr(void) {
  uint32_t __EXTI_PR = EXTI_PR;
  uint16_t pin_A = 0, pin_B = 0;
  static uint32_t last_turn = 0;
  static int32_t state = 0;

  exti_reset_request(__EXTI_PR & (GPIO10 | GPIO11));


  if ((system_millis - last_turn) < PAUSE)
  {
    // if time less then 'PAUSE' we should ignore the reading
  //  return;
  }
  pin_A = gpio_get(PEC_PORT, A_GPIO);
  pin_B = gpio_get(PEC_PORT, B_GPIO);


//  printf("%s -- 0x%x  pin_A 0x%x pin_B 0x%x state %d \n",
//         __func__, __EXTI_PR, pin_A, pin_B, state);
  if (__EXTI_PR & B_GPIO)
  {
    /* B */
    if ((state == 1 && !pin_A && !pin_B) ||
        (state == 3 && pin_A && pin_B))
    {
      state += 1;
      last_turn = system_millis;
    }

    if ((state == 0 && pin_A && !pin_B) ||
        (state == -2 && !pin_A && pin_B))
    {
      state -= 1;
      last_turn = system_millis;
    }
    set_count(state);
  }
  if(__EXTI_PR & A_GPIO)
  {
    /* A */
    if ((state == 0  && !pin_A &&  pin_B)
      || (state == 2  && pin_A && !pin_B))
    {
      state += 1; /* if condition is true then state ++ */
      last_turn = system_millis;
    }
    if ((state == -1 && !pin_A && !pin_B) ||
      (state == -3 && pin_A &&  pin_B))
    {
      state -= 1; /* if condition is true then state -- */
      last_turn = system_millis;
    }
    set_count(state);
  }

  if (pin_A && pin_B && state != 0)
  {
    state = 0;
  }
}


