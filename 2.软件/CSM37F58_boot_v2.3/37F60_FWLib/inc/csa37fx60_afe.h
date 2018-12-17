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
 
#ifndef __CSA37FX60_AFE_H
#define __CSA37FX60_AFE_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

#define FAST_DAC_ADJUST 0 //快速校准

typedef enum
{ 
    AFE_SingleMode = 0x00,
    AFE_SingleCycleMode = 0x01,
    AFE_FiniteCycleMode1 = 0x02,
    AFE_FiniteCycleMode2 = 0x03,
    AFE_InfiniteCycleMode = 0x04,
    AFE_FIFOMode = 0x05,    
    
}AFE_ScanMode_TypeDef;

typedef enum
{ 
    AFE_PGA1_Gain_1 = 0x00,
    AFE_PGA1_Gain_16 = 0x01,
    AFE_PGA1_Gain_32 = 0x02,
    AFE_PGA1_Gain_64 = 0x03,
    AFE_PGA1_Gain_128 = 0x04,
    AFE_PGA1_Gain_256 = 0x05, 
    
}AFE_PGA1_TypeDef;

typedef enum
{ 
    AFE_PGA2_Gain_1 = 0x00,
    AFE_PGA2_Gain_2 = 0x01,
    AFE_PGA2_Gain_3 = 0x02,
    AFE_PGA2_Gain_4 = 0x03,
    AFE_PGA2_Gain_5 = 0x04,
    AFE_PGA2_Gain_6 = 0x05, 
    AFE_PGA2_Gain_7 = 0x06, 
    AFE_PGA2_Gain_8 = 0x07, 
    
}AFE_PGA2_TypeDef;

typedef enum
{ 
    Time_ADCClock_1 = 0x00,
    Time_ADCClock_2 = 0x01,
    Time_ADCClock_4 = 0x02,
    Time_ADCClock_8 = 0x03,
    Time_ADCClock_16 = 0x04,
    Time_ADCClock_32 = 0x05,
    Time_ADCClock_64 = 0x06,
    Time_ADCClock_128 = 0x07,
    
}AFE_x_SampleTime_TypeDef;

typedef enum
{ 
    Vaild_Num_2 = 0x00,
    Vaild_Num_4 = 0x01,
    Vaild_Num_8 = 0x02,
    Vaild_Num_16 = 0x03,
    Vaild_Num_32 = 0x04,
    Vaild_Num_64 = 0x05,
    Vaild_Num_128 = 0x06,
    Vaild_Num_256 = 0x07,
    
}AFE_x_VaildNum_TypeDef;

typedef enum
{ 
    All_Avg = 0x00,
    Mid_Avg = 0x01,
    
}AFE_x_CycleMode1_AvgMode_TypeDef;

typedef enum
{ 
    VS_26 = 0x00,
    VS_28 = 0x01,
    VS_30 = 0x02,
    VS_45 = 0x03,
    
}AFE_VS_TypeDef;

typedef struct
{
    AFE_ScanMode_TypeDef AFE_ScanMode;
    FunctionalState AFE_IntEn;
    
    FunctionalState AFE_PGAEn;
    AFE_PGA1_TypeDef PGA1_Gain;
    AFE_PGA2_TypeDef PGA2_Gain;
    
    AFE_x_SampleTime_TypeDef AFE_SampleTime;
    
    uint8_t CycleMode1_unVaildNum;
    AFE_x_VaildNum_TypeDef CycleMode_VaildNum;
    
    AFE_x_CycleMode1_AvgMode_TypeDef Avg_Mode;
    
    AFE_VS_TypeDef VS_Sel;
    
    uint16_t AFEx_SampleChannel;
}AFE_InitTypeDef;

extern uint16_t AFE0_DAC_AdjData[16];
extern uint16_t AFE1_DAC_AdjData[16];

extern uint16_t AFE0_SampleData[16];
extern uint16_t AFE1_SampleData[16];

void AFE_Init(AFE_TypeDef *AFEx , AFE_InitTypeDef* AFE_InitStruct);
void AFEx_StartADScan(AFE_TypeDef* AFEx);
uint8_t AFEx_CheckADFinish(AFE_TypeDef *AFEx);
void AFEx_ADPowerOpen(AFE_TypeDef *AFEx);
void AFEx_ADPowerClose(AFE_TypeDef *AFEx);
void AFEx_SetDACData(AFE_TypeDef *AFEx, uint16_t *dac_AdjData);
uint8_t AFEx_ReadSampleData(AFE_TypeDef *AFEx, uint8_t AFEx_Channelx, uint16_t *dat);
void AFEx_DAC_Adjust(AFE_TypeDef *AFEx);
void AFEx_DAC_AdjustFast(AFE_TypeDef *AFEx);

#endif /* __CSA37FX60_AFE_H */








