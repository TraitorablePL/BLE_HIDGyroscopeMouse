#ifndef CORE_MODULE_H__
#define CORE_MODULE_H__
#include "stdint.h"

/**@brief Function for handling Service errors.
 *
 * @details A pointer to this function will be passed to each service which may need to inform the
 *          application about an error.
 *
 * @param[in]   nrf_error   Error code containing information about what went wrong.
 */
void service_error_handler(uint32_t nrf_error);

/**@brief Function for initializing services that will be used by the application.
 */
void services_init(void);

/**@brief Function for the GAP initialization.
 *
 * @details This function sets up all the necessary GAP (Generic Access Profile) parameters of the
 *          device including the device name, appearance, and the preferred connection parameters.
 */
void gap_params_init(void);

/**@brief Function for initializing Device Information Service.
 */
void dis_init(void);

/**@brief Function for handling a Connection Parameters error.
 *
 * @param[in]   nrf_error   Error code containing information about what went wrong.
 */
void conn_params_error_handler(uint32_t nrf_error);

/**@brief Function for initializing the Connection Parameters module.
 */
void conn_params_init(void);

#endif // CORE_MODULE_H__