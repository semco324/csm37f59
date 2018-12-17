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
	//默认是使能24MHZ高速度时钟和10KHz震荡器,
	RCC_InsideRCCmd(RCC_InsideRC_HIRC|RCC_InsideRC_LIRC, ENABLE);
	
	//PCLK HCLK分频设置
	RCC_PCLKConfig(0); //PCLK 时钟频率 = PCLK 时钟源 / ( CLKDiv +1 )
	RCC_HCLKConfig(0); //HCLK 时钟频率 = HCLK 时钟源 / 1 
	
	//判断时钟是否开启并且稳定
	while(!RCC_GetClkStatus(RCC_CLKState_HIRC));
	while(!RCC_GetClkStatus(RCC_CLKState_LIRC));
	
	//系统选择时钟源
	RCC_HCLKSourceConfig(RCC_CLKSource_HIRC,RCC_HCLKDIV_1);//HCLK选择24MHz 1不分频
	RCC_SysTickCLKSourceConfig(RCC_CLKSource_HIRC_Div2);        //STCLK选择HIRC/2 12Mhz
 
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
