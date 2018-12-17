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
 
#ifndef __CSA37FX60_TIMER_H
#define __CSA37FX60_TIMER_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

typedef enum
{ 
    Timer_0 = 0x00,
    Timer_1 = 0x01,
    
}Timer_x_TypeDef;

typedef enum
{ 
    Timer_CountMode_OneShot = 0x00,
    Timer_CountMode_Peroid = 0x01,
    Timer_CountMode_Continue = 0x03,
    
}Timer_Mode_TypeDef;

typedef enum
{ 
    Timer_PeriodSel_Mode0 = 0x00,
    Timer_PeriodSel_Mode1 = 0x01,
}Timer_PeriodSel_TypeDef;


typedef struct
{
    FunctionalState Timer_IntEn;
    Timer_Mode_TypeDef Timer_CountMode;
    Timer_PeriodSel_TypeDef Timer_PeroidSel;
    uint8_t Timer_Prescale;
    uint32_t Timer_TCMP;
    
}Timer_InitTypeDef;

void Timer_Init(Timer_x_TypeDef Timer_x , Timer_InitTypeDef* Timer_InitStruct);
void Timer_Enable(Timer_x_TypeDef Timer_x);
void Timer_Disable(Timer_x_TypeDef Timer_x);
void Timer_Reset(Timer_x_TypeDef Timer_x);
uint8_t Timer_ReadWorkState(Timer_x_TypeDef Timer_x);
uint8_t Timer_ReadIEState(Timer_x_TypeDef Timer_x);
void Timer_ClearIEState(Timer_x_TypeDef Timer_x);

#endif /* __CSA37FX60_TIMER_H */





