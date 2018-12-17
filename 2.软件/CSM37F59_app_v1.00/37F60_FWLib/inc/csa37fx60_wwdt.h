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
 
#ifndef __CSA37FX60_WWDT_H
#define __CSA37FX60_WWDT_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

typedef enum
{ 
    WWDT_CLK_Div_1 = 0x00,
    WWDT_CLK_Div_2 = 0x01,
    WWDT_CLK_Div_4 = 0x02,
    WWDT_CLK_Div_8 = 0x03,
    WWDT_CLK_Div_16 = 0x04,
    WWDT_CLK_Div_32 = 0x05,
    WWDT_CLK_Div_64 = 0x06,
    WWDT_CLK_Div_128 = 0x07,
    WWDT_CLK_Div_192 = 0x08,
    WWDT_CLK_Div_256 = 0x09,
    WWDT_CLK_Div_384 = 0x0A,
    WWDT_CLK_Div_512 = 0x0B,
    WWDT_CLK_Div_768 = 0x0C,
    WWDT_CLK_Div_1024 = 0x0D,
    WWDT_CLK_Div_1536 = 0x0E,
    WWDT_CLK_Div_2048 = 0x0F,
    
}WWDT_CLK_TypeDef;

typedef struct
{
    uint8_t WWDT_CMPData;
    WWDT_CLK_TypeDef WWDT_PeriodSel;
    FunctionalState WWDT_CMP_INT;
    FunctionalState WWDT_Enable;
    
}WWDT_InitTypeDef;

void WWDT_Init(WWDT_InitTypeDef* WWDT_InitStruct);
uint8_t WWDT_TimeReload(void);
uint8_t WWDT_IEState_CMP(void);
void WWDT_ClearState_CMP(void);
uint8_t WWDT_IEState_OverTime(void);
void WWDT_ClearState_OverTime(void);

#endif /* __CSA37FX60_WWDT_H */

