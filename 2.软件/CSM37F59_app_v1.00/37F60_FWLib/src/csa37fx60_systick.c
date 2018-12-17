/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from  CHIPSEA.
 *
 *            (C) COPYRIGHT 2015 SHENZHEN CHIPSEA TECHNOLOGIES CO.,LTD.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from CHIPSEA.
 *
 *      Release Information : CSA37FX60 
 *-----------------------------------------------------------------------------
 */
 
#include "csa37fx60_systick.h"

/**
  * @brief  SysTick 系统定时器 初始化
  * @param  SysTick_InitStruct: 初始化结构体参数 （指针）, 内部参数定义参考 systick.h 文件
  * @retval None
  */
void SysTick_Init(SysTick_InitTypeDef* SysTick_InitStruct)
{
    uint32_t temp = 0;
    
    //设置重装值  
    temp = SysTick_InitStruct->SysTick_Reload;
    
    if(temp > 0x0fff)
    {
        temp = 0x0fff;
    }
    
    SYST->SYST_RVR = temp;   
    
    //清计数值
    SYST->SYST_CVR = 0;
    
    //设置中断使能

    if(SysTick_InitStruct->SysTick_IEEnable == ENABLE) //SysTick 中断使能
    {
        SYST->SYST_CSR |=  BIT(1);    
    }

}

/**
  * @brief  SysTick 系统定时器使能
  * @param  None
  * @retval None
  */
void SysTick_Enable(void)
{
    SYST->SYST_CSR |= BIT(0);
}

/**
  * @brief  SysTick 系统定时器关闭
  * @param  None
  * @retval None
  */
void SysTick_Disable(void)
{
    SYST->SYST_CSR &= ~BIT(0);
}








































































