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
 
#ifndef __CSA37FX60_I2C_H
#define __CSA37FX60_I2C_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

typedef enum
{ 
    I2C_MAT_SAR = 0x0f,
//     I2C_RX_DONE = 0x07,
    I2C_RD_REQ = 0x05,
    I2C_R_RESTART = 0x04,
    I2C_R_STOP = 0x03,
    I2C_RX_FULL = 0x02,
    I2C_R_START = 0x01,

}I2C_IntMode_TypeDef;

typedef struct
{
    uint8_t I2C_Addr;
    uint8_t I2C_RX_FIFO_Level;
    uint8_t I2C_TX_FIFO_Level;
    
}I2C_InitTypeDef;

extern uint8_t AFE0_UserSampleNum[16] ;
extern uint8_t AFE1_UserSampleNum[16] ;

void I2C_Master_Init(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Salve_Init(I2C_InitTypeDef* I2C_InitStruct);
void I2C_SendByte(uint8_t dat);
void I2C_SendMoreByte(uint8_t *dat, uint8_t num);
uint8_t I2C_RxFIFONum(void);
uint8_t I2C_ReadByte(void);
uint8_t I2C_ReadInt_Stete(I2C_IntMode_TypeDef I2C_IntMode);
void I2C_IntAllDisable(void);
void I2C_IntModeEnable(I2C_IntMode_TypeDef I2C_IntMode);
void I2C_ClearAllIntState(void);
void I2C_Enable(void);
void I2C_Disable(void);
void I2C_CleraIntState(I2C_IntMode_TypeDef I2C_IntMode);
#endif /* __CSA37FX60_I2C_H */


