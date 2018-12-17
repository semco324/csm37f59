#ifndef __KEY_H
#define __KEY_H
#include "csa37fx60.h"
#define KEY        GPIO_PA1

#define DRDY_KEY        GPIO_PA4

#define READ_KEY   GPIO_ReadInputDataBit(KEY)

#define READ_DRDY_KEY   GPIO_ReadInputDataBit(DRDY_KEY)

void key_init(void);

#endif


/*
1        2      4      8       IIC    DRDY    ERR     key    SDA  SCL  TX
led0   led1    led2   led3     led4   led5    led6    key     
PA7    PA6     PA5    PA4      PA0    PA8     PA2     PA1    PA9  PA10 PA3
*/
