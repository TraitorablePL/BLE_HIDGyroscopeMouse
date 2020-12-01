#include "app_scheduler.h"
#include "spi_module.h"
#include "power_module.h"
#include "bsp_module.h"
#include "peer_module.h"
#include "stack_module.h"
#include "advertise_module.h"
#include "hid_module.h"
#include "timers_module.h"
#include "core_module.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

ble_hids_t           m_hids;                                                                         /**< Structure used to identify the HID service. */
ble_bas_t            m_bas;                                                                          /**< Structure used to identify the battery service. */
bool                 m_in_boot_mode = false;                                                         /**< Current protocol mode. */
uint16_t             m_conn_handle  = BLE_CONN_HANDLE_INVALID;                                       /**< Handle of the current connection. */

ble_uuid_t           m_adv_uuids[] = {{BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE, BLE_UUID_TYPE_BLE}}; /**< Universally unique service identifiers. */ 

/**@brief Function for application main entry.
 */

int main(void){

    bool     erase_bonds;
    uint32_t err_code;
    
    // Initialize.
    err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    timers_init();
    spi_init();
    acc_init();
    buttons_leds_init(&erase_bonds);
    ble_stack_init();
    scheduler_init();
    peer_manager_init(erase_bonds);

    if (erase_bonds == true){
        NRF_LOG_INFO("Bonds erased!\r\n");
    }

    gap_params_init();
    advertising_init();
    services_init();
    conn_params_init();

    spi_message_t acc_data_msg = {
        .rw_addr = (READ | GYRO_X_L),
        .len = 6
    };

    current_msg = &acc_data_msg;

    // Start execution.
    NRF_LOG_INFO("Gyro Mausior start!\r\n");
    timers_start();
    advertising_start();

    // Enter main loop.
    for (;;){
        app_sched_execute();
        if (NRF_LOG_PROCESS() == false){
            power_manage();
        }
    }
}
