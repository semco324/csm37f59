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
 
#ifndef __CSA37FX60_UART_H
#define __CSA37FX60_UART_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

typedef enum
{ 
    UART_Parity_No = 0x00,
    UART_Parity_Even = 0x01,  //偶校验
    UART_Parity_Odd = 0x02,  //奇校验
    
}UART_ParityMode_TypeDef;

typedef enum
{ 
    BaudRate_9600 = 0x00,
    BaudRate_19200 = 0x01,
    BaudRate_38400 = 0x02,
    BaudRate_115200 = 0x03,
    
}UART_BAUDRATE_TypeDef;

typedef enum
{ 
    UART_WordLength_5bit = 0x00,
    UART_WordLength_6bit = 0x01,
    UART_WordLength_7bit = 0x02,
    UART_WordLength_8bit = 0x03
    
}UART_WordLength_TypeDef;

typedef enum
{ 
    UART_StopBit_1 = 0x00, 
    UART_StopBit_2 = 0x01,
    
}UART_StopBit_TypeDef;

typedef enum
{ 
    FIFO_OneData = 0x00,
    FIFO_QuarterData = 0x01,
    FIFO_HalfData = 0x02,
    FIFO_FastFull = 0x03,
    
}UART_FIFORState_TypeDef;

typedef struct
{
    UART_BAUDRATE_TypeDef UART_BaudRate;
    UART_WordLength_TypeDef UART_WordLength;
    UART_StopBit_TypeDef UART_StopBits;
    UART_ParityMode_TypeDef UART_Parity;

    FunctionalState FIFO_Enable;  
    UART_FIFORState_TypeDef FIFO_RCVR; 
    FunctionalState RIE_Enable;  //接收数据有效中断
    
}UART_InitTypeDef;

void UART_Init(UART_InitTypeDef* UART_InitStruct);
void UART_SendByte(uint8_t dat);
uint8_t UART_FIFO_ReceiveData(void);
uint8_t UART_GetData(void);

#endif /* __CSA37FX60_GPIO_H */



































