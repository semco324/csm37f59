#include "timer.h"

void timer0_init(void)
{
    Timer_InitTypeDef Timer_InitStruct;
	
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_Timer0 , ENABLE); //打开timer0时钟
    RCC_Timer0CLKSourceConfig(RCC_CLKSource_LIRC); //选择timer0 时钟源 10K
    //RCC_Timer0CLKSourceConfig(RCC_CLKSource_HIRC); //24M
	
    Timer_InitStruct.Timer_CountMode = Timer_CountMode_Peroid; //选择周期模式
    Timer_InitStruct.Timer_IntEn = ENABLE; //选择允许中断
    Timer_InitStruct.Timer_Prescale = 9; //选择时钟源分频系数 (实际分频数为 配置值+1)
	  //Timer_InitStruct.Timer_Prescale = 23;
    Timer_InitStruct.Timer_TCMP = 20; //设置计数溢出值 5MS
    
    Timer_Init(Timer_0 , &Timer_InitStruct); //初始化time0
  
	  NVIC_IRQxEnable(IRQ_TMR0); //使能timer0中断
    NVIC_IRQPriorityConfig(IRQ_TMR0 , 1); //设置timer0 中断优先级
}

//2s
//void timer1_init(void)
//{
//    Timer_InitTypeDef Timer_InitStruct;
//	
//    RCC_APBPerophClOCKCmd(RCC_APBPeriph_Timer1 , ENABLE); //打开timer1时钟
//    RCC_Timer0CLKSourceConfig(RCC_CLKSource_LIRC); //选择timer1 时钟源 
//    
//    Timer_InitStruct.Timer_CountMode = Timer_CountMode_Peroid; //选择周期模式
//    Timer_InitStruct.Timer_IntEn = ENABLE; //选择允许中断
//    Timer_InitStruct.Timer_Prescale = 9; //选择时钟源分频系数 (实际分频数为 配置值+1)
//    Timer_InitStruct.Timer_TCMP = 2000; //设置计数溢出值
//    
//    Timer_Init(Timer_1 , &Timer_InitStruct); //初始化time1
//  
//	  NVIC_IRQxEnable(IRQ_TMR1); //使能timer1中断
//    NVIC_IRQPriorityConfig(IRQ_TMR1 , 2); //设置timer1 中断优先级
//}
