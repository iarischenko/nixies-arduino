/**
 * PD_UFP.h
 *
 *  Updated on: Jan 28, 2021
 *      Author: Ryan Ma
 *  Updated on: July 1, 2023
 *      Author: Ivan Arishchenko
 *
 * Minimalist USB PD stm32 UNO R3 board
 * Only support UFP(device) sink only functionality
 * Requires FUSB302_UFP.h, PD_UFP_Protocol.h and libopencm3 library
 *
 * Support PD3.0 PPS
 *
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>

#include "PD_UFP.h"
#include "libopencm3/stm32/f1/rcc.h"

#define t_PD_POLLING            100
#define t_TypeCSinkWaitCap      350
/* combine t_SenderResponse and t_PSTransition */
#define t_RequestToPSReady      580
/* must less than 10000 (10s) */
#define t_PPSRequest            5000

#define PIN_OUTPUT_ENABLE       10
#define PIN_FUSB302_INT         0
#define PIN_FUSB302_PORT        GPIOB


extern uint32_t system_millis;

static void handle_FUSB302_event(struct usb_pd_pps *c, FUSB302_event_t events);
static bool PD_timer(struct usb_pd_pps *c);
static void set_default_power(struct usb_pd_pps *c);
static void status_power_ready(struct usb_pd_pps *c, status_power_t status,
        uint16_t voltage, uint16_t current);
static int status_log_readline_msg(struct usb_pd_pps *c, uint16_t msg_header,
        uint8_t status, uint32_t *obj);
static int status_log_readline_src_cap(struct usb_pd_pps *c);
static int status_log_event(struct usb_pd_pps *c, uint8_t status,
        uint32_t * obj);
static FUSB302_ret_t FUSB302_i2c_read(uint32_t i2c_bus, uint8_t dev_addr,
        uint8_t reg_addr, uint8_t *data, uint8_t count);
static FUSB302_ret_t FUSB302_i2c_write(uint32_t i2c_bus, uint8_t dev_addr,
        uint8_t reg_addr, uint8_t *data, uint8_t count);
static FUSB302_ret_t FUSB302_delay_ms(uint32_t t);


enum {
    STATUS_LOG_MSG_TX,
    STATUS_LOG_MSG_RX,
    STATUS_LOG_DEV,
    STATUS_LOG_CC,
    STATUS_LOG_SRC_CAP,
    STATUS_LOG_POWER_READY,
    STATUS_LOG_POWER_PPS_STARTUP,
    STATUS_LOG_POWER_REJECT,
    STATUS_LOG_LOAD_SW_ON,
    STATUS_LOG_LOAD_SW_OFF,
};

static void i2c_gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_I2C1);

//        RCC_APB1RSTR_I2C1RST
    //
        
        gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_OPENDRAIN,
                      GPIO6);
        gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_OPENDRAIN,
                      GPIO7);

	i2c_peripheral_enable(I2C1);

    /* hack: generate stop condition - recover from uncomplited transaction */
#define SCL GPIO6
#define SDA GPIO7
        while ((I2C_SR2(I2C1) & I2C_SR2_BUSY)) {
            gpio_set(GPIOB, SCL);
            gpio_set(GPIOB, SDA);
            FUSB302_delay_ms(1);
            gpio_clear(GPIOB, SCL);
            FUSB302_delay_ms(1);
            gpio_clear(GPIOB, SDA);
            FUSB302_delay_ms(1);
            gpio_set(GPIOB, SCL);
            FUSB302_delay_ms(1);
            gpio_set(GPIOB, SDA);
            FUSB302_delay_ms(1);
        }

	gpio_set_mode(PIN_FUSB302_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT,
            PIN_FUSB302_INT);
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
		      GPIO_I2C1_SCL | GPIO_I2C1_SDA);

	i2c_peripheral_disable(I2C1);
        rcc_periph_reset_pulse(RST_I2C1);
	i2c_set_clock_frequency(I2C1, 36);
	i2c_set_fast_mode(I2C1);
	i2c_set_ccr(I2C1, 0x1e);
	i2c_set_trise(I2C1, 0x0b);
        i2c_set_speed(I2C1, i2c_speed_sm_100k, 36); 
	//i2c_set_own_7bit_slave_address(I2C1, 0x32);
	i2c_set_own_7bit_slave_address(I2C1, 0x11);
	i2c_peripheral_enable(I2C1);


}


