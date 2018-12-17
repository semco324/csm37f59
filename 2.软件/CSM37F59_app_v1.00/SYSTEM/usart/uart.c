#include "uart.h" 

/**
  * @brief  串口初始化
  * @param  None
  * @retval None
  */
void User_UART0_Init(void)
{
    UART_InitTypeDef UART_InitStruct;
    
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_UART , ENABLE); //打开串口时钟
    RCC_UARTCLKSourceConfig(RCC_CLKSource_HIRC2 , 0); //选择串口时钟源与分频系数
    
    NVIC_IRQxEnable(IRQ_UART); //使能串口中断
    
    UART_InitStruct.UART_BaudRate = BaudRate_115200; //设置波特率
    UART_InitStruct.UART_Parity = UART_Parity_No; //无校验
    UART_InitStruct.UART_WordLength = UART_WordLength_8bit; //数据长度
    UART_InitStruct.UART_StopBits = UART_StopBit_1; //停止位
    
    UART_InitStruct.FIFO_Enable = ENABLE; //使能FIFO
    UART_InitStruct.FIFO_RCVR = FIFO_OneData; //FIFO接受中断 数据个数
    UART_InitStruct.RIE_Enable = DISABLE; //关闭接受中断
    
    System_SetGPIOReuse(Reuse_PA10,UART_RXD); //设置PA10为 rx
    System_SetGPIOReuse(Reuse_PA9,UART_TXD); //设置PA9为 tx
    
    UART_Init(&UART_InitStruct); //初始化串口并使能
}

//void UART_SendByte(uint8_t dat)
//
//
