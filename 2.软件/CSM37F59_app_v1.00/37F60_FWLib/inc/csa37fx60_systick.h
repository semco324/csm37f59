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
 
#ifndef __CSA37FX60_SYSTICK_H
#define __CSA37FX60_SYSTICK_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

typedef struct
{
    FunctionalState SysTick_IEEnable;
    uint32_t SysTick_Reload;

}SysTick_InitTypeDef;

void SysTick_Init(SysTick_InitTypeDef* SysTick_InitStruct);
void SysTick_Enable(void);
void SysTick_Disable(void);

#endif /* __CSA37FX60_SYSTEM_H */ 

