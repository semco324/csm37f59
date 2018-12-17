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
 
#include "csa37fx60_wwdt.h"

/**
  * @brief  窗看门狗初始化
  * @param  WWDT_InitStruct: 初始化结构体参数 （指针）, 内部参数定义参考 wwdt.h 文件
  * @retval None
  */
void WWDT_Init(WWDT_InitTypeDef* WWDT_InitStruct)
{
    uint32_t temp;
    
    temp = WWDT_InitStruct->WWDT_CMPData;      //  比较窗口值 
    temp <<= 8;

    temp |= WWDT_InitStruct->WWDT_PeriodSel;   //WWDT 时钟分频
    temp <<= 8;
    
    if( WWDT_InitStruct->WWDT_CMP_INT == ENABLE )  //开启比较中断
    {
        temp |= BIT(1);
    }

    if( WWDT_InitStruct->WWDT_Enable == ENABLE )  //开启计数  WWDT 使能
    {
        temp |= BIT(0);
    }
    
    WWDT->WWDTCR = temp;
    
}

/**
  * @brief  窗看门狗计数器重载
  * @param  None
  * @retval 0: 重载成功  1: 重载失败
  */
uint8_t WWDT_TimeReload(void)
{
    uint8_t CMP_Data;
    uint8_t RLD_Data;
    
    uint32_t temp;
    
    temp = WWDT->WWDTCR;
    CMP_Data = temp>>16 ;
    
    RLD_Data = WWDT->WWDTCVR;
    
    if( RLD_Data < CMP_Data ) 
    {
        WWDT->WWDTRLD = 0x00005AA5;    
    }
    else
    {
        return 1;
    }
   
    return 0 ;
}


/**
  * @brief  窗看门狗比较中断状态查询 
  * @param  None
  * @retval 0: 没有发生比较中断 1: 发生比较中断
  */
uint8_t WWDT_IEState_CMP(void)
{
    uint32_t temp;
    
    temp = WWDT->WWDTSR;
    
    if( temp & 0x01)
    {
        return 1;
    }
    
    return 0;
}
/**
  * @brief  清除窗看门狗比较中断状态标志
  * @param  None
  * @retval None
  */
void WWDT_ClearState_CMP(void)
{
    WWDT->WWDTSR |= 0x01; 
}
/**
  * @brief  窗看门狗超时复位状态查询 
  * @param  None
  * @retval 0: 没有发生超时复位 1: 发生超时复位
  */
uint8_t WWDT_IEState_OverTime(void)
{
    uint32_t temp;
    
    temp = WWDT->WWDTSR;
    
    if( temp & 0x02)
    {
        return 1;
    }
    
    return 0;
}
/**
  * @brief  清除窗看门狗超时超时复位标志
  * @param  None
  * @retval None
  */
void WWDT_ClearState_OverTime(void)
{
    WWDT->WWDTSR |= 0x02; 
}




