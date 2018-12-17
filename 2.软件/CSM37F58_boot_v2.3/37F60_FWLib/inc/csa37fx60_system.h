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
 
#ifndef __CSA37FX60_SYSTEM_H
#define __CSA37FX60_SYSTEM_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

typedef enum
{ 
    HCLK_Div_2 = 0x00,
    HCLK_Div_4 = 0x01,
    HCLK_Div_8 = 0x02,
    HCLK_Div_16 = 0x03,
 
}TempSensorClk_TypeDef;

typedef enum
{ 
    MCU_Reset = 0x00,
    CPU_Reset = 0x01,
    Chip_Reset = 0x02,
 
}ResetMode_TypeDef;

typedef enum
{ 
    Reuse_PA2 = 0x00,
    Reuse_PA3 = 0x01,
    Reuse_PA9 = 0x02,
    Reuse_PA10 = 0x03,
    Reuse_PA11 = 0x04,
    Reuse_PA12 = 0x05,
 
}GPIO_Sel_TypeDef;

typedef enum
{ 
    GPIO_Mode = 0x00,
    UART_RXD = 0x01,
    UART_TXD = 0x02,
    I2C_SCL = 0x03,
    I2C_SDA = 0x04,
    AFE_CLK = 0x05,
    AFE_DAT = 0x06,
    SWDIO = 0x07,
    SWCLK = 0x08,
    
}GPIO_ReuseMode_TypeDef;

void Reg_WRProtDisable(void);
void Reg_WRProtEnable(void);
uint32_t System_ReadChipPDID(void);
uint32_t System_ReadChipCPUID(void);
void System_TempSensorInit( TempSensorClk_TypeDef TempSensor_Clk , FunctionalState NewState);
void System_TempSensorStartChange(void);
uint8_t System_TempSensorBusy(void);
uint16_t System_ReadTempSensorData(void);
void System_Reset(ResetMode_TypeDef Reset_Mode);
void System_SetGPIOReuse(GPIO_Sel_TypeDef GPIO_x, GPIO_ReuseMode_TypeDef Reuse_Mode);
#endif /* __CSA37FX60_SYSTEM_H */ 

