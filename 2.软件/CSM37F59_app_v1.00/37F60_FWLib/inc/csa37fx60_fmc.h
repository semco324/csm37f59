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
 
#ifndef __CSA37FX60_FMC_H
#define __CSA37FX60_FMC_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

// ISP Control Register (ISPCON) definitions
#define FMC_ISPFF             ((uint32_t)0x00000040)
#define FMC_ISPEN             ((uint32_t)0x00000001)
#define FMC_EXIT_STANDBY      ((uint32_t)0x00000080)
#define FMC_LDUEN             ((uint32_t)0x00000020)
#define FMC_CFGUEN            ((uint32_t)0x00000010)
#define FMC_APUEN             ((uint32_t)0x00000008)
#define FMC_CLK_HIRC          ((uint32_t)0x00000100)
//#define FMC_CLK_HIRC          ((unsigned int)0x00000500)
// ICP Control Register (ICPCON) definitions
#define FMC_ICPEN             ((uint32_t)0x00000001)

// ISP Command (ISPCMD) definitions
#define FMC_STANDBY             ((uint32_t)0x00000030)
#define FMC_READ                ((uint32_t)0x00000000)
#define FMC_PROGRAM             ((uint32_t)0x00000021)
#define FMC_PAGE_ERASE          ((uint32_t)0x00000022)
#define FMC_READ_CID            ((uint32_t)0x0000000B)
#define FMC_READ_DID            ((uint32_t)0x00000004)
#define FMC_PAGE_SWITCH         ((uint32_t)0x0000002e) 

// ISP Trigger Control Register (ISPTRG) definitions
#define FMC_ISPGO               ((uint32_t)0x00000001)

typedef enum
{ 
    FMC_APROM = 0x00,
    FMC_LDROM = 0x01,
    FMC_SRAM = 0x02,
    
}FMC_ROM_Mode_TypeDef;

typedef enum
{ 
    ISP_Freq_48MHz = 0x00,
    ISP_Freq_24MHz = 0x01,
    ISP_Freq_22MHz = 0x02,
    ISP_Freq_16MHz = 0x03,
    ISP_Freq_12MHz = 0x04,
    ISP_Freq_8MHz = 0x05,
    ISP_Freq_4MHz = 0x06,
    ISP_Freq_1MHz = 0x07,
    
}FMC_ISP_Freq_TypeDef;

typedef struct
{
    FMC_ISP_Freq_TypeDef ISP_Freq;
    FunctionalState Enter_DeepStandby;
    FunctionalState LDROM_Update;
    FunctionalState CFG_Update;
    FunctionalState APROM_Update;
    
}FMC_InitTypeDef;

void FMC_Init(FMC_InitTypeDef* FMC_InitStruct);
uint8_t FMC_ErasePage(uint32_t adr);
uint8_t FMC_EraseMorePage(uint32_t adr, uint8_t num);

uint8_t FMC_WritePage (uint32_t adr, uint16_t sz, uint8_t *buf) ; 
uint32_t FMC_ReadPage (uint32_t adr, uint16_t sz, uint8_t *buf);

void FMC_SwitchROM(FMC_ROM_Mode_TypeDef ROM_Mode);

#endif /* __CSA37FX60_FMC_H */

