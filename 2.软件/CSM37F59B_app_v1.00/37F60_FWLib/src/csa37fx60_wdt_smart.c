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
  * @brief  �����Ź���ʼ��
  * @param  wdt_time: ��λ��ʱʱ�� ȡֵ��Χ�ο� wdt_smart.h WDTSmartTime_TypeDef
  * @param  NewState: ����ʹ��ѡ�� �� ʹ��: ENABLE  �ر�: DISABLE
  * @retval None
  */
void WDT_Smart_Init( WDTSmartTime_TypeDef WDT_Time , FunctionalState NewState)
{
    uint32_t temp = 0;
    
    Reg_WRProtDisable();//���д���� 
    
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
    
    Reg_WRProtEnable(); //�ָ�д���� 
}

/**
  * @brief  �����Ź���ʱ����
  * @param  None
  * @retval None
  */
void WDT_Smart_TimeReload(void)
{
    WDT_SMART->WTSCR = 0x5A;
}


