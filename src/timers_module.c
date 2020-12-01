#include "timers_module.h"
#include "app_timer_appsh.h"
#include "app_timer.h"
#include "app_error.h"
#include "power_module.h"
#include "spi_module.h"
#include "hid_module.h"

#define APP_TIMER_PRESCALER             0                                                                   /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE         4                                                                   /**< Size of timer operation queues. */

APP_TIMER_DEF(m_msg_timer_id);                                                                              /**< SPI Message timer. */
APP_TIMER_DEF(m_mouse_timer_id);                                                                          
APP_TIMER_DEF(m_battery_timer_id);                                                                          /**< Battery timer. */


/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module.
 */
void timers_init(void){

    uint32_t err_code;

    // Initialize timer module, making it use the scheduler.
    APP_TIMER_APPSH_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, true);

    // Create battery timer.
    err_code = app_timer_create(&m_battery_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                battery_level_meas_timeout_handler);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_create(&m_mouse_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                mouse_pos_timeout_handler);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_create(&m_msg_timer_id,
                                APP_TIMER_MODE_REPEATED,
                                spi_message_timeout_handler);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for starting timers.
 */
void timers_start(void){

    uint32_t err_code;

    err_code = app_timer_start(m_battery_timer_id, BATTERY_LEVEL_MEAS_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_start(m_msg_timer_id, MSG_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);

    err_code = app_timer_start(m_mouse_timer_id, MOUSE_POS_UPDATE_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code);

    
}
