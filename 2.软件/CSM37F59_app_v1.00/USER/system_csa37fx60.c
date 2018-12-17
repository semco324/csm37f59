/**
  ******************************************************************************
  * @file    system_csa37fx60.c
  * @author  chipsea Application Team
  * @version 
  * @date    08-April-2011
  * @brief   
  * @attention
  */
#include "csa37fx60.h"

#include "csa37fx60_conf.h"

/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
	//Ĭ����ʹ��24MHZ���ٶ�ʱ�Ӻ�10KHz����,
	RCC_InsideRCCmd(RCC_InsideRC_HIRC|RCC_InsideRC_LIRC, ENABLE);
	
	//PCLK HCLK��Ƶ����
	RCC_PCLKConfig(0); //PCLK ʱ��Ƶ�� = PCLK ʱ��Դ / ( CLKDiv +1 )
	RCC_HCLKConfig(0); //HCLK ʱ��Ƶ�� = HCLK ʱ��Դ / 1 
	
	//�ж�ʱ���Ƿ��������ȶ�
	while(!RCC_GetClkStatus(RCC_CLKState_HIRC));
	while(!RCC_GetClkStatus(RCC_CLKState_LIRC));
	
	//ϵͳѡ��ʱ��Դ
	RCC_HCLKSourceConfig(RCC_CLKSource_HIRC,RCC_HCLKDIV_1);//HCLKѡ��24MHz 1����Ƶ
	RCC_SysTickCLKSourceConfig(RCC_CLKSource_HIRC_Div2);        //STCLKѡ��HIRC/2 12Mhz
 
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
