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
  * @brief  ��ʱ����ʼ��
  * @param  Timer_x : ѡ��Timer_0 or Timer_1
  * @param  Timer_InitStruct : Timer_x ��ʼ���������ο�timer.h
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
  * @brief  ʹ�ܶ�ʱ��x
  * @param  Timer_x : ѡ��Timer_0 or Timer_1
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
  * @brief  �رն�ʱ��x
  * @param  Timer_x : ѡ��Timer_0 or Timer_1
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
  * @brief  ��λ��ʱ��x����λ��ʹ����Ҫ���³�ʼ��
  * @param  Timer_x : ѡ��Timer_0 or Timer_1
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
  * @brief  ��ȡ��ʱ��x ����״̬
  * @param  Timer_x : ѡ��Timer_0 or Timer_1
  * @retval 0�� ������  1�� ����
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
  * @brief  ��ȡ��ʱ��x �ж�״̬
  * @param  Timer_x : ѡ��Timer_0 or Timer_1
  * @retval 0�� δ�����ж�  1�� �����ж�
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
  * @brief  �����ʱ��x �ж�״̬
  * @param  Timer_x : ѡ��Timer_0 or Timer_1
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













