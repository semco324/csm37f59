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
  * @brief  ���ڳ�ʼ��
  * @param  UART_InitStruct : UART ��ʼ���������ο�uart.h
  * @retval None
  */

void UART_Init(UART_InitTypeDef* UART_InitStruct)
{
    uint32_t temp ;
    
    //���ò�����
    UART0->UARTx_LCR = 0x80 ; //���д����
    
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
    
    UART0->UARTx_LCR = 0x00 ; //�ָ�д����
    
    
    temp = 0;
    //�����շ�����λ��
    temp = UART_InitStruct->UART_WordLength;
    
    //����ֹͣλ
    if(UART_InitStruct->UART_StopBits == UART_StopBit_2)
    {
        temp |= BIT(2);
    }
    
    //������żУ��
    
    if(UART_InitStruct->UART_Parity ==  UART_Parity_Even) //żУ��
    {
        temp |= BIT(5) | BIT(4) | BIT(3) ;    
    }
    else if(UART_InitStruct->UART_Parity ==  UART_Parity_Odd) //��У��
    {
        temp |= BIT(5) | BIT(3) ;    
    }
    
    UART0->UARTx_LCR = temp;
    //����FIFO
    temp = 0;
    
    temp = UART_InitStruct->FIFO_RCVR;
    temp <<= 6;
    
    if(UART_InitStruct->FIFO_Enable == ENABLE)
    {
        temp |= BIT(0) | BIT(1) | BIT(2); 
    }
    
    UART0->UARTx_IIR_FCR = temp;
    
    //�ж�����
    if(UART_InitStruct->RIE_Enable == ENABLE) //����������Ч�ж�
    {
        UART0->UARTx_DLH_IER |= BIT(0); 
    }
}

/**
  * @brief  ���ڷ���һ���ֽ�����
  * @param  dat : Ҫ���͵�����
  * @retval None
  */
void UART_SendByte(uint8_t dat)
{

    UART0->UARTx_RBR_THR_DLL = dat;
    
    while(!(UART0->UARTx_USR & BIT(1))); //�ȴ�FIFO ����

}

/**
  * @brief  ����FIFO�н��յ����ֽ���
  * @param  None
  * @retval �յ����ֽڸ���
  */
uint8_t UART_FIFO_ReceiveData(void)
{
    uint8_t temp;
    
    temp = UART0->UARTx_RFL & 0x0f;
    
    return temp;
}

/**
  * @brief  ��ȡ���ڽ��յ�������
  * @param  None
  * @retval ���ؽ��յ�������
  */
uint8_t UART_GetData(void)
{
    uint8_t temp;
    
    temp = UART0->UARTx_RBR_THR_DLL;
    
    return temp;
}


