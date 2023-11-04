#include "PD_UFP_Protocol.h"
#include <stdbool.h>
#include <stdlib.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "system.h"

#define TUBES_LINES 60
#define TUBES_COUNT 6

/* PB8 */
#define DATA_PIN  GPIO8
#define DATA_PORT GPIOB
/* PB9 */
#define STROBE_PIN  GPIO9
#define STROBE_PORT GPIOB
/* PA8 */
#define CLOCK_PIN GPIO15
#define CLOCK_PORT GPIOB


// array of int numbers for the poisoning prevention
int digits[TUBES_COUNT][10];

/* see schematic : the HV5812 drivers */
/* number in the array is calculated in the following way: */
/* base + (20 - hv5812_line) */
/* example: tube 6, 0 digit: 0  + (20 - 19) = 61 */

/*            0    1   2   3   4   5   6   7   8  9 */
int nixie6[]={56, 40, 41, 42, 43, 44, 45, 59, 58, 57};
int nixie5[]={49, 55, 54, 53, 52, 51, 50, 46, 47, 48};
int nixie4[]={36, 20, 21, 22, 23, 24, 25, 39, 38, 37};
int nixie3[]={29, 35, 34, 33, 32, 31, 30, 26, 27, 28};
int nixie2[]={16,  0,  1,  2,  3,  4,  5, 19, 18, 17};
int nixie1[]={ 9, 15, 14, 13, 12, 11, 10, 6,   7,  8};

bool nixie_tubes_array[TUBES_LINES];

extern uint32_t system_millis;
#define msleep mdelay
static void mdelay(uint32_t t)
{
    uint32_t wake = system_millis + (uint32_t)t;
    while (wake > system_millis);
}

void setup_tubes(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_set_mode(DATA_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_OPENDRAIN, DATA_PIN);
    gpio_set_mode(CLOCK_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_OPENDRAIN, CLOCK_PIN);
    gpio_set_mode(STROBE_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_OPENDRAIN, STROBE_PIN);

    gpio_clear(DATA_PORT, DATA_PIN);
    gpio_clear(CLOCK_PORT, CLOCK_PIN);
    gpio_clear(STROBE_PORT, STROBE_PIN);
}


#define wait  for (int __i = 0; __i < 0x20; __i++) __asm__("nop")
static void update_tubes(void)
{
    for (int i = 0; i < TUBES_LINES; i++)
    {
        if (nixie_tubes_array[i])
            gpio_set(DATA_PORT, DATA_PIN);
        else
            gpio_clear(DATA_PORT, DATA_PIN);

        //mdelay(1);
        wait;
        gpio_set(CLOCK_PORT, CLOCK_PIN);
        //mdelay(1);
        wait;
        gpio_clear(CLOCK_PORT, CLOCK_PIN);
    }
    gpio_clear(DATA_PORT, DATA_PIN);
    gpio_set(STROBE_PORT, STROBE_PIN);
    wait;
    //mdelay(1);
    gpio_clear(STROBE_PORT, STROBE_PIN);
}

void set_tubes(int digit1, int digit2, int digit3, int digit4, int digit5, int digit6)
{
    int i = 0;
    enum system_state *state = get_system_state();
    static int dim = false;

    digit1 = nixie1[digit1];
    digit2 = nixie2[digit2];
    digit3 = nixie3[digit3];
    digit4 = nixie4[digit4];
    digit5 = nixie5[digit5];
    digit6 = nixie6[digit6];


    for (i = 0; i < TUBES_LINES; i++)
    {
        nixie_tubes_array[i] = true;
    }

    if (*state == SHOW_CLOCK || !dim)
    {
        nixie_tubes_array[digit1] = 0;
        nixie_tubes_array[digit2] = 0;
        nixie_tubes_array[digit3] = 0;
        nixie_tubes_array[digit4] = 0;
        nixie_tubes_array[digit5] = 0;
        nixie_tubes_array[digit6] = 0;
    }
    else
    {

        if (*state == SHOW_DIM_SEC)
        {
            nixie_tubes_array[digit1] = 0;
            nixie_tubes_array[digit2] = 0;
        }
        else if (*state == SHOW_DIM_MIN)
        {
            nixie_tubes_array[digit3] = 0;
            nixie_tubes_array[digit4] = 0;
        }
        else if (*state == SHOW_DIM_HOUR)
        {
            nixie_tubes_array[digit5] = 0;
            nixie_tubes_array[digit6] = 0;

        }
    }

    dim = (dim > 3) ? 0 : dim + 1;
    update_tubes();
}

void tubes_refresh(void)
{
    int tubes[TUBES_COUNT][10];
    int count = 0;

    for (count = 0; count < TUBES_COUNT; count++)
    {
        for (int i = 0; i < 10; i++)
        {
            tubes[count][i] = i;
        }
    }

    for (count = 0; count < TUBES_COUNT; count++)
    {
        for (int i = 0; i < 5; i++)
        {
            int a = 0, b = 0, temp = 0;

            a = rand() % 10;
            b = rand() % 10;

            while (a == b)
            {
                a = rand() % 10;
            }

            temp = tubes[count][a];
            tubes[count][a] =  tubes[count][b];
            tubes[count][b] = temp;
        }
    }

    for (count = 0; count < 10; count++)
    {
        set_tubes(tubes[0][count],
                  tubes[1][count],
                  tubes[2][count],
                  tubes[3][count],
                  tubes[4][count],
                  tubes[5][count]);
        msleep(100);
    }
    msleep(100);


}

