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
 
#include "csa37fx60_wdt_smart.h"
#include "csa37fx60_system.h"


/**
  * @brief  精简看门狗初始化
  * @param  wdt_time: 复位超时时间 取值范围参考 wdt_smart.h WDTSmartTime_TypeDef
  * @param  NewState: 功能使能选择 ， 使能: ENABLE  关闭: DISABLE
  * @retval None
  */
void WDT_Smart_Init( WDTSmartTime_TypeDef WDT_Time , FunctionalState NewState)
{
    uint32_t temp = 0;
    
    Reg_WRProtDisable();//解除写保护 
    
    if( NewState == ENABLE)
    {
        temp = WDT_Time;
        temp <<= 8;
        
        temp |=  BIT(7);
    }
    else
    {
        temp =  0;
    }
    
    WDT_SMART->WTSCR = temp;
    
    Reg_WRProtEnable(); //恢复写保护 
}

/**
  * @brief  精简看门狗计时重载
  * @param  None
  * @retval None
  */
void WDT_Smart_TimeReload(void)
{
    WDT_SMART->WTSCR = 0x5A;
}


