
/**
 * PD_UFP.h
 *
 *  Updated on: Jan 25, 2021
 *      Author: Ryan Ma
 *
 * Minimalist USB PD Ardunio Library for PD Micro board
 * Only support UFP(device) sink only functionality
 * Requires FUSB302_UFP.h, PD_UFP_Protocol.h and Standard Arduino Library
 *
 * Support PD3.0 PPS
 *
 */

#ifndef PD_UFP_H
#define PD_UFP_H

#include <stdint.h>
#include "FUSB302_UFP.h"
#include "PD_UFP_Protocol.h"

enum {
    PD_UFP_VOLTAGE_LED_OFF      = 0,
    PD_UFP_VOLTAGE_LED_5V       = 1,
    PD_UFP_VOLTAGE_LED_9V       = 2,
    PD_UFP_VOLTAGE_LED_12V      = 3,
    PD_UFP_VOLTAGE_LED_15V      = 4,
    PD_UFP_VOLTAGE_LED_20V      = 5,
    PD_UFP_VOLTAGE_LED_AUTO     = 6
};
typedef uint8_t PD_UFP_VOLTAGE_LED_t;

enum {
    PD_UFP_CURRENT_LED_OFF      = 0,
    PD_UFP_CURRENT_LED_LE_1V    = 1,
    PD_UFP_CURRENT_LED_LE_3V    = 2,
    PD_UFP_CURRENT_LED_GT_3V    = 3,
    PD_UFP_CURRENT_LED_AUTO     = 4
};
typedef uint8_t PD_UFP_CURRENT_LED_t;

enum {
    STATUS_POWER_NA = 0,
    STATUS_POWER_TYP,
    STATUS_POWER_PPS
};
typedef uint8_t status_power_t;

struct usb_pd_pps
{
    /* Device */
    FUSB302_dev_t FUSB302;
    PD_protocol_t protocol;
    /* Power ready power */
    uint16_t ready_voltage;
    uint16_t ready_current;
    /* PPS setup */
    uint16_t PPS_voltage_next;
    uint8_t PPS_current_next;
    /* Status */
    uint8_t status_initialized;
    uint8_t status_src_cap_received;
    status_power_t status_power;
    /* Timer and counter for PD Policy */
    uint32_t time_polling;
    uint32_t time_wait_src_cap;
    uint32_t time_wait_ps_rdy;
    uint32_t time_PPS_request;
    uint8_t get_src_cap_retry_count;
    uint8_t wait_src_cap;
    uint8_t wait_ps_rdy;
    uint8_t send_request;
    uint32_t status_log_level;
};

void PD_init(struct usb_pd_pps *c, enum PD_power_option_t power_option);
void PD_init_PPS(struct usb_pd_pps *c, uint16_t PPS_voltage,
        uint8_t PPS_current, enum PD_power_option_t power_option);
void PD_run(struct usb_pd_pps *c);

static inline bool is_power_ready(struct usb_pd_pps *c)
{
    return c->status_power == STATUS_POWER_TYP;
}

static inline bool is_PPS_ready(struct usb_pd_pps *c)
{
    return c->status_power == STATUS_POWER_PPS;
}

static inline bool is_ps_transition(struct usb_pd_pps *c)
{
    return c->send_request || c->wait_ps_rdy;
}

/* Voltage in 50mV units, 20mV(PPS) */
static inline uint16_t get_voltage(struct usb_pd_pps *c)
{
    return c->ready_voltage;
}
/*  Current in 10mA units, 50mA(PPS) */
static inline uint16_t get_current(struct usb_pd_pps *c)
{
    return c->ready_current;
}
bool PD_set_PPS(struct usb_pd_pps *c, uint16_t PPS_voltage,
        uint8_t PPS_current);
void PD_set_power_option(struct usb_pd_pps *c,
        enum PD_power_option_t power_option);

void PD_handle_protocol_event(struct usb_pd_pps *c, PD_protocol_event_t events);

////////////////////////////////////////////////////////////////////////////////
// Optional: PD_UFP_log_c, extended from PD_UFP_c to provide logging function.
//           Asynchronous, minimal impact on PD timing.
////////////////////////////////////////////////////////////////////////////////
struct status_log_t {
    uint16_t time;
    uint16_t msg_header;
    uint8_t obj_count;
    uint8_t status;
};

enum pd_log_level_t {
    PD_LOG_LEVEL_INFO,
    PD_LOG_LEVEL_VERBOSE
};

#endif

