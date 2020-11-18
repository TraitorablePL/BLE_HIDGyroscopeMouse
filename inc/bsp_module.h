#ifndef BSP_MODULE_H__
#define BSP_MODULE_H__
#include "bsp.h"

void bsp_event_handler(bsp_event_t event);
void buttons_leds_init(bool * p_erase_bonds);

#endif // BSP_MODULE_H__