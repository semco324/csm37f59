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
 
#include "csa37fx60_timer.h"

/**
  * @brief  定时器初始化
  * @param  Timer_x : 选择Timer_0 or Timer_1
  * @param  Timer_InitStruct : Timer_x 初始化参数，参考timer.h
  * @retval None
  */

void Timer_Init(Timer_x_TypeDef Timer_x , Timer_InitTypeDef* Timer_InitStruct)
{
    uint32_t temp = 0;
    
    if(Timer_InitStruct->Timer_IntEn == ENABLE)
    {
        temp |= BIT(5); 
    }
    
    temp |= (Timer_InitStruct->Timer_CountMode << 3);
    
    temp <<= 8;
    
    temp |= (Timer_InitStruct->Timer_PeroidSel<<4);
    
    temp <<= 8;
    temp <<= 8;
    
    temp |= Timer_InitStruct->Timer_Prescale;    
    
    if(Timer_x == Timer_0)
    {
        TIMER0->TCSR0 = temp;
        TIMER0->TCMPR0 = Timer_InitStruct->Timer_TCMP;
    }
    else
    {
        TIMER1->TCSR1 = temp;
        TIMER1->TCMPR1 = Timer_InitStruct->Timer_TCMP;
    }
}

/**
  * @brief  使能定时器x
  * @param  Timer_x : 选择Timer_0 or Timer_1
  * @retval None
  */

void Timer_Enable(Timer_x_TypeDef Timer_x)
{
    if(Timer_x == Timer_0)
    {
        TIMER0->TCSR0 |= BIT(30);  
    }
    else
    {
        TIMER1->TCSR1 |= BIT(30); 
    }    
}

/**
  * @brief  关闭定时器x
  * @param  Timer_x : 选择Timer_0 or Timer_1
  * @retval None
  */
void Timer_Disable(Timer_x_TypeDef Timer_x)
{
    if(Timer_x == Timer_0)
    {
        TIMER0->TCSR0 &= ~BIT(30);  
    }
    else
    {
        TIMER1->TCSR1 &= ~BIT(30);  
    }    
}

/**
  * @brief  复位定时器x，复位后使能需要重新初始化
  * @param  Timer_x : 选择Timer_0 or Timer_1
  * @retval None
  */
void Timer_Reset(Timer_x_TypeDef Timer_x)
{
    if(Timer_x == Timer_0)
    {
        TIMER0->TCSR0 |= BIT(26);  
    }
    else
    {
        TIMER1->TCSR1 |= BIT(26);  
    }    
}

/**
  * @brief  读取定时器x 工作状态
  * @param  Timer_x : 选择Timer_0 or Timer_1
  * @retval 0： 不工作  1： 工作
  */
uint8_t Timer_ReadWorkState(Timer_x_TypeDef Timer_x)
{
    uint8_t temp = 0;
    
    if(Timer_x == Timer_0)
    {
        if(TIMER0->TCSR0 & BIT(25))
        {
            temp = 1;
        }
    }
    else
    {
        if(TIMER1->TCSR1 & BIT(25))
        {
            temp = 1;
        }
    }
    
    return temp;
}

/**
  * @brief  读取定时器x 中断状态
  * @param  Timer_x : 选择Timer_0 or Timer_1
  * @retval 0： 未发生中断  1： 发生中断
  */
uint8_t Timer_ReadIEState(Timer_x_TypeDef Timer_x)
{
    uint8_t temp = 0;
    
    if(Timer_x == Timer_0)
    {
        if(TIMER0->TISR0 & BIT(0))
        {
            temp = 1;
        }
    }
    else
    {
        if(TIMER1->TISR1 & BIT(0))
        {
            temp = 1;
        }
    }
    
    return temp;
}

/**
  * @brief  清除定时器x 中断状态
  * @param  Timer_x : 选择Timer_0 or Timer_1
  * @retval None
  */
void Timer_ClearIEState(Timer_x_TypeDef Timer_x)
{
    
    if(Timer_x == Timer_0)
    {

        TIMER0->TISR0 |= BIT(0);
    }
    else
    {
        
        TIMER1->TISR1 |= BIT(0);
    }
    
}













