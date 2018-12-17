
#ifndef __UDELAY_H
#define __UDELAY_H

#include "csa37fx60.h"

#define SysTickClock   24000000  

void delay_init(void);
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);

#endif

