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
 
#include "csa37fx60_nvic.h"
#include "csa37fx60_system.h"

/**
  * @brief  使能允许中断的中断源，可一次设置多个中断源
  * @param  IRQ_x: 中断源 取值范围参考 nvic.h 头文件列表
  * @retval None
  */
void NVIC_IRQxEnable(uint32_t IRQ_x)
{
    uint8_t i;
    
    for(i=0;i<9;i++)
    {
        if( IRQ_x & BIT(i) )
        {
            NVIC->NVIC_ISER |= BIT(i); 
        }
    }
}
/**
  * @brief  关闭允许中断源，可一次设置多个中断源
  * @param  IRQ_x: 中断源 取值范围参考 nvic.h 头文件列表
  * @retval None
  */
void NVIC_IRQxDisable(uint32_t IRQ_x)
{
    uint8_t i;
    
    for(i=0;i<9;i++)
    {
        if( IRQ_x & BIT(i) )
        {
            NVIC->NVIC_ICER |= BIT(i); 
        }
    }
}
/**
  * @brief  设置中断源挂起状态，可一次设置多个中断源
  * @param  IRQ_x: 中断源 取值范围参考 nvic.h 头文件列表
  * @retval None
  */
void NVIC_IRQxSetPending(uint32_t IRQ_x)
{
    uint8_t i;
    
    for(i=0;i<9;i++)
    {
        if( IRQ_x & BIT(i) )
        {
            NVIC->NVIC_ISPR |= BIT(i); 
        }
    }    
}
/**
  * @brief  清除中断源挂起状态，可一次设置多个中断源
  * @param  IRQ_x: 中断源 取值范围参考 nvic.h 头文件列表
  * @retval None
  */
void NVIC_IRQxClearPending(uint32_t IRQ_x)
{
    uint8_t i;
    
    for(i=0;i<9;i++)
    {
        if( IRQ_x & BIT(i))
        {
            NVIC->NVIC_ICPR |= BIT(i); 
        }
    }
}
/**
  * @brief  设置中断源优先级，不可同时设置多个中断源
  * @param  IRQ_x: 中断源 取值范围参考 nvic.h 头文件列表
  * @param  priority: 优先级 取值范围 0~3 , 0为最高优先级
  * @retval None
  */
void NVIC_IRQPriorityConfig(uint32_t IRQ_x , uint8_t priority)
{
    uint32_t temp;
    
    if( priority>3 ) //优先级范围 0~3
    {
        priority = 3;
    }
    
    temp = priority;
    
    switch (IRQ_x)
    {
        case IRQ_BOD_HVD_RPL: 
                NVIC->NVIC_IPR0 |= (temp<<6) ; 
            break;
        case IRQ_WDT_WWDT:
                NVIC->NVIC_IPR0 |= (temp<<14) ; 
            break;
        case IRQ_TMR0:
                NVIC->NVIC_IPR0 |= (temp<<22) ; 
            break;
        case IRQ_TMR1:
                NVIC->NVIC_IPR0 |= (temp<<30) ; 
            break;
        case IRQ_UART:
                NVIC->NVIC_IPR1 |= (temp<<6) ; 
            break;
        case IRQ_I2C:
                NVIC->NVIC_IPR1 |= (temp<<14) ; 
            break;
        case IRQ_AFE0:
                NVIC->NVIC_IPR1 |= (temp<<22) ; 
            break;
        case IRQ_AFE1:
                NVIC->NVIC_IPR1 |= (temp<<30) ; 
            break;
        case IRQ_PD_WU:
                NVIC->NVIC_IPR2 |= (temp<<6) ; 
            break;
        
        default: break;
    }
}

/**
  * @brief  设置NMI中断源
  * @param  IRQ_x: 中断源 取值范围参考 nvic.h 头文件列表
  * @param NewState: 功能使能选择 ， 使能: ENABLE  关闭: DISABLE
  * @retval None
  */
void NVIC_NMI_IRQSource(uint32_t IRQ_x , FunctionalState NewState)
{
    uint8_t i;
    
    Reg_WRProtDisable();//解锁写保护
    
    for(i=0;i<8;i++)
    {
        if( IRQ_x & BIT(i) )
        {
            INT->NMI_SEL = i;
            break;
        }
    }
    
    if(NewState == ENABLE)
    {
        INT->NMI_SEL |= BIT(8) ;
    }
    else
    {
        INT->NMI_SEL = 0;
    }

    Reg_WRProtEnable();//恢复写保护
}








