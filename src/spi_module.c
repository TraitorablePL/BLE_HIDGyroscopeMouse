#include "spi_module.h"
#include <string.h>
#include "nordic_common.h"
#include "app_error.h"
#include "nrf_log.h"
#include "custom_board.h"

static const nrf_drv_spi_t  spi = NRF_DRV_SPI_INSTANCE(0);                                                  /**< SPI instance. */
static volatile bool        spi_transfer_done = true;                                                       /**< Flag used to indicate that SPI instance completed the transfer. */
static volatile bool        data_read = false;

static uint8_t              m_rx_buf[BUFFER_SIZE];                                                          /**< RX buffer. */
spi_message_t               *current_msg;

/**
 * @brief Function for handling SPI Message timer timeout.
 */
void spi_message_timeout_handler(void * p_context){

    UNUSED_PARAMETER(p_context);
    if(spi_transfer_done){
        // Reset rx buffer and transfer done flag
        memset(m_rx_buf, 0, BUFFER_SIZE);
        spi_transfer_done = false;
        data_read = true;
        APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, (uint8_t*)current_msg, current_msg->len+1, m_rx_buf, current_msg->len+1));
    }
}

/**
 * @brief SPI user event handler.
 * @param event
 */

void spi_event_handler(nrf_drv_spi_evt_t const * p_event){

    int16_t dps_x = 0;
    int16_t dps_y = 0;
    int16_t dps_z = 0;

    spi_transfer_done = true;


    if(data_read){

        dps_x = m_rx_buf[2]<<8 | m_rx_buf[1];
        dps_y = m_rx_buf[4]<<8 | m_rx_buf[3];
        dps_z = m_rx_buf[6]<<8 | m_rx_buf[5];
        
        NRF_LOG_INFO("GYRO X: %d, Y: %d, Z: %d\r\n", dps_x, dps_y, dps_z);
    }
    else{
        NRF_LOG_INFO("Transfer completed.\r\n");
        NRF_LOG_INFO("Received: 0x%x\r\n", m_rx_buf[1]);
    }
}

/**
 * @brief Function for SPI bus initialization.
 */
void spi_init(void){

    nrf_drv_spi_config_t spi_config = NRF_DRV_SPI_DEFAULT_CONFIG;
    spi_config.ss_pin   = SPIM0_SS_PIN;
    spi_config.miso_pin = SPIM0_MISO_PIN;
    spi_config.mosi_pin = SPIM0_MOSI_PIN;
    spi_config.sck_pin  = SPIM0_SCK_PIN;
    spi_config.mode = NRF_DRV_SPI_MODE_0;
    spi_config.frequency = NRF_DRV_SPI_FREQ_250K;

    uint32_t err_code = nrf_drv_spi_init(&spi, &spi_config, spi_event_handler);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for SPI bus initialization.
 */
void acc_init(void){

    spi_message_t init_msg = {
        .rw_addr = (WRITE | CTRL2_G),
        .data[0] = (GYRO_416HZ | GYRO_500DPS),
        .len = 1
    };

    spi_message_t inc_msg = {
        .rw_addr = (WRITE | CTRL3_C),
        .data[0] = (IF_INC),
        .len = 1
    };
    
    current_msg = &init_msg;

    memset(m_rx_buf, 0, BUFFER_SIZE);
    spi_transfer_done = false;
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, (uint8_t*)current_msg, current_msg->len+1, m_rx_buf, current_msg->len+1));

    while(!spi_transfer_done){};

    current_msg = &inc_msg;

    memset(m_rx_buf, 0, BUFFER_SIZE);
    spi_transfer_done = false;
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, (uint8_t*)current_msg, current_msg->len+1, m_rx_buf, current_msg->len+1));
}
