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
  * @brief  硬件除法器
  * @param  dividend: 被除数
  * @param  divisor:  除数
  * @param  divquo: 商 （指针）
  * @param  divrem: 余数 （指针）
  * @retval 1: 商和余数有效  0: 除数为0，结果无效
  */
uint8_t Hardware_Div(int32_t dividend , int16_t divisor , int32_t *divquo , int16_t *divrem )
{
    
    HDIV->DIVIDEND = dividend; //设置被除数
    HDIV->DIVISOR = divisor; //设置除数
    
    *divquo = HDIV->DIVQUO; //商
    *divrem = HDIV->DIVREM; //余数
    
	//除数为负数时，余数符号要反向
    if(divisor&0x8000)
    {
        *divrem = 0 - *divrem;
    }
	
    if( HDIV->DIVSTS & 0x02)
    {
        return 0; //除数是 0
    }   
    
    return 1;
}








