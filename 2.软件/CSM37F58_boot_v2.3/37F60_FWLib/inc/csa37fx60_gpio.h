/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from  CHIPSEA.
 *
 *            (C) COPYRIGHT 2015 SHENZHEN CHIPSEA TECHNOLOGIES CO.,LTD.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from CHIPSEA.
 *
 *      Release Information : CSA37FX60 
 *-----------------------------------------------------------------------------
 */
 
#ifndef __CSA37FX60_GPIO_H
#define __CSA37FX60_GPIO_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

#define GPIO_PA0 0x0001
#define GPIO_PA1 0x0002
#define GPIO_PA2 0x0004
#define GPIO_PA3 0x0008
#define GPIO_PA4 0x0010
#define GPIO_PA5 0x0020
#define GPIO_PA6 0x0040
#define GPIO_PA7 0x0080
#define GPIO_PA8 0x0100
#define GPIO_PA9 0x0200
#define GPIO_PA10 0x0400
#define GPIO_PA11 0x0800
#define GPIO_PA12 0x1000 

typedef enum
{ 
    GPIO_Mode_OUTPUT = 0x01,
    GPIO_Mode_INPUT = 0x00,
}GPIOMode_TypeDef;



void GPIO_SetMode(uint16_t GPIO_Pin , GPIOMode_TypeDef GPIO_Mode);
void GPIO_WriteBits(uint16_t GPIO_Pin , uint8_t is_high);
uint8_t GPIO_ReadInputDataBit(uint16_t GPIO_Pin);
uint8_t GPIO_ReadOutputDataBit(uint16_t GPIO_Pin);
void GPIO_CloseInputChannel(uint16_t GPIO_Pin);
void GPIO_OpenInputChannel(uint16_t GPIO_Pin);
void GPIO_DisWriteOutput(uint16_t GPIO_Pin);
void GPIO_EnWriteOutput(uint16_t GPIO_Pin);
void GPIO_EnPullUp(uint16_t GPIO_Pin);
void GPIO_DisPullUp(uint16_t GPIO_Pin);
void GPIO_EnTYP(uint16_t GPIO_Pin);
void GPIO_DisTYP(uint16_t GPIO_Pin);

#endif /* __CSA37FX60_GPIO_H */

