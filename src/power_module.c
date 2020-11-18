#include "power_module.h"
#include <string.h>
#include "nordic_common.h"
#include "app_error.h"
#include "ble_gap.h"
#include "bsp.h"
#include "bsp_btn_ble.h"
#include "nrf_error.h"
#include "nrf_soc.h"

#define BATTERY_LEVEL                   100

extern ble_bas_t            m_bas;                                                                          /**< Structure used to identify the battery service. */

/**
 * @brief Function for initializing Battery Service.
 */
void bas_init(void){

    uint32_t       err_code;
    ble_bas_init_t bas_init_obj;

    memset(&bas_init_obj, 0, sizeof(bas_init_obj));

    bas_init_obj.evt_handler          = NULL;
    bas_init_obj.support_notification = true;
    bas_init_obj.p_report_ref         = NULL;
    bas_init_obj.initial_batt_level   = 100;

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&bas_init_obj.battery_level_char_attr_md.cccd_write_perm);
    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&bas_init_obj.battery_level_char_attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&bas_init_obj.battery_level_char_attr_md.write_perm);

    BLE_GAP_CONN_SEC_MODE_SET_ENC_NO_MITM(&bas_init_obj.battery_level_report_read_perm);

    err_code = ble_bas_init(&m_bas, &bas_init_obj);
    APP_ERROR_CHECK(err_code);
}

/**
 * @brief Function for performing a battery measurement, and update the Battery Level characteristic in the Battery Service.
 */
void battery_level_update(void){

    uint32_t err_code;
    uint8_t  battery_level = BATTERY_LEVEL;

    err_code = ble_bas_battery_level_update(&m_bas, battery_level);
    if ((err_code != NRF_SUCCESS) &&
        (err_code != NRF_ERROR_INVALID_STATE) &&
        (err_code != BLE_ERROR_NO_TX_PACKETS) &&
        (err_code != BLE_ERROR_GATTS_SYS_ATTR_MISSING)
       ){
        APP_ERROR_HANDLER(err_code);
    }
}

/**
 * @brief Function for handling the Battery measurement timer timeout.
 *
 * @details This function will be called each time the battery level measurement timer expires.
 *
 * @param[in]   p_context   Pointer used for passing some arbitrary information (context) from the
 *                          app_start_timer() call to the timeout handler.
 */
void battery_level_meas_timeout_handler(void * p_context){

    UNUSED_PARAMETER(p_context);
    battery_level_update();
}

/**
 * @brief Function for putting the chip into sleep mode.
 *
 * @note This function will not return.
 */
void sleep_mode_enter(void){

    uint32_t err_code = bsp_indication_set(BSP_INDICATE_IDLE);

    APP_ERROR_CHECK(err_code);

    // Prepare wakeup buttons.
    err_code = bsp_btn_ble_sleep_mode_prepare();
    APP_ERROR_CHECK(err_code);

    // Go to system-off mode (this function will not return; wakeup will cause a reset).
    err_code = sd_power_system_off();
    APP_ERROR_CHECK(err_code);
}

/**
 * @brief Function for the Power manager.
 */
void power_manage(void){

    uint32_t err_code = sd_app_evt_wait();

    APP_ERROR_CHECK(err_code);
}

