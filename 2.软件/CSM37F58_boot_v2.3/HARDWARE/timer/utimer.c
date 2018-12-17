#include "utimer.h"
uint8_t Flag_WaitTime;

void timer0_init(void) //100ms
{
    Timer_InitTypeDef Timer_InitStruct;
    
    NVIC_IRQxEnable(IRQ_TMR0);  //����Timer0 �ж�ʹ��
    NVIC_IRQPriorityConfig(IRQ_TMR0 , 1);  //����Timer0 �ж����ȼ�
    
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_Timer0 , ENABLE); //ʹ��Timer0 ʱ��
    RCC_Timer0CLKSourceConfig(RCC_CLKSource_LIRC); //����Timer0 ʱ��Դ 10KHz
    
    //
    Timer_InitStruct.Timer_CountMode = Timer_CountMode_Peroid; //���ڼ���ģʽ
    Timer_InitStruct.Timer_IntEn = ENABLE; //�����ж�
    Timer_InitStruct.Timer_Prescale = 9; //ʱ��Դ��Ƶϵ�� 
    Timer_InitStruct.Timer_TCMP = 100; //����ֵ
    
    Timer_Init(Timer_0 , &Timer_InitStruct); //��ʼ��
    
//    Timer_Enable(Timer_0); //ʹ�ܣ���ʼ����
}

