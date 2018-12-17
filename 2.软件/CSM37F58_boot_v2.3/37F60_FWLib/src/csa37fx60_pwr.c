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
  * @brief  设置备份寄存器，深度掉电模式下不丢失
  * @param  backup_data: 要保存的数据
  * @retval None
  */ 
void PWR_SetBackUp(uint32_t backup_data)
{
    PWRMU->BACKUP0 = backup_data;
}

/**
  * @brief  省电模式设置
  * @param  PWR_InitStruct:  省电模式 初始化参数，参考pwr.h
  * @param  WF_Mode:唤醒方式  
  * @retval None
  */ 
void PWR_EnterSleepMode(PWR_DeepSleep_InitTypeDef* PWR_InitStruct, PWR_WFMode_TypeDef WF_Mode)
{
    Reg_WRProtDisable();//解除写保护
    
    //设置功能
    if(PWR_InitStruct->WakeUp_IntEn == ENABLE) //deep sleep x 唤醒中断
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
    
    if(PWR_InitStruct->WakeUp_DelayEn == ENABLE) //deep sleep x 唤醒后延迟
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
        
                //设置sleep 模式
                PWRMU->PWR_CON &= ~BIT(15); 
                PWRMU->PWR_CON &= ~BIT(23); 
                SCB->SCR &= ~BIT(2);
        
                break;
        case DeepSleep_Mode1:
        
                //设置sleep1 模式
                PWRMU->PWR_CON &= ~BIT(15); 
                PWRMU->PWR_CON &= ~BIT(23); 
                SCB->SCR |= BIT(2);
        
                break;
        case DeepSleep_Mode2:
                
                //设置sleep2 模式
                PWRMU->PWR_CON &= ~BIT(15); 
                PWRMU->PWR_CON |= BIT(23); 
                SCB->SCR |= BIT(2);
        
                break;
        case PowerDown_Mode:
                
                //设置pd sleep 模式
                PWRMU->PWR_CON |= BIT(15); 
                PWRMU->PWR_CON |= BIT(23); 
                SCB->SCR |= BIT(2);
        
                break;
        default: break;
    }
    
    Reg_WRProtEnable(); //恢复写保护    
    
    if(WF_Mode == WFI_Mode)
    {
        __WFI();
    }
    else
    {
        __WFE();
    }
    
}










