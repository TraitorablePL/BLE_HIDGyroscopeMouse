#ifndef ADVERTISE_MODULE_H__
#define ADVERTISE_MODULE_H__
#include "ble_advertising.h"

/**@brief Function for starting advertising.
 */
void advertising_start(void);

/**@brief Function for handling advertising errors.
 *
 * @param[in] nrf_error  Error code containing information about what went wrong.
 */
void ble_advertising_error_handler(uint32_t nrf_error);

/**@brief Function for handling advertising events.
 *
 * @details This function will be called for advertising events which are passed to the application.
 *
 * @param[in] ble_adv_evt  Advertising event.
 */
void on_adv_evt(ble_adv_evt_t ble_adv_evt);

/**@brief Function for initializing the Advertising functionality.
 */
void advertising_init(void);

#endif // ADVERTISE_MODULE_H__