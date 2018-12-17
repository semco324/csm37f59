#include "uart.h" 

/**
  * @brief  ���ڳ�ʼ��
  * @param  None
  * @retval None
  */
void User_UART0_Init(void)
{
    UART_InitTypeDef UART_InitStruct;
    
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_UART , ENABLE); //�򿪴���ʱ��
    RCC_UARTCLKSourceConfig(RCC_CLKSource_HIRC2 , 0); //ѡ�񴮿�ʱ��Դ���Ƶϵ��
    
    NVIC_IRQxEnable(IRQ_UART); //ʹ�ܴ����ж�
    
    UART_InitStruct.UART_BaudRate = BaudRate_115200; //���ò�����
    UART_InitStruct.UART_Parity = UART_Parity_No; //��У��
    UART_InitStruct.UART_WordLength = UART_WordLength_8bit; //���ݳ���
    UART_InitStruct.UART_StopBits = UART_StopBit_1; //ֹͣλ
    
    UART_InitStruct.FIFO_Enable = ENABLE; //ʹ��FIFO
    UART_InitStruct.FIFO_RCVR = FIFO_OneData; //FIFO�����ж� ���ݸ���
    UART_InitStruct.RIE_Enable = DISABLE; //�رս����ж�
    
    System_SetGPIOReuse(Reuse_PA10,UART_RXD); //����PA10Ϊ rx
    System_SetGPIOReuse(Reuse_PA9,UART_TXD); //����PA9Ϊ tx
    
    UART_Init(&UART_InitStruct); //��ʼ�����ڲ�ʹ��
}

//void UART_SendByte(uint8_t dat)
//
//
