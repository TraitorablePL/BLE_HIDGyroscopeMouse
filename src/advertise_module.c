#include "advertise_module.h"
#include "peer_module.h"
#include "power_module.h"
#include "app_error.h"
#include "nrf_log.h"
#include "bsp.h"
#include "ble_advdata.h"
#include "ble_gap.h"
#include <string.h>

#define APP_ADV_FAST_INTERVAL           0x0028                                                              /**< Fast advertising interval (in units of 0.625 ms. This value corresponds to 25 ms.). */
#define APP_ADV_SLOW_INTERVAL           0x0C80                                                              /**< Slow advertising interval (in units of 0.625 ms. This value corrsponds to 2 seconds). */

#define APP_ADV_FAST_TIMEOUT            30                                                                  /**< The duration of the fast advertising period (in seconds). */
#define APP_ADV_SLOW_TIMEOUT            180                                                                 /**< The duration of the slow advertising period (in seconds). */

extern ble_uuid_t           m_adv_uuids[1];                                                                   /**< Universally unique service identifiers. */

/**@brief Function for starting advertising.
 */
void advertising_start(void){

    ret_code_t ret;

    whitelist_setup();

    ret = ble_advertising_start(BLE_ADV_MODE_FAST);
    APP_ERROR_CHECK(ret);
}

/**@brief Function for handling advertising errors.
 *
 * @param[in] nrf_error  Error code containing information about what went wrong.
 */
void ble_advertising_error_handler(uint32_t nrf_error){

    APP_ERROR_HANDLER(nrf_error);
}

/**@brief Function for handling advertising events.
 *
 * @details This function will be called for advertising events which are passed to the application.
 *
 * @param[in] ble_adv_evt  Advertising event.
 */
void on_adv_evt(ble_adv_evt_t ble_adv_evt){

    uint32_t err_code;

    switch (ble_adv_evt){

        case BLE_ADV_EVT_DIRECTED:
            NRF_LOG_INFO("BLE_ADV_EVT_DIRECTED\r\n");
            err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING_DIRECTED);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_ADV_EVT_FAST:
            NRF_LOG_INFO("BLE_ADV_EVT_FAST\r\n");
            err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_ADV_EVT_SLOW:
            NRF_LOG_INFO("BLE_ADV_EVT_SLOW\r\n");
            err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING_SLOW);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_ADV_EVT_FAST_WHITELIST:
            NRF_LOG_INFO("BLE_ADV_EVT_FAST_WHITELIST\r\n");
            err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING_WHITELIST);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_ADV_EVT_SLOW_WHITELIST:
            NRF_LOG_INFO("BLE_ADV_EVT_SLOW_WHITELIST\r\n");
            err_code = bsp_indication_set(BSP_INDICATE_ADVERTISING_WHITELIST);
            APP_ERROR_CHECK(err_code);
            err_code = ble_advertising_restart_without_whitelist();
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_ADV_EVT_IDLE:
            err_code = bsp_indication_set(BSP_INDICATE_IDLE);
            APP_ERROR_CHECK(err_code);
            sleep_mode_enter();
            break;

        case BLE_ADV_EVT_WHITELIST_REQUEST:
        {
            whitelist_request();
        }
        break;

        case BLE_ADV_EVT_PEER_ADDR_REQUEST:
        {
            peer_addr_request();
            break;
        }

        default:
            break;
    }
}

/**@brief Function for initializing the Advertising functionality.
 */
void advertising_init(void){

    uint32_t               err_code;
    uint8_t                adv_flags;
    ble_advdata_t          advdata;
    ble_adv_modes_config_t options;

    // Build and set advertising data
    memset(&advdata, 0, sizeof(advdata));

    adv_flags                       = BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE;
    advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    advdata.include_appearance      = true;
    advdata.flags                   = adv_flags;
    advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    advdata.uuids_complete.p_uuids  = m_adv_uuids;

    memset(&options, 0, sizeof(options));
    options.ble_adv_whitelist_enabled      = true;
    options.ble_adv_directed_enabled       = true;
    options.ble_adv_directed_slow_enabled  = false;
    options.ble_adv_directed_slow_interval = 0;
    options.ble_adv_directed_slow_timeout  = 0;
    options.ble_adv_fast_enabled           = true;
    options.ble_adv_fast_interval          = APP_ADV_FAST_INTERVAL;
    options.ble_adv_fast_timeout           = APP_ADV_FAST_TIMEOUT;
    options.ble_adv_slow_enabled           = true;
    options.ble_adv_slow_interval          = APP_ADV_SLOW_INTERVAL;
    options.ble_adv_slow_timeout           = APP_ADV_SLOW_TIMEOUT;

    err_code = ble_advertising_init(&advdata,
                                    NULL,
                                    &options,
                                    on_adv_evt,
                                    ble_advertising_error_handler);
    APP_ERROR_CHECK(err_code);
}
