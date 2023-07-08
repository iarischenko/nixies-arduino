/**
 * PD_UFP.h
 *
 *  Updated on: Jan 25, 2021
 *      Author: Ryan Ma
 *  Ported on stm32: June 27, 2023
 *      Author: Ivan Arishchenko
 *
 * Minimalist USB PD Library for stm32-nixie board
 * Only support UFP(device) sink only functionality
 * Requires FUSB302_UFP.h, PD_UFP_Protocol.h and LibOpenCM3 Library
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

/*  PD_UFP_core_c */

void PD_UFP_core_c(struct PD_UFP_core_c *context);
/* Init */
void PD_UFP_core_c_init(enum PD_power_option_t power_option);
void PD_UFP_core_c_init_PPS(uint16_t PPS_voltage, uint8_t PPS_current,
        enum PD_power_option_t power_option);
/* Task */
void PD_UFP_core_c_run(void);
/* Status */
bool is_power_ready(void) { return status_power == STATUS_POWER_TYP; }
bool is_PPS_ready(void)   { return status_power == STATUS_POWER_PPS; }
bool is_ps_transition(void) { return send_request || wait_ps_rdy; }
/* Get Voltage in 50mV units, 20mV(PPS) */
uint16_t get_voltage(void) { return ready_voltage; }
uint16_t get_current(void) { return ready_current; }

/* Set Current in 10mA units, 50mA(PPS) */
bool PD_UFP_core_c_set_PPS(struct PD_UFP_core_c *context, uint16_t PPS_voltage,
        uint8_t PPS_current);
void PD_UFP_core_c_set_power_option(struct PD_UFP_core_c *context,
        enum PD_power_option_t power_option);

void PD_UFP_core_c_handle_protocol_event(PD_protocol_event_t events);
void PD_UFP_core_c_handle_FUSB302_event(FUSB302_event_t events);

bool timer(void);
void set_default_power(void);
void delay_ms(uint16_t ms);
void PD_UFP_c_status_power_ready(status_power_t status, uint16_t voltage,
        uint16_t current);

/* Status logging */
void status_log_event(uint8_t status, uint32_t * obj);

struct usb_pd_pps
{
    /* Device */
    FUSB302_dev_t FUSB302;
    PD_protocol_t protocol;
    PD_log_t log;
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
    uint16_t time_polling;
    uint16_t time_wait_src_cap;
    uint16_t time_wait_ps_rdy;
    uint16_t time_PPS_request;
    uint8_t get_src_cap_retry_count;
    uint8_t wait_src_cap;
    uint8_t wait_ps_rdy;
    uint8_t send_request;
    /* Time functions */
    uint16_t clock_ms(void);
};


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

/* Task */
void print_status(void);
/* Get */
int status_log_readline(char * buffer, int maxlen);
int status_log_readline_msg(char * buffer, int maxlen, status_log_t * log);
int status_log_readline_src_cap(char * buffer, int maxlen);
/* Status log functions */
uint8_t status_log_obj_add(uint16_t header, uint32_t * obj);
void status_log_event(uint8_t status, uint32_t * obj);


#endif /* PD_UFP_H */
