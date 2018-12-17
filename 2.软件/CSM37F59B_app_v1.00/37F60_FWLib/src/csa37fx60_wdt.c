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
 
#include "csa37fx60_wdt.h"
#include "csa37fx60_system.h"


/**
  * @brief  看门狗初始化
  * @param  WDT_InitStruct : 参数意义参考 wdt.h  WDT_InitTypeDef
  * @retval None
  */
void WDT_Init(WDT_InitTypeDef* WDT_InitStruct)
{
    uint32_t temp;
    
    temp = WDT_InitStruct->WDT_PeriodTime;
    temp <<= 8;
    
    if( WDT_InitStruct->WDT_Enable == ENABLE)
    {
        temp |= BIT(7);
    }
    
    if( WDT_InitStruct->WDT_Int_Enable == ENABLE)
    {
        temp |= BIT(6);
    }   

    if( WDT_InitStruct->WDT_IntWakeUp_Enable == ENABLE)
    {
        temp |= BIT(4);
    }     
    
    if( WDT_InitStruct->WDT_ReSystem_Enable == ENABLE)
    {
        temp |= BIT(1);
    }

    Reg_WRProtDisable(); 
    
    WDT->WTCR = temp;
    
    WDT->WTCRALT = WDT_InitStruct->WDT_DelayTime;
    
    Reg_WRProtEnable();
}


/**
  * @brief  看门狗状态查询
  * @param  WDT_State : 状态类型 参数意义参考 wdt.h  WDT_State_TypeDef
  * @retval 0: 没有发生  1: 发生
  */
uint8_t WDT_StateRead(WDT_State_TypeDef WDT_State)
{
    uint8_t temp;
    
    temp = 0;
    switch (WDT_State)
    {
        case  WDT_State_WakeUp :
            
            if( WDT->WTCR & BIT(5) )
            {
                temp = 1;
            }
        
            break;
        case  WDT_State_Int :
        
            if( WDT->WTCR & BIT(3) )
            {
                temp = 1;
            }        
        
            break;
        case  WDT_State_ReSystem :
        
            if( WDT->WTCR & BIT(2) )
            {
                temp = 1;
            }        
        
            break;
        default : break;
    }
    
    return temp;
}

/**
  * @brief  看门狗状态清除
  * @param  WDT_State : 状态类型 参数意义参考 wdt.h  WDT_State_TypeDef
  * @retval None
  */
void WDT_StateClear(WDT_State_TypeDef WDT_State)
{

    switch (WDT_State)
    {
        case  WDT_State_WakeUp :
            
            WDT->WTCR &= ~BIT(5);
        
            break;
        case  WDT_State_Int :
        
            WDT->WTCR &= ~BIT(3);
        
            break;
        case  WDT_State_ReSystem :
        
            WDT->WTCR &= ~BIT(2);    
        
            break;
        default : break;
    }
}

/**
  * @brief  看门狗计数器清零
  * @param  None
  * @retval None
  */
void WDT_TimeReload(void)
{
    Reg_WRProtDisable();    
    
    WDT->WTCR |= BIT(0);
        
    Reg_WRProtEnable();
}