void PD_init(struct usb_pd_pps *c, enum PD_power_option_t power_option)
{
    memset(c, 0x0, sizeof(*c));
    c->status_power = STATUS_POWER_NA;
    c->status_log_level = PD_LOG_LEVEL_VERBOSE;
    PD_init_PPS(c, 0, 0, power_option);
    //PD_init_PPS(c, PPS_V(13.0), PPS_A(1), power_option);
}

void PD_init_PPS(struct usb_pd_pps *c, uint16_t PPS_voltage,
        uint8_t PPS_current, enum PD_power_option_t power_option)
{
    i2c_gpio_setup();
    /* Initialize FUSB302 */
    c->FUSB302.i2c_bus = I2C1;
    c->FUSB302.i2c_address = 0x22;
    c->FUSB302.i2c_read = FUSB302_i2c_read;
    c->FUSB302.i2c_write = FUSB302_i2c_write;
    c->FUSB302.delay_ms = FUSB302_delay_ms;

    FUSB302_tx_hard_reset(&c->FUSB302);

    if (FUSB302_init(&c->FUSB302) == FUSB302_SUCCESS
            && FUSB302_get_ID(&c->FUSB302, 0, 0) == FUSB302_SUCCESS) {
        c->status_initialized = 1;
    }

    /* Two stage startup for PPS Voltge < 5V */
    if (PPS_voltage && PPS_voltage < PPS_V(5.0)) {
        c->PPS_voltage_next = PPS_voltage;
        c->PPS_current_next = PPS_current;
        PPS_voltage = PPS_V(5.0);
    }

    /* Initialize PD protocol engine */
    PD_protocol_init(&c->protocol);
    PD_protocol_set_power_option(&c->protocol, power_option);
    PD_protocol_set_PPS(&c->protocol, PPS_voltage, PPS_current, false);

    status_log_event(c, STATUS_LOG_DEV, NULL);
}

void PD_run(struct usb_pd_pps *c)
{
    uint8_t i = 0;

    if (PD_timer(c) || (gpio_get(PIN_FUSB302_PORT, PIN_FUSB302_INT) == 0)) {
        FUSB302_event_t FUSB302_events = 0;
        for (i = 0; i < 3 &&
                FUSB302_alert(&c->FUSB302, &FUSB302_events) != FUSB302_SUCCESS; i++) {}
        if (FUSB302_events) {
            handle_FUSB302_event(c, FUSB302_events);
        }
    }
}

bool PD_set_PPS(struct usb_pd_pps *c, uint16_t PPS_voltage, uint8_t PPS_current)
{
    if (c->status_power == STATUS_POWER_PPS &&
            PD_protocol_set_PPS(&c->protocol, PPS_voltage, PPS_current, true)) {
        c->send_request = 1;
        return true;
    }
    return false;
}

void PD_set_power_option(struct usb_pd_pps *c,
        enum PD_power_option_t power_option)
{
    if (PD_protocol_set_power_option(&c->protocol, power_option)) {
        c->send_request = 1;
    }
}

static FUSB302_ret_t FUSB302_i2c_read(uint32_t i2c_bus, uint8_t dev_addr,
        uint8_t reg_addr, uint8_t *data, uint8_t count)
{
	i2c_transfer7(i2c_bus, dev_addr, &reg_addr, 1, data, count);
    return FUSB302_SUCCESS;
}

static FUSB302_ret_t FUSB302_i2c_write(uint32_t i2c_bus, uint8_t dev_addr,
        uint8_t reg_addr, uint8_t *data, uint8_t count)
{
#define WRITE_BUFFER_SIZE 64
    uint8_t buffer[WRITE_BUFFER_SIZE] = {};

    if (count + 1 > WRITE_BUFFER_SIZE)
        return FUSB302_ERR_WRITE_DEVICE;

    buffer[0] = reg_addr;
    memcpy(&buffer[1], data, count);

    i2c_transfer7(i2c_bus, dev_addr, buffer, count + 1, NULL, 0);
    return FUSB302_SUCCESS;
}

