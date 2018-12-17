#include "timer.h"

void timer0_init(void)
{
    Timer_InitTypeDef Timer_InitStruct;
	
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_Timer0 , ENABLE); //��timer0ʱ��
    RCC_Timer0CLKSourceConfig(RCC_CLKSource_LIRC); //ѡ��timer0 ʱ��Դ 10K
    //RCC_Timer0CLKSourceConfig(RCC_CLKSource_HIRC); //24M
	
    Timer_InitStruct.Timer_CountMode = Timer_CountMode_Peroid; //ѡ������ģʽ
    Timer_InitStruct.Timer_IntEn = ENABLE; //ѡ�������ж�
    Timer_InitStruct.Timer_Prescale = 9; //ѡ��ʱ��Դ��Ƶϵ�� (ʵ�ʷ�Ƶ��Ϊ ����ֵ+1)
	  //Timer_InitStruct.Timer_Prescale = 23;
    Timer_InitStruct.Timer_TCMP = 20; //���ü������ֵ 5MS
    
    Timer_Init(Timer_0 , &Timer_InitStruct); //��ʼ��time0
  
	  NVIC_IRQxEnable(IRQ_TMR0); //ʹ��timer0�ж�
    NVIC_IRQPriorityConfig(IRQ_TMR0 , 1); //����timer0 �ж����ȼ�
}

//2s
//void timer1_init(void)
//{
//    Timer_InitTypeDef Timer_InitStruct;
//	
//    RCC_APBPerophClOCKCmd(RCC_APBPeriph_Timer1 , ENABLE); //��timer1ʱ��
//    RCC_Timer0CLKSourceConfig(RCC_CLKSource_LIRC); //ѡ��timer1 ʱ��Դ 
//    
//    Timer_InitStruct.Timer_CountMode = Timer_CountMode_Peroid; //ѡ������ģʽ
//    Timer_InitStruct.Timer_IntEn = ENABLE; //ѡ�������ж�
//    Timer_InitStruct.Timer_Prescale = 9; //ѡ��ʱ��Դ��Ƶϵ�� (ʵ�ʷ�Ƶ��Ϊ ����ֵ+1)
//    Timer_InitStruct.Timer_TCMP = 2000; //���ü������ֵ
//    
//    Timer_Init(Timer_1 , &Timer_InitStruct); //��ʼ��time1
//  
//	  NVIC_IRQxEnable(IRQ_TMR1); //ʹ��timer1�ж�
//    NVIC_IRQPriorityConfig(IRQ_TMR1 , 2); //����timer1 �ж����ȼ�
//}
