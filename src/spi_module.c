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

    int16_t acc_x = 0;
    int16_t acc_y = 0;
    int16_t acc_z = 0;

    spi_transfer_done = true;


    if(data_read){

        acc_x = m_rx_buf[2]<<8 | m_rx_buf[1];
        acc_y = m_rx_buf[4]<<8 | m_rx_buf[3];
        acc_z = m_rx_buf[6]<<8 | m_rx_buf[5];
        
        NRF_LOG_INFO("ACC X: %d, Y: %d, Z: %d\r\n", acc_x, acc_y, acc_z);
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
    spi_config.frequency = NRF_DRV_SPI_FREQ_500K;

    uint32_t err_code = nrf_drv_spi_init(&spi, &spi_config, spi_event_handler);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for SPI bus initialization.
 */
void acc_init(void){

    spi_message_t init_msg = {
        .rw_addr = (WRITE | CTRL1_XL),
        .data[0] = (ACC_100HZ | ACC_2G),
        .len = 2
    };

    spi_message_t high_perf_msg = {
        .rw_addr = (WRITE | CTRL6_C),
        .data[0] = (ACC_HIGH_PERF),
        .len = 2
    };

    current_msg = &init_msg;

    memset(m_rx_buf, 0, BUFFER_SIZE);
    spi_transfer_done = false;
    APP_ERROR_CHECK(nrf_drv_spi_transfer(&spi, (uint8_t*)current_msg, current_msg->len+1, m_rx_buf, current_msg->len+1));

    while(!spi_transfer_done){};

    current_msg = &high_perf_msg;
}
