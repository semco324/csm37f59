#ifndef __TEST_CSM_H
#define __TEST_CSM_H

#include "stm32f10x.h"
#include "myiic.h"
#include "key.h"
#include "lcd.h"
#include "led.h"
#include "led.h"
#include "delay.h"
#define DRDY1_GPIOX  GPIOB
#define DRDY1_CLOCK  RCC_APB2Periph_GPIOB
#define DRDY1_PIN    GPIO_Pin_12

#define RESET1_GPIOX  GPIOB
#define RESET1_CLOCK  RCC_APB2Periph_GPIOB
#define RESET1_PIN    GPIO_Pin_13

#define CE1_GPIOX  GPIOE
#define CE1_CLOCK  RCC_APB2Periph_GPIOE
#define CE1_PIN    GPIO_Pin_15

#define READ_DRDY1() GPIO_ReadInputDataBit(DRDY1_GPIOX,DRDY1_PIN) //

void DRDY_Init(void);
void check_pre(void);
void measure(void);
void dis_part(void);
void get_result(void);
#endif
