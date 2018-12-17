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
  * @brief  �����Ź���ʼ��
  * @param  WWDT_InitStruct: ��ʼ���ṹ����� ��ָ�룩, �ڲ���������ο� wwdt.h �ļ�
  * @retval None
  */
void WWDT_Init(WWDT_InitTypeDef* WWDT_InitStruct)
{
    uint32_t temp;
    
    temp = WWDT_InitStruct->WWDT_CMPData;      //  �Ƚϴ���ֵ 
    temp <<= 8;

    temp |= WWDT_InitStruct->WWDT_PeriodSel;   //WWDT ʱ�ӷ�Ƶ
    temp <<= 8;
    
    if( WWDT_InitStruct->WWDT_CMP_INT == ENABLE )  //�����Ƚ��ж�
    {
        temp |= BIT(1);
    }

    if( WWDT_InitStruct->WWDT_Enable == ENABLE )  //��������  WWDT ʹ��
    {
        temp |= BIT(0);
    }
    
    WWDT->WWDTCR = temp;
    
}

/**
  * @brief  �����Ź�����������
  * @param  None
  * @retval 0: ���سɹ�  1: ����ʧ��
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
  * @brief  �����Ź��Ƚ��ж�״̬��ѯ 
  * @param  None
  * @retval 0: û�з����Ƚ��ж� 1: �����Ƚ��ж�
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
  * @brief  ��������Ź��Ƚ��ж�״̬��־
  * @param  None
  * @retval None
  */
void WWDT_ClearState_CMP(void)
{
    WWDT->WWDTSR |= 0x01; 
}
/**
  * @brief  �����Ź���ʱ��λ״̬��ѯ 
  * @param  None
  * @retval 0: û�з�����ʱ��λ 1: ������ʱ��λ
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
  * @brief  ��������Ź���ʱ��ʱ��λ��־
  * @param  None
  * @retval None
  */
void WWDT_ClearState_OverTime(void)
{
    WWDT->WWDTSR |= 0x02; 
}




