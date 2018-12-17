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
 
#include "csa37fx60_crc32.h"


/**
  * @brief  crc��ʼ��
  * @param  CRC32_InitStruct: crc ��ʼ���������ο�crct.h
  * @retval None
  */
void CRC32_Init(CRC32_InitTypeDef* CRC32_InitStruct)
{
      
    CRC32->CRC_CR = 0;
    
    if(CRC32_InitStruct->REV_OUT == ENABLE) //��������ת
    {
        CRC32->CRC_CR |= BIT(7);
    }
    
    CRC32->CRC_CR |= ((CRC32_InitStruct->REV_IN)<<5); //�������ݷ�ת����
    
    CRC32->CRC_CR |= CRC32_InitStruct->VAILD_LONG; //����������Ч����
      
}

/**
  * @brief  crc ����
  * @param  dat: ��Ҫ������������
  * @retval ���ؼ�����
  */
uint32_t CRC32_Cal(uint32_t dat)
{
    uint8_t i;
    
    CRC32->CRC_DR = dat; 
    
    for(i=0;i<8;i++)
    {
        __nop();        
    }
    
    return(CRC32->CRC_DR);

}

/**
  * @brief  crc ������ʱ����
  * @param  dat: ��Ҫ���������(8 bits)
  * @retval None
  */
void CRC32_SaveData(uint8_t dat)
{   
    CRC32->CRC_IDR = dat; 
}

/**
  * @brief  crc ���س�ʼ��������
  * @param  dat: ��ʼ����
  * @retval None
  */
void CRC32_LoadInitData(uint32_t dat)
{
    CRC32->CRC_INIT = dat;
    
    CRC32->CRC_CR |= BIT(4);
    
    while(CRC32->CRC_CR & BIT(4)) {}; //�ȴ���ʼֵ�������   
}


