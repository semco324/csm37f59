#ifndef __LED_H
#define __LED_H	 
#include "sys.h"


#define M1_LEDR PBout(0)	// PB0 R
#define M1_LEDG PBout(1)	// PB1 G

#define M1_OK()  do{M1_LEDR=0;M1_LEDG=1;}while(0)
#define M1_ERR() do{M1_LEDR=1;M1_LEDG=0;}while(0)
#define M1_NONE() do{M1_LEDR=0;M1_LEDG=0;}while(0)

void LED_Init(void);//≥ı ºªØ

		 				    
#endif
