#ifndef TIMERS_MODULE_H__
#define TIMERS_MODULE_H__

#define APP_TIMER_PRESCALER             0                                                                   /**< Value of the RTC1 PRESCALER register. */

#define MOUSE_POS_UPDATE_INTERVAL           APP_TIMER_TICKS(20, APP_TIMER_PRESCALER)
#define MSG_INTERVAL                        APP_TIMER_TICKS(10, APP_TIMER_PRESCALER)                          /**< SPI Message interval (ticks). */

/**@brief Function for the Timer initialization.
 *
 * @details Initializes the timer module.
 */
void timers_init(void);

/**@brief Function for starting timers.
 */
void timers_start(void);

#endif // TIMERS_MODULE_H__