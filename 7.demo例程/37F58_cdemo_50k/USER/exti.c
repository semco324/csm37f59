/****************************************
 * �ļ���  ��exti.c
 * ����    ��I/O���ж�Ӧ�ú�����         
 * ��汾  ��ST3.5.0
******************************************/
#include "exti.h"
#include "sys.h"
/*
 * ��������NVIC_Configuration
 * ����  ������Ƕ�������жϿ�����NVIC
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
void EXTI_M1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	
	/* config the extiline(PB12) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	/* EXTI line gpio config(PB12) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  EXTI_DeInit();
	/* EXTI line(PB12) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // EXTI_Trigger_Rising;
  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

/******************* (C) COPYRIGHT 2018 CHIPSEA *****END OF FILE****/

