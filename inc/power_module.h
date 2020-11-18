#ifndef POWER_MODULE_H__
#define POWER_MODULE_H__
#include "ble_bas.h"
#include "app_timer.h"

#define BATTERY_LEVEL_MEAS_INTERVAL     APP_TIMER_TICKS(2000, APP_TIMER_PRESCALER)                          /**< Battery level measurement interval (ticks). */


extern ble_bas_t            m_bas;                                                                          /**< Structure used to identify the battery service. */

void bas_init(void);
void battery_level_update(void);
void battery_level_meas_timeout_handler(void * p_context);
void sleep_mode_enter(void);
void power_manage(void);

#endif // POWER_MODULE_H__