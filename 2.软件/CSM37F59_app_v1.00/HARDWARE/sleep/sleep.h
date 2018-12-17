#ifndef __SLEEP_H
#define __SLEEP_H

#include "csa37fx60.h"
#include "wdt.h"
#include "addr_map.h"
#include "CS1258.h"
#include "hw_iic.h"
#include "timer.h" 

extern uint8_t addr_mat;



#define SLEEP_TIME 2000

void check_sleep(void); 
void no_use_peripherals(void);
#endif

