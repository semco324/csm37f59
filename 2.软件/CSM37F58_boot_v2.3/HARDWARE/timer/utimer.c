#include "utimer.h"
uint8_t Flag_WaitTime;

void timer0_init(void) //100ms
{
    Timer_InitTypeDef Timer_InitStruct;
    
    NVIC_IRQxEnable(IRQ_TMR0);  //设置Timer0 中断使能
    NVIC_IRQPriorityConfig(IRQ_TMR0 , 1);  //设置Timer0 中断优先级
    
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_Timer0 , ENABLE); //使能Timer0 时钟
    RCC_Timer0CLKSourceConfig(RCC_CLKSource_LIRC); //设置Timer0 时钟源 10KHz
    
    //
    Timer_InitStruct.Timer_CountMode = Timer_CountMode_Peroid; //周期计数模式
    Timer_InitStruct.Timer_IntEn = ENABLE; //允许中断
    Timer_InitStruct.Timer_Prescale = 9; //时钟源分频系数 
    Timer_InitStruct.Timer_TCMP = 100; //计数值
    
    Timer_Init(Timer_0 , &Timer_InitStruct); //初始化
    
//    Timer_Enable(Timer_0); //使能，开始计数
}

