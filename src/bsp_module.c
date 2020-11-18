#include "bsp_module.h"
#include "ble_gap.h"
#include "ble_hci.h"
#include "ble_types.h"
#include "ble_advertising.h"
#include "bsp_btn_ble.h"
#include "nrf_error.h"
#include "app_error.h"
#include "app_timer.h"
#include "power_module.h"
#include "hid_module.h"

#define MOVEMENT_SPEED                  5                                                                   /**< Number of pixels by which the cursor is moved each time a button is pushed. */
#define APP_TIMER_PRESCALER             0                                                                   /**< Value of the RTC1 PRESCALER register. */

extern uint16_t             m_conn_handle;

/**@brief Function for handling events from the BSP module.
 *
 * @param[in]   event   Event generated by button press.
 */
void bsp_event_handler(bsp_event_t event){

    uint32_t err_code;

    switch (event){

        case BSP_EVENT_SLEEP:
            sleep_mode_enter();
            break;

        case BSP_EVENT_DISCONNECT:
            err_code = sd_ble_gap_disconnect(m_conn_handle,
                                             BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            if (err_code != NRF_ERROR_INVALID_STATE){

                APP_ERROR_CHECK(err_code);
            }
            break;

        case BSP_EVENT_WHITELIST_OFF:
            if (m_conn_handle == BLE_CONN_HANDLE_INVALID){
                err_code = ble_advertising_restart_without_whitelist();
                if (err_code != NRF_ERROR_INVALID_STATE){
                    APP_ERROR_CHECK(err_code);
                }
            }
            break;

        case BSP_EVENT_KEY_0:
            if (m_conn_handle != BLE_CONN_HANDLE_INVALID){
                mouse_movement_send(-MOVEMENT_SPEED, 0);
            }
            break;

        case BSP_EVENT_KEY_1:
            if (m_conn_handle != BLE_CONN_HANDLE_INVALID){
                mouse_movement_send(0, -MOVEMENT_SPEED);
            }
            break;

        case BSP_EVENT_KEY_2:
            if (m_conn_handle != BLE_CONN_HANDLE_INVALID){
                mouse_movement_send(MOVEMENT_SPEED, 0);
            }
            break;

        case BSP_EVENT_KEY_3:
            if (m_conn_handle != BLE_CONN_HANDLE_INVALID){
                mouse_movement_send(0, MOVEMENT_SPEED);
            }
            break;

        default:
            break;
    }
}

/**@brief Function for initializing buttons and leds.
 *
 * @param[out] p_erase_bonds  Will be true if the clear bonding button was pressed to wake the application up.
 */
void buttons_leds_init(bool * p_erase_bonds){

    bsp_event_t startup_event;

    uint32_t err_code = bsp_init(BSP_INIT_LED | BSP_INIT_BUTTONS,
                                 APP_TIMER_TICKS(100, APP_TIMER_PRESCALER),
                                 bsp_event_handler);

    APP_ERROR_CHECK(err_code);

    err_code = bsp_btn_ble_init(NULL, &startup_event);
    APP_ERROR_CHECK(err_code);

    *p_erase_bonds = (startup_event == BSP_EVENT_CLEAR_BONDING_DATA);
}