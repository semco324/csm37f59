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
  * @brief  SysTick ϵͳ��ʱ�� ��ʼ��
  * @param  SysTick_InitStruct: ��ʼ���ṹ����� ��ָ�룩, �ڲ���������ο� systick.h �ļ�
  * @retval None
  */
void SysTick_Init(SysTick_InitTypeDef* SysTick_InitStruct)
{
    uint32_t temp = 0;
    
    //������װֵ  
    temp = SysTick_InitStruct->SysTick_Reload;
    
    if(temp > 0x0fff)
    {
        temp = 0x0fff;
    }
    
    SYST->SYST_RVR = temp;   
    
    //�����ֵ
    SYST->SYST_CVR = 0;
    
    //�����ж�ʹ��

    if(SysTick_InitStruct->SysTick_IEEnable == ENABLE) //SysTick �ж�ʹ��
    {
        SYST->SYST_CSR |=  BIT(1);    
    }

}

/**
  * @brief  SysTick ϵͳ��ʱ��ʹ��
  * @param  None
  * @retval None
  */
void SysTick_Enable(void)
{
    SYST->SYST_CSR |= BIT(0);
}

/**
  * @brief  SysTick ϵͳ��ʱ���ر�
  * @param  None
  * @retval None
  */
void SysTick_Disable(void)
{
    SYST->SYST_CSR &= ~BIT(0);
}








































































