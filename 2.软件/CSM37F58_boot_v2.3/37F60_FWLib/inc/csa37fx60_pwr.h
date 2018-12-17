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
 
#ifndef __CSA37FX60_PWR_H
#define __CSA37FX60_PWR_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

typedef enum
{ 
    WFI_Mode = 0x00,
    WFE_Mode = 0x01,
   
}PWR_WFMode_TypeDef;

typedef enum
{ 
    Sleep_Mode = 0x00,
    DeepSleep_Mode1 = 0x01,
    DeepSleep_Mode2 = 0x02,
    PowerDown_Mode = 0x03,
   
}PWR_SleepMode_TypeDef;

typedef struct
{
    PWR_SleepMode_TypeDef Mode;
    FunctionalState WakeUp_IntEn;
    FunctionalState WakeUp_DelayEn;
    
}PWR_DeepSleep_InitTypeDef;

void PWR_SetBackUp(uint32_t backup_data);
void PWR_EnterSleepMode(PWR_DeepSleep_InitTypeDef* PWR_InitStruct, PWR_WFMode_TypeDef WF_Mode);

#endif /* __CSA37FX60_PWR_H */



































