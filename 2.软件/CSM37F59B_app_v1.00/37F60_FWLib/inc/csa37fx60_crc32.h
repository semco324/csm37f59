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
 
#ifndef __CSA37FX60_CRC32_H
#define __CSA37FX60_CRC32_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

//输入数据翻转模式选择
typedef enum
{
    NO_REV = 0x00,  //不翻转
    BYTE_REV = 0x01, //按字节翻转
//    HALF_WORD_REV = 0x02, //按半字翻转
    WORD_REV = 0x03, //按字翻转
    
}CRC32_REV_IN_TypeDef;

//输入数据翻转模式选择
typedef enum
{
    BYTE_VALID = 0x00, //字节有效
    HALF_WORD_VALID = 0x01, //半字有效
    WORD_VALID = 0x02, //字有效
    
}CRC32_VALID_TypeDef;

typedef struct
{
    FunctionalState REV_OUT;
    CRC32_REV_IN_TypeDef REV_IN;
    CRC32_VALID_TypeDef VAILD_LONG;
}CRC32_InitTypeDef;

void CRC32_Init(CRC32_InitTypeDef* CRC32_InitStruct);
uint32_t CRC32_Cal(uint32_t dat);
void CRC32_SaveData(uint8_t dat);
void CRC32_LoadInitData(uint32_t dat);

#endif /* __CSA37FX60_HDIV_H */