static FUSB302_ret_t FUSB302_delay_ms(uint32_t t)
{
    uint32_t wake = system_millis + (uint32_t)t;
    while (wake > system_millis);
    return FUSB302_SUCCESS;
}

void PD_handle_protocol_event(struct usb_pd_pps *c, PD_protocol_event_t events)
{
    if (events & PD_PROTOCOL_EVENT_SRC_CAP) {
        c->wait_src_cap = 0;
        c->get_src_cap_retry_count = 0;
        c->wait_ps_rdy = 1;
        c->time_wait_ps_rdy = system_millis;
        status_log_event(c, STATUS_LOG_SRC_CAP, NULL);
    }
    if (events & PD_PROTOCOL_EVENT_REJECT) {
        if (c->wait_ps_rdy) {
            c->wait_ps_rdy = 0;
            status_log_event(c, STATUS_LOG_POWER_REJECT, NULL);
        }
    }
    if (events & PD_PROTOCOL_EVENT_PS_RDY) {
        PD_power_info_t p = {};
        uint8_t i, selected_power =
            PD_protocol_get_selected_power(&c->protocol);

        PD_protocol_get_power_info(&c->protocol, selected_power, &p);
        c->wait_ps_rdy = 0;
        if (p.type == PD_PDO_TYPE_AUGMENTED_PDO) {
            /* PPS mode */
            FUSB302_set_vbus_sense(&c->FUSB302, 0);
            if (c->PPS_voltage_next) {
                /* Two stage startup for PPS voltage < 5V */
                PD_protocol_set_PPS(&c->protocol, c->PPS_voltage_next,
                        c->PPS_current_next, false);
                c->PPS_voltage_next = 0;
                c->send_request = 1;
                status_log_event(c, STATUS_LOG_POWER_PPS_STARTUP, NULL);
            } else {
                c->time_PPS_request = system_millis;
                status_power_ready(c, STATUS_POWER_PPS,
                    PD_protocol_get_PPS_voltage(&c->protocol),
                    PD_protocol_get_PPS_current(&c->protocol));
                status_log_event(c, STATUS_LOG_POWER_READY, NULL);
            }
        } else {
            FUSB302_set_vbus_sense(&c->FUSB302, 1);
            status_power_ready(c, STATUS_POWER_TYP, p.max_v, p.max_i);
            status_log_event(c, STATUS_LOG_POWER_READY, NULL);
        }
    }
}

static void handle_FUSB302_event(struct usb_pd_pps *c, FUSB302_event_t events)
{
    if (events & FUSB302_EVENT_DETACHED) {
        PD_protocol_reset(&c->protocol);
        return;
    }
    if (events & FUSB302_EVENT_ATTACHED) {
        uint8_t cc1 = 0, cc2 = 0, cc = 0;
        FUSB302_get_cc(&c->FUSB302, &cc1, &cc2);
        PD_protocol_reset(&c->protocol);
        if (cc1 && cc2 == 0) {
            cc = cc1;
        } else if (cc2 && cc1 == 0) {
            cc = cc2;
        }
        /* TODO: handle no cc detected error */
        if (cc > 1) {
            c->wait_src_cap = 1;
        } else {
            set_default_power(c);
        }
        status_log_event(c, STATUS_LOG_CC, NULL);
    }
    if (events & FUSB302_EVENT_RX_SOP) {
        PD_protocol_event_t protocol_event = 0;
        uint16_t header = 0;
        uint32_t obj[7] = {};
        FUSB302_get_message(&c->FUSB302, &header, obj);
        PD_protocol_handle_msg(&c->protocol, header, obj, &protocol_event);
        status_log_event(c, STATUS_LOG_MSG_RX, obj);
        if (protocol_event) {
            PD_handle_protocol_event(c, protocol_event);
        }
    }
    if (events & FUSB302_EVENT_GOOD_CRC_SENT) {
        uint16_t header;
        uint32_t obj[7];
        c->FUSB302.delay_ms(2);  /* Delay respond in case there are retry messages */
        if (PD_protocol_respond(&c->protocol, &header, obj)) {
            status_log_event(c, STATUS_LOG_MSG_TX, obj);
            FUSB302_tx_sop(&c->FUSB302, header, obj);
        }
    }
}

