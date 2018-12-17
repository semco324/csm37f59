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
 
#include "csa37fx60_uart.h"

/**
  * @brief  串口初始化
  * @param  UART_InitStruct : UART 初始化参数，参考uart.h
  * @retval None
  */

void UART_Init(UART_InitTypeDef* UART_InitStruct)
{
    uint32_t temp ;
    
    //设置波特率
    UART0->UARTx_LCR = 0x80 ; //解除写保护
    
    switch(UART_InitStruct->UART_BaudRate)
    {
        case BaudRate_9600 : 
        
                 UART0->UARTx_RBR_THR_DLL = 0x9C;

                UART0->UARTx_DLH_IER = 0x00;
        
            break;
        case BaudRate_19200 : 
                UART0->UARTx_RBR_THR_DLL = 0x4E;

                UART0->UARTx_DLH_IER = 0x00;    
        
            
            break;
        case BaudRate_38400 : 
            
                UART0->UARTx_RBR_THR_DLL = 0x27;
                UART0->UARTx_DLH_IER = 0x00;
                
            break;
        case BaudRate_115200 : 
                
                  UART0->UARTx_RBR_THR_DLL = 0x0d;
                UART0->UARTx_DLH_IER = 0x00;
            
            break;
        
        default:
            break;
    }
    
    UART0->UARTx_LCR = 0x00 ; //恢复写保护
    
    
    temp = 0;
    //设置收发数据位数
    temp = UART_InitStruct->UART_WordLength;
    
    //设置停止位
    if(UART_InitStruct->UART_StopBits == UART_StopBit_2)
    {
        temp |= BIT(2);
    }
    
    //设置奇偶校验
    
    if(UART_InitStruct->UART_Parity ==  UART_Parity_Even) //偶校验
    {
        temp |= BIT(5) | BIT(4) | BIT(3) ;    
    }
    else if(UART_InitStruct->UART_Parity ==  UART_Parity_Odd) //奇校验
    {
        temp |= BIT(5) | BIT(3) ;    
    }
    
    UART0->UARTx_LCR = temp;
    //设置FIFO
    temp = 0;
    
    temp = UART_InitStruct->FIFO_RCVR;
    temp <<= 6;
    
    if(UART_InitStruct->FIFO_Enable == ENABLE)
    {
        temp |= BIT(0) | BIT(1) | BIT(2); 
    }
    
    UART0->UARTx_IIR_FCR = temp;
    
    //中断设置
    if(UART_InitStruct->RIE_Enable == ENABLE) //接收数据有效中断
    {
        UART0->UARTx_DLH_IER |= BIT(0); 
    }
}

/**
  * @brief  串口发送一个字节数据
  * @param  dat : 要发送的数据
  * @retval None
  */
void UART_SendByte(uint8_t dat)
{

    UART0->UARTx_RBR_THR_DLL = dat;
    
    while(!(UART0->UARTx_USR & BIT(1))); //等待FIFO 不满

}

/**
  * @brief  串口FIFO中接收到的字节数
  * @param  None
  * @retval 收到的字节个数
  */
uint8_t UART_FIFO_ReceiveData(void)
{
    uint8_t temp;
    
    temp = UART0->UARTx_RFL & 0x0f;
    
    return temp;
}

/**
  * @brief  读取串口接收到的数据
  * @param  None
  * @retval 返回接收到的数据
  */
uint8_t UART_GetData(void)
{
    uint8_t temp;
    
    temp = UART0->UARTx_RBR_THR_DLL;
    
    return temp;
}


