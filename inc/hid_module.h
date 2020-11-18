#ifndef HID_MODULE_H__
#define HID_MODULE_H__
#include "ble_hids.h"

/**@brief Function for initializing HID Service.
 */
void hids_init(void);

/**@brief Function for handling HID events.
 *
 * @details This function will be called for all HID events which are passed to the application.
 *
 * @param[in]   p_hids  HID service structure.
 * @param[in]   p_evt   Event received from the HID service.
 */
void on_hids_evt(ble_hids_t * p_hids, ble_hids_evt_t * p_evt);

/**@brief Function for sending a Mouse Movement.
 *
 * @param[in]   x_delta   Horizontal movement.
 * @param[in]   y_delta   Vertical movement.
 */
void mouse_movement_send(int16_t x_delta, int16_t y_delta);

#endif // HID_MODULE_H__