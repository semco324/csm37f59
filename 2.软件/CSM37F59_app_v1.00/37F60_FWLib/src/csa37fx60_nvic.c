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
  * @brief  ʹ�������жϵ��ж�Դ����һ�����ö���ж�Դ
  * @param  IRQ_x: �ж�Դ ȡֵ��Χ�ο� nvic.h ͷ�ļ��б�
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
  * @brief  �ر������ж�Դ����һ�����ö���ж�Դ
  * @param  IRQ_x: �ж�Դ ȡֵ��Χ�ο� nvic.h ͷ�ļ��б�
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
  * @brief  �����ж�Դ����״̬����һ�����ö���ж�Դ
  * @param  IRQ_x: �ж�Դ ȡֵ��Χ�ο� nvic.h ͷ�ļ��б�
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
  * @brief  ����ж�Դ����״̬����һ�����ö���ж�Դ
  * @param  IRQ_x: �ж�Դ ȡֵ��Χ�ο� nvic.h ͷ�ļ��б�
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
  * @brief  �����ж�Դ���ȼ�������ͬʱ���ö���ж�Դ
  * @param  IRQ_x: �ж�Դ ȡֵ��Χ�ο� nvic.h ͷ�ļ��б�
  * @param  priority: ���ȼ� ȡֵ��Χ 0~3 , 0Ϊ������ȼ�
  * @retval None
  */
void NVIC_IRQPriorityConfig(uint32_t IRQ_x , uint8_t priority)
{
    uint32_t temp;
    
    if( priority>3 ) //���ȼ���Χ 0~3
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
  * @brief  ����NMI�ж�Դ
  * @param  IRQ_x: �ж�Դ ȡֵ��Χ�ο� nvic.h ͷ�ļ��б�
  * @param NewState: ����ʹ��ѡ�� �� ʹ��: ENABLE  �ر�: DISABLE
  * @retval None
  */
void NVIC_NMI_IRQSource(uint32_t IRQ_x , FunctionalState NewState)
{
    uint8_t i;
    
    Reg_WRProtDisable();//����д����
    
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

    Reg_WRProtEnable();//�ָ�д����
}








