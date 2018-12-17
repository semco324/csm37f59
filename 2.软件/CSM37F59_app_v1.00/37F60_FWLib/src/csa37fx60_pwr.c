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
 
#include "csa37fx60_pwr.h"
#include "csa37fx60_system.h"
 
/**
  * @brief  ���ñ��ݼĴ�������ȵ���ģʽ�²���ʧ
  * @param  backup_data: Ҫ���������
  * @retval None
  */ 
void PWR_SetBackUp(uint32_t backup_data)
{
    PWRMU->BACKUP0 = backup_data;
}

/**
  * @brief  ʡ��ģʽ����
  * @param  PWR_InitStruct:  ʡ��ģʽ ��ʼ���������ο�pwr.h
  * @param  WF_Mode:���ѷ�ʽ  
  * @retval None
  */ 
void PWR_EnterSleepMode(PWR_DeepSleep_InitTypeDef* PWR_InitStruct, PWR_WFMode_TypeDef WF_Mode)
{
    Reg_WRProtDisable();//���д����
    
    //���ù���
    if(PWR_InitStruct->WakeUp_IntEn == ENABLE) //deep sleep x �����ж�
    {
        PWRMU->PWR_CON |= BIT(29); // sleep 1
        PWRMU->PWR_CON |= BIT(21); // sleep 2
        PWRMU->PWR_CON |= BIT(13); // pd sleep 
    }
    else
    {
        PWRMU->PWR_CON &= ~BIT(29); // sleep 1
        PWRMU->PWR_CON &= ~BIT(21); // sleep 2
        PWRMU->PWR_CON &= ~BIT(13); // pd sleep 
    }
    
    if(PWR_InitStruct->WakeUp_DelayEn == ENABLE) //deep sleep x ���Ѻ��ӳ�
    {
        PWRMU->PWR_CON |= BIT(28); // sleep 1
        PWRMU->PWR_CON |= BIT(20); // sleep 2
        PWRMU->PWR_CON |= BIT(12); // pd sleep 
    }
    else
    {
        PWRMU->PWR_CON &= ~BIT(28); // sleep 1
        PWRMU->PWR_CON &= ~BIT(20); // sleep 2
        PWRMU->PWR_CON &= ~BIT(12); // pd sleep 
    }
    
    
    switch(PWR_InitStruct->Mode)
    {
        case Sleep_Mode:
        
                //����sleep ģʽ
                PWRMU->PWR_CON &= ~BIT(15); 
                PWRMU->PWR_CON &= ~BIT(23); 
                SCB->SCR &= ~BIT(2);
        
                break;
        case DeepSleep_Mode1:
        
                //����sleep1 ģʽ
                PWRMU->PWR_CON &= ~BIT(15); 
                PWRMU->PWR_CON &= ~BIT(23); 
                SCB->SCR |= BIT(2);
        
                break;
        case DeepSleep_Mode2:
                
                //����sleep2 ģʽ
                PWRMU->PWR_CON &= ~BIT(15); 
                PWRMU->PWR_CON |= BIT(23); 
                SCB->SCR |= BIT(2);
        
                break;
        case PowerDown_Mode:
                
                //����pd sleep ģʽ
                PWRMU->PWR_CON |= BIT(15); 
                PWRMU->PWR_CON |= BIT(23); 
                SCB->SCR |= BIT(2);
        
                break;
        default: break;
    }
    
    Reg_WRProtEnable(); //�ָ�д����    
    
    if(WF_Mode == WFI_Mode)
    {
        __WFI();
    }
    else
    {
        __WFE();
    }
    
}










