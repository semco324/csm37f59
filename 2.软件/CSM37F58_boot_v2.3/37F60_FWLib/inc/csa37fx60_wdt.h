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
 
#ifndef __CSA37FX60_WDT_H
#define __CSA37FX60_WDT_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

typedef enum
{ 
    WDT_PeriodTime_2q4 = 0x00,
    WDT_PeriodTime_2q6 = 0x01,
    WDT_PeriodTime_2q8 = 0x02,
    WDT_PeriodTime_2q10 = 0x03,
    WDT_PeriodTime_2q12 = 0x04,
    WDT_PeriodTime_2q14 = 0x05,
    WDT_PeriodTime_2q16 = 0x06,
    WDT_PeriodTime_2q18 = 0x07,
    
}WDT_Period_TypeDef;

typedef enum
{ 
    WDT_State_WakeUp = 0x00,
    WDT_State_Int = 0x01,
    WDT_State_ReSystem = 0x02,
    
}WDT_State_TypeDef;

typedef enum
{ 
    WDT_DelayTime_1026CLK = 0x00,
    WDT_DelayTime_130CLK = 0x01,
    WDT_DelayTime_18CLK = 0x02,
    WDT_DelayTime_3CLK = 0x03,
    
}WDT_DelayTime_TypeDef;

typedef struct
{
    WDT_Period_TypeDef WDT_PeriodTime;    //看门狗超时周期
    FunctionalState WDT_Enable;            //看门狗使能
    FunctionalState WDT_Int_Enable;        //看门狗超时中断使能
    FunctionalState WDT_IntWakeUp_Enable;  //看门狗中断唤醒CPU使能
    FunctionalState WDT_ReSystem_Enable;   //看门狗超时复位使能
    WDT_DelayTime_TypeDef WDT_DelayTime;   //复位延迟时间
    
}WDT_InitTypeDef;



void WDT_Init(WDT_InitTypeDef* WDT_InitStruct);
uint8_t WDT_StateRead(WDT_State_TypeDef WDT_State);
void WDT_StateClear(WDT_State_TypeDef WDT_State);
void WDT_TimeReload(void);

#endif /* __CSA37FX60_WDT_H */

