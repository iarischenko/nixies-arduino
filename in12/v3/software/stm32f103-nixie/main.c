#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>


#include "api.h"
#include "api-asm.h"

static void i2c_setup(void)
{
	rcc_periph_clock_enable(RCC_I2C1);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_AFIO);

    gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO0);
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
		      GPIO_I2C1_SCL | GPIO_I2C1_SDA);

	i2c_peripheral_disable(I2C1);
	i2c_set_clock_frequency(I2C1, 36);
	i2c_set_fast_mode(I2C1);
	i2c_set_ccr(I2C1, 0x1e);
	i2c_set_trise(I2C1, 0x0b);
	i2c_set_own_7bit_slave_address(I2C1, 0x32);
	i2c_peripheral_enable(I2C1);
}

/*
static void i2c_setup(void)
{
	rcc_periph_clock_enable(RCC_I2C1);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_set_i2c_clock_hsi(I2C1);

	rcc_periph_reset_pulse(RST_I2C1);
	// Setup GPIO pin GPIO_USART2_TX/GPIO9 on GPIO port A for transmit.
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6 | GPIO7);
	gpio_set_af(GPIOB, GPIO_AF4, GPIO6 | GPIO7);
	i2c_peripheral_disable(I2C1);
	//configure ANFOFF DNF[3:0] in CR1
	i2c_enable_analog_filter(I2C1);
	i2c_set_digital_filter(I2C1, 0);
	// HSI is at 8Mhz
	i2c_set_speed(I2C1, i2c_speed_fm_400k, 36);
	//configure No-Stretch CR1 (only relevant in slave mode)
	i2c_enable_stretching(I2C1);
	//addressing mode
	i2c_set_7bit_addr_mode(I2C1);
	i2c_peripheral_enable(I2C1);
}
*/
#define I2C_ACC_ADDR (0x22)
#define DEVICE_ID 0x01

int main(void) {
	uint8_t cmd = DEVICE_ID;
	uint8_t data;
    int i = 0;
/*
 $2 =
 {pll_mul = 7 '\a',
  pll_source = 1 '\001',
  hpre = 0 '\000',
  ppre1 = 4 '\004',
  ppre2 = 0 '\000',
  adcpre = 3 '\003',
  flash_waitstates = 2 '\002',
  prediv1 = 0 '\000',
  prediv1_source = 0 '\000',
  prediv2 = 0 '\000', pll2_mul = 0 '\000',
  pll3_mul = 0 '\000',
  usbpre = 0 '\000',
  ahb_frequency = 72000000,
  apb1_frequency = 36000000,
  apb2_frequency = 72000000
  }
  */


    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);


    i2c_setup();

    while (1) {
        for (i = 0; i < 0x800000; i++)
            __asm__("nop");
		i2c_transfer7(I2C1, I2C_ACC_ADDR, &cmd, 1, &data, 1);
    }

}