static bool PD_timer(struct usb_pd_pps *c)
{
    uint32_t t = system_millis;
    if (c->wait_src_cap && t - c->time_wait_src_cap > t_TypeCSinkWaitCap) {
        c->time_wait_src_cap = t;
        if (c->get_src_cap_retry_count < 3) {
            uint16_t header = 0;
            c->get_src_cap_retry_count += 1;
            /* Try to request soruce capabilities message
             * (will not cause power cycle VBUS) */
            PD_protocol_create_get_src_cap(&c->protocol, &header);
            status_log_event(c, STATUS_LOG_MSG_TX, NULL);
            FUSB302_tx_sop(&c->FUSB302, header, 0);
        } else {
            c->get_src_cap_retry_count = 0;
            /* Hard reset will cause the source power cycle VBUS. */
            FUSB302_tx_hard_reset(&c->FUSB302);
            PD_protocol_reset(&c->protocol);
        }
    }
    if (c->wait_ps_rdy) {
        if (t - c->time_wait_ps_rdy > t_RequestToPSReady) {
            c->wait_ps_rdy = 0;
            set_default_power(c);
        }
    } else if (c->send_request ||
            (c->status_power == STATUS_POWER_PPS && t - c->time_PPS_request >
             t_PPSRequest)) {
        uint16_t header = 0;
        uint32_t obj[7] = {};

        c->wait_ps_rdy = 1;
        c->send_request = 0;
        c->time_PPS_request = t;
        /* Send request if option updated or regularly in PPS mode
         * to keep power alive */
        PD_protocol_create_request(&c->protocol, &header, obj);
        status_log_event(c, STATUS_LOG_MSG_TX, obj);
        c->time_wait_ps_rdy = system_millis;
        FUSB302_tx_sop(&c->FUSB302, header, obj);
    }
    if (t - c->time_polling > t_PD_POLLING) {
        c->time_polling = t;
        return true;
    }
    return false;
}

static void set_default_power(struct usb_pd_pps *c)
{
    status_power_ready(c, STATUS_POWER_TYP, PD_V(5), PD_A(1));
    status_log_event(c, STATUS_LOG_POWER_READY, NULL);
}

void status_power_ready(struct usb_pd_pps *c, status_power_t status,
        uint16_t voltage, uint16_t current)
{
    c->ready_voltage = voltage;
    c->ready_current = current;
    c->status_power = status;
}

