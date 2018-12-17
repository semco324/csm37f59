#ifndef __LED_H
#define __LED_H

#include "csa37fx60.h"

#define  LED0   GPIO_PA7
#define  LED1   GPIO_PA6
#define  LED2   GPIO_PA5
//#define  LED3   GPIO_PA4

#define  DRDY   GPIO_PA8

#define  ERR    GPIO_PA2

#define  IIC    GPIO_PA0

#define  LED_Bit0()		do{GPIO_WriteBits(LED0|LED1|LED2,0);}while(0);
#define  LED_Bit1()		do{LED_Bit0() GPIO_WriteBits(LED0,1);}while(0);
#define  LED_Bit2()   do{LED_Bit0() GPIO_WriteBits(LED1,1);}while(0);
#define  LED_Bit3()   do{LED_Bit0() GPIO_WriteBits(LED0|LED1,1);}while(0);
#define  LED_Bit4()   do{LED_Bit0() GPIO_WriteBits(LED2,1);}while(0);
#define  LED_Bit5()   do{LED_Bit0() GPIO_WriteBits(LED2|LED0,1);}while(0);
#define  LED_Bit6()   do{LED_Bit0() GPIO_WriteBits(LED2|LED1,1);}while(0);
#define  LED_Bit7()   do{LED_Bit0() GPIO_WriteBits(LED2|LED1|LED0,1);}while(0);

#define  SET_DRDY(x)  GPIO_WriteBits(DRDY,x); 

#define  SET_ERR(x)   GPIO_WriteBits(ERR,x); 

#define  SET_IIC(x)   GPIO_WriteBits(IIC,x); 


void led_init(void);
#endif
