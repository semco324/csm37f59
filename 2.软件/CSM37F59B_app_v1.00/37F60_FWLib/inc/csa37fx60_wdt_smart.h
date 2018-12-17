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
 
#ifndef __CSA37FX60_WDT_SMART_H
#define __CSA37FX60_WDT_SMART_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

typedef enum
{ 
    WDTSmart_819ms = 0x00,
    WDTSmart_1638ms = 0x01,
    WDTSmart_3276ms = 0x02,
    WDTSmart_6553ms = 0x03,
    WDTSmart_409ms = 0x04,
    WDTSmart_204ms = 0x05,
    WDTSmart_102ms = 0x06,
    WDTSmart_51ms = 0x07,
 
}WDTSmartTime_TypeDef;

void WDT_Smart_Init( WDTSmartTime_TypeDef WDT_Time , FunctionalState NewState);
void WDT_Smart_TimeReload(void);

#endif /* __CSA37FX60_WDT_SMART_H */



