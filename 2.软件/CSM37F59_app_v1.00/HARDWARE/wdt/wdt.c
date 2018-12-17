#include "wdt.h"

/**
  * @brief  wdt ��ʼ�� 409.6ms �ж�
  * @param  None
  * @retval None
  */
void User_WDT_Init(void)
{
    WDT_InitTypeDef WDT_InitStruct; 
    
//    NVIC_IRQxEnable(IRQ_WDT_WWDT); //ʹ��wdt�ж�
    
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_WDT , ENABLE); //��wdtʱ��Դ
    RCC_WDTCLKSourceConfig(RCC_CLKSource_LIRC); //ѡ��wdtʱ��Դ

    WDT_InitStruct.WDT_PeriodTime = WDT_PeriodTime_2q18;//WDT_PeriodTime_2q12; //���ü������� 409.6 ms
    WDT_InitStruct.WDT_Int_Enable = DISABLE; //�����ж�
	  WDT_InitStruct.WDT_IntWakeUp_Enable= DISABLE; //������
    WDT_InitStruct.WDT_ReSystem_Enable = ENABLE; //����λϵͳ
    WDT_InitStruct.WDT_DelayTime = WDT_DelayTime_130CLK; //��λ��ʱʱ��
    WDT_InitStruct.WDT_Enable = ENABLE; //ʹ��
    
    WDT_Init(&WDT_InitStruct); //��ʼ��wdt
    
}


void User_WDT_DISABLE(void)
{
    WDT_InitTypeDef WDT_InitStruct; 
    
    NVIC_IRQxEnable(IRQ_WDT_WWDT); //ʹ��wdt�ж�
    
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_WDT , ENABLE); //��wdtʱ��Դ
    RCC_WDTCLKSourceConfig(RCC_CLKSource_LIRC); //ѡ��wdtʱ��Դ

    WDT_InitStruct.WDT_PeriodTime = WDT_PeriodTime_2q18;//WDT_PeriodTime_2q12; //���ü������� 409.6 ms
    WDT_InitStruct.WDT_Int_Enable = DISABLE; //�����ж�
	  WDT_InitStruct.WDT_IntWakeUp_Enable= DISABLE; //������
    WDT_InitStruct.WDT_ReSystem_Enable = DISABLE; //����λϵͳ
    WDT_InitStruct.WDT_DelayTime = WDT_DelayTime_130CLK; //��λ��ʱʱ��
    WDT_InitStruct.WDT_Enable = DISABLE; //ʹ��
    
    WDT_Init(&WDT_InitStruct); //��ʼ��wdt
    
}
