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
 
#include "csa37fx60_hdiv.h"


/**
  * @brief  Ӳ��������
  * @param  dividend: ������
  * @param  divisor:  ����
  * @param  divquo: �� ��ָ�룩
  * @param  divrem: ���� ��ָ�룩
  * @retval 1: �̺�������Ч  0: ����Ϊ0�������Ч
  */
uint8_t Hardware_Div(int32_t dividend , int16_t divisor , int32_t *divquo , int16_t *divrem )
{
    
    HDIV->DIVIDEND = dividend; //���ñ�����
    HDIV->DIVISOR = divisor; //���ó���
    
    *divquo = HDIV->DIVQUO; //��
    *divrem = HDIV->DIVREM; //����
    
	//����Ϊ����ʱ����������Ҫ����
    if(divisor&0x8000)
    {
        *divrem = 0 - *divrem;
    }
	
    if( HDIV->DIVSTS & 0x02)
    {
        return 0; //������ 0
    }   
    
    return 1;
}








