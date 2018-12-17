#ifndef __UIIC__H
#define __UIIC__H

#include "csa37fx60.h"

#define  DRDY_IO   GPIO_PA8

//设置 DRDY输出
#define  SetDRDYOutput(DRDY_IO)	   	  GPIO_SetMode(DRDY_IO,GPIO_Mode_OUTPUT)
//设置 DRDY输出高低
#define  SetDRDY(a)	   	              GPIO_WriteBits(DRDY_IO,a)

typedef enum 
{		
	TRUE = 0, 
	FALSE =1,
}BOOL;

void User_IIC_Init(void);
#endif