#define LOG(format, ...)                                                       \
    do  {                                                                      \
            n = printf("%10lu:", system_millis);                               \
            n += printf(format, ## __VA_ARGS__);                               \
    } while (0)

static int status_log_readline_msg(struct usb_pd_pps *c, uint16_t msg_header,
        uint8_t status, uint32_t *obj)
{
    int n = 0, i = 0;
    /* output message header */
    char type = status == STATUS_LOG_MSG_TX ? 'T' : 'R';
    PD_msg_info_t info = {};
    PD_protocol_get_msg_info(msg_header, &info);
    if (c->status_log_level >= PD_LOG_LEVEL_VERBOSE) {
        const char * ext = info.extended ? "ext, " : "";
        LOG("%cX %s id=%d %sraw=0x%04X\n", type, info.name, info.id, ext,
                msg_header);
    } else {
        LOG("%cX %s\n", type, info.name);
    }

    if (obj)
    {
        for (i = 0; i < info.num_of_obj; i++)
            /* output object data */
            LOG("obj%d=0x%08lx\n", i, *obj++);

    }
    return n;
}

static int status_log_readline_src_cap(struct usb_pd_pps *c)
{
    PD_power_info_t p = {};
    int n = 0;
    uint8_t i = 0;
    while (PD_protocol_get_power_info(&c->protocol, i, &p)) {
        /* PD_power_data_obj_type_t */
        const char * str_pps[] = {"", " BAT", " VAR", " PPS"};
        uint8_t selected = PD_protocol_get_selected_power(&c->protocol);
        char min_v[8] = {0}, max_v[8] = {0}, power[8] = {0};

        LOG("[%d] %s%s %s%s%s ", i, min_v, max_v, power,
                str_pps[p.type], i == selected ? " *" : "");

        if (p.min_v)
            printf("%d.%02dV-", p.min_v / 20, (p.min_v * 5) % 100);
        if (p.max_v)
            printf("%d.%02dV", p.max_v / 20, (p.max_v * 5) % 100);
        if (p.max_i) {
            printf("%d.%02dA", p.max_i / 100, p.max_i % 100);
        } else {
            printf("%d.%02dW", p.max_p / 4, p.max_p * 25);
        }

        printf("\n");
        i++;
    }
    return n;
}

int status_log_event(struct usb_pd_pps *c, uint8_t status,
        uint32_t *obj)
{
    int n = 0;
    uint16_t msg_header = 0;

    switch (status) {
    case STATUS_LOG_MSG_TX:
        msg_header = PD_protocol_get_tx_msg_header(&c->protocol);
        break;
    case STATUS_LOG_MSG_RX:
        msg_header = PD_protocol_get_rx_msg_header(&c->protocol);
        break;
    default:
        break;
    }

    switch (status) {
    case STATUS_LOG_MSG_TX:
    case STATUS_LOG_MSG_RX:
        n = status_log_readline_msg(c, msg_header, status, obj);
        break;
    case STATUS_LOG_DEV:
        if (c->status_initialized) {
            uint8_t version_ID = 0, revision_ID = 0;
            FUSB302_get_ID(&c->FUSB302, &version_ID, &revision_ID);
            LOG("FUSB302 ver ID:%c_rev%c\n",
                    'A' + version_ID, 'A' + revision_ID);
        } else {
            LOG("FUSB302 init error\n");
        }
        break;
    case STATUS_LOG_CC: {
        const char *detection_type_str[] = {"USB", "1.5", "3.0"};
        uint8_t cc1 = 0, cc2 = 0;
        FUSB302_get_cc(&c->FUSB302, &cc1, &cc2);
        if (cc1 == 0 && cc2 == 0) {
            LOG("USB attached vRA\n");
        } else if (cc1 && cc2 == 0) {
            LOG("USB attached CC1 vRd-%s\n", detection_type_str[cc1 - 1]);
        } else if (cc2 && cc1 == 0) {
            LOG("USB attached CC2 vRd-%s\n", detection_type_str[cc2 - 1]);
        } else {
            LOG("USB attached unknown\n");
        }
        break; }
    case STATUS_LOG_SRC_CAP:
        n = status_log_readline_src_cap(c);
        break;
    case STATUS_LOG_POWER_READY: {
        uint16_t v = c->ready_voltage;
        uint16_t a = c->ready_current;
        if (c->status_power == STATUS_POWER_TYP) {
            LOG("%d.%02dV %d.%02dA supply ready\n",
                    v / 20, (v * 5) % 100, a / 100, a % 100);
        } else if (c->status_power == STATUS_POWER_PPS) {
            LOG("PPS %d.%02dV %d.%02dA supply ready\n",
                    v / 50, (v * 2) % 100, a / 20, (a * 5) % 100);
        }
        break; }
    case STATUS_LOG_POWER_PPS_STARTUP:
        LOG("PPS 2-stage startup\n");
        break;
    case STATUS_LOG_POWER_REJECT:
        LOG("Request Rejected\n");
        break;
    case STATUS_LOG_LOAD_SW_ON:
        LOG("Load SW ON\n");
        break;
    case STATUS_LOG_LOAD_SW_OFF:
        LOG("Load SW OFF\n");
        break;
    }

    return n;
}

