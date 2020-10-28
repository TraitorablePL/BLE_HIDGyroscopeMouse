
#ifndef CUSTOM_BOARD_H
#define CUSTOM_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

//********************************************LEDS FOR MOTHER BOARD********************************************
// LEDs definitions for NRF51822_XXAC
 #define LEDS_NUMBER    5

#define LED_START      18
#define LED_1          18
#define LED_2          19
#define LED_3          20
#define LED_4          21
#define LED_5          22
#define LED_STOP       22

#define LEDS_ACTIVE_STATE 0
	
#define LEDS_LIST { LED_1, LED_2, LED_3, LED_4, LED_5 }

#define BSP_LED_0      LED_1
#define BSP_LED_1      LED_2
#define BSP_LED_2      LED_3
#define BSP_LED_3      LED_4
#define BSP_LED_4      LED_5

#define BSP_LED_0_MASK (1<<BSP_LED_0)
#define BSP_LED_1_MASK (1<<BSP_LED_1)
#define BSP_LED_2_MASK (1<<BSP_LED_2)
#define BSP_LED_3_MASK (1<<BSP_LED_3)
#define BSP_LED_4_MASK (1<<BSP_LED_4)

#define LEDS_MASK      (BSP_LED_0_MASK | BSP_LED_1_MASK | BSP_LED_2_MASK | BSP_LED_3_MASK | BSP_LED_4_MASK)
///* all LEDs are lit when GPIO is low */
#define LEDS_INV_MASK  ~LEDS_MASK
//****************************************END LEDS FOR MOTHER BOARD****************************************

//********************************************LEDS FOR ADARFUIT********************************************
//#define LEDS_NUMBER    2

//#define LED_START      18
//#define LED_1          18
//#define LED_2          19
//#define LED_STOP       19

//#define LEDS_ACTIVE_STATE 0

//#define LEDS_LIST { LED_1, LED_2 }

//#define BSP_LED_0      LED_1
//#define BSP_LED_1      LED_2

//#define BSP_LED_0_MASK (1<<BSP_LED_0)
//#define BSP_LED_1_MASK (1<<BSP_LED_1)

//#define LEDS_MASK      (BSP_LED_0_MASK | BSP_LED_1_MASK)
/////* all LEDs are lit when GPIO is low */
//#define LEDS_INV_MASK  LEDS_MASK
//***************************************END LEDS FOR ADARFUIT********************************************

//**************************************BUTTON FOR MOTHER BOARD*******************************************
#define BUTTONS_NUMBER 2

#define BUTTON_START   16
#define BUTTON_1       16
#define BUTTON_2       17
#define BUTTON_STOP    17
#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

#define BUTTONS_LIST { BUTTON_1, BUTTON_2 }

#define BSP_BUTTON_0   BUTTON_1
#define BSP_BUTTON_1   BUTTON_2

#define BSP_BUTTON_0_MASK (1<<BSP_BUTTON_0)
#define BSP_BUTTON_1_MASK (1<<BSP_BUTTON_1)

#define BUTTONS_MASK   (BSP_BUTTON_0_MASK | BSP_BUTTON_1_MASK) //0x001E0000
//************************************END BUTTON FOR MOTHER BOARD*******************************************

//****************************************BUTTON FOR ADAFRUIT***********************************************
//#define BUTTONS_NUMBER 1

//#define BUTTON_START   7
//#define BUTTON_1       7
//#define BUTTON_STOP    7
//#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

//#define BUTTONS_ACTIVE_STATE 0

//#define BUTTONS_LIST { BUTTON_1 }

//#define BSP_BUTTON_0   BUTTON_1

//#define BSP_BUTTON_0_MASK (1<<BSP_BUTTON_0)

//#define BUTTONS_MASK   (BSP_BUTTON_0_MASK) //0x001E0000
//************************************END BUTTON FOR ADAFRUIT*******************************************

//#define RX_PIN_NUMBER  9
//#define TX_PIN_NUMBER  11
//#define CTS_PIN_NUMBER 8
//#define RTS_PIN_NUMBER 10
//#define HWFC           true

#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  9
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8
#define HWFC           true


#define SPIM0_SCK_PIN       25     /**< SPI clock GPIO pin number. */
#define SPIM0_MOSI_PIN      24     /**< SPI Master Out Slave In GPIO pin number. */
#define SPIM0_MISO_PIN      23     /**< SPI Master In Slave Out GPIO pin number. */
#define SPIM0_SS_PIN        1      /**< SPI Slave Select GPIO pin number.  30*/

#define SCL_PIN             1     // SCL signal pin
#define SDA_PIN             0     // SDA signal pin

// serialization APPLICATION board
#define SER_CONN_CHIP_RESET_PIN     30    // Pin used to reset connectivity chip


////Left ARDUINO for easy compilation
//#define ARDUINO_SCL_PIN             1     // SCL signal pin
//#define ARDUINO_SDA_PIN             0    // SDA signal pin
//#define SCL_PIN             		1     // SCL signal pin
//#define SDA_PIN             		0    // SDA signal pin



// Low frequency clock source to be used by the SoftDevice
//#define NRF_CLOCK_LFCLKSRC      NRF_CLOCK_LFCLKSRC_XTAL_20_PPM
//s210

//#ifdef S130
//#define NRF_CLOCK_LFCLKSRC      NRF_CLOCK_LFCLKSRC_XTAL_20_PPM
//#else
#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 0,                                \
                                 .rc_temp_ctiv  = 0,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}
//#endif

#ifdef __cplusplus
}
#endif

#endif // NRF51822_XXAC
