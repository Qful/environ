#ifndef __WS2812B_H
#define	__WS2812B_H

#include "map.h"


void WS2812_init(void);
void WS2812_send(uint8_t (*color)[3], uint16_t len);

#endif /* __LED_H */
