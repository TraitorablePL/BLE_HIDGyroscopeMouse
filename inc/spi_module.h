#ifndef SPI_MODULE_H__
#define SPI_MODULE_H__
#include "stdint.h"
#include "nrf_drv_spi.h"


#define STAT_REG                        0x1e 
#define ACC_X_L                         0x28
#define WHO_AM_I                        0x0F
#define CTRL3_C                         0x12
#define IF_INC                          0x04

//ACC 

#define ACC_HIGH_PERF                   0x10

#define ACC_100HZ                       0x50
#define ACC_8G                          0x0C
#define ACC_2G                          0x00

#define CTRL1_XL                        0x10
#define CTRL6_C                         0x15

//GYRO

#define CTRL2_G                         0x11
#define GYRO_X_L                        0x22

#define GYRO_416HZ                      0x60
#define GYRO_500DPS                     0x04

//SPI part start

#define MSG_INTERVAL                    APP_TIMER_TICKS(100, APP_TIMER_PRESCALER)                          /**< SPI Message interval (ticks). */

#define BUFFER_SIZE                     16

#define WRITE                           (0<<7)
#define READ                            (1<<7)

typedef struct {
    uint8_t rw_addr;
    uint8_t data[BUFFER_SIZE];
    uint8_t len;
} spi_message_t;

extern spi_message_t        *current_msg;

void spi_message_timeout_handler(void * p_context);
void spi_event_handler(nrf_drv_spi_evt_t const * p_event);
void spi_init(void);
void acc_init(void);

#endif // SPI_MODULE_H__