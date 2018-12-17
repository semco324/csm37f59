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
 
#ifndef __CSA37FX60_RCC_H
#define __CSA37FX60_RCC_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

//内部时钟选择
#define RCC_InsideRC_HIRC2     BIT(4)
#define RCC_InsideRC_LIRC      BIT(3)
#define RCC_InsideRC_HIRC      BIT(2)

//AHB外设选择
#define RCC_AHBPeriph_SysTick  BIT(4) //0x10
#define RCC_AHBPeriph_CRC      BIT(3) //0x08
#define RCC_AHBPeriph_HDIV     BIT(2) //0x04
#define RCC_AHBPeriph_ISP      BIT(1) //0x02
#define RCC_AHBPeriph_GPIO     BIT(0) //0x01


//APB外设选择
#define RCC_APBPeriph_AFE1     BIT(29) 
#define RCC_APBPeriph_AFE0     BIT(28) 
#define RCC_APBPeriph_Timer1   BIT(17) 
#define RCC_APBPeriph_Timer0   BIT(16) 
#define RCC_APBPeriph_I2C      BIT(8) 
#define RCC_APBPeriph_UART     BIT(2) 
#define RCC_APBPeriph_WWDT     BIT(1) 
#define RCC_APBPeriph_WDT      BIT(0) 

//时钟源选择
typedef enum
{ 
    RCC_CLKSource_HCLK = 0x01,
    RCC_CLKSource_HIRC = 0x02,
    RCC_CLKSource_LIRC = 0X03,
    RCC_CLKSource_PLL = 0x04,
    RCC_CLKSource_HCLK_Div2048 = 0x05,
    RCC_CLKSource_HIRC2 = 0x06,
    RCC_CLKSource_HCLK_Div2 = 0x07,
    RCC_CLKSource_HIRC_Div2 = 0x08,
    
}RCC_CLKSource_TypeDef;

//时钟源状态选择
typedef enum
{ 
    RCC_CLKState_HIRC = 0x01,
    RCC_CLKState_LIRC = 0X02,
    RCC_CLKState_PLL = 0x03,
    
    CLK_SW_State = 0x04,
    
}RCC_CLKState_TypeDef;

//时钟源分频系数选择
typedef enum
{ 
    RCC_HCLKDIV_1 = 0x00,
    RCC_HCLKDIV_2 = 0x01,
    RCC_HCLKDIV_4 = 0x02,
    RCC_HCLKDIV_8 = 0x03,
    RCC_HCLKDIV_16 = 0x04,
    RCC_HCLKDIV_32 = 0x05,
    RCC_HCLKDIV_64 = 0x06,
    RCC_HCLKDIV_128 = 0x07,
    RCC_HCLKDIV_256 = 0x08,
    RCC_HCLKDIV_512 = 0x09,
    
}RCC_HCLKDIV_TypeDef;

typedef enum
{ 
    PLL_OUTDIV_3 = 0x00,
    PLL_OUTDIV_2 = 0x01,
    PLL_OUTDIV_4 = 0x02,
    PLL_OUTDIV_5 = 0x03,
    PLL_OUTDIV_6 = 0x04,
    PLL_OUTDIV_7 = 0x05,
    PLL_OUTDIV_8 = 0x06,
    PLL_OUTDIV_9 = 0x07,
    
}RCC_PLLOUTDIV_TypeDef;

typedef enum
{ 
    PLL_INDIV_1 = 0x00,
    PLL_INDIV_2 = 0x01,
    PLL_INDIV_3 = 0x02,
    PLL_INDIV_4 = 0x03,
    PLL_INDIV_5 = 0x04,
    PLL_INDIV_6 = 0x05,
    PLL_INDIV_7 = 0x06,
    PLL_INDIV_8 = 0x07,
 
}RCC_PLLINDIV_TypeDef;

typedef enum
{ 
    PLL_FBDIV_20 = 0x00,
    PLL_FBDIV_22 = 0x01,
    PLL_FBDIV_24 = 0x02,
    PLL_FBDIV_26 = 0x03,
    PLL_FBDIV_28 = 0x04,
    PLL_FBDIV_30 = 0x05,
    PLL_FBDIV_32 = 0x06,
    PLL_FBDIV_34 = 0x07,
    PLL_FBDIV_36 = 0x08,
    PLL_FBDIV_38 = 0x09,
    PLL_FBDIV_40 = 0x0a,
    PLL_FBDIV_42 = 0x0b,
    PLL_FBDIV_44 = 0x0c,
    PLL_FBDIV_46 = 0x0d,
    PLL_FBDIV_48 = 0x0e,
 
}RCC_PLLFBDIV_TypeDef;

typedef struct
{
    uint8_t PLL_SRC;
    uint8_t PLL_OE;
    uint8_t PLL_BP;
    RCC_PLLOUTDIV_TypeDef PLL_OUTDV;
    RCC_PLLINDIV_TypeDef PLL_INDV;
    RCC_PLLFBDIV_TypeDef PLL_FBDV;
}
RCC_PLLConfig_TypeDef;


void RCC_InsideRCCmd(uint32_t RCC_InsideRC , FunctionalState NewState);
void RCC_AHBPerophClOCKCmd(uint32_t RCC_AHBPeriph , FunctionalState NewState);
void RCC_APBPerophClOCKCmd(uint32_t RCC_APBPeriph , FunctionalState NewState);
uint8_t RCC_GetClkStatus(RCC_CLKState_TypeDef RCC_CLKState);
void RCC_SysTickCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource);
void RCC_HCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource, RCC_HCLKDIV_TypeDef CLKDiv);
void RCC_Timer1CLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource);
void RCC_Timer0CLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource);
void RCC_UARTCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource , uint8_t CLKDiv);
void RCC_ADCCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource , uint8_t CLKDiv);
void RCC_WWDTCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource);
void RCC_WDTCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource);
void RCC_PCLKConfig(uint8_t CLKDiv);
void RCC_HCLKConfig(uint8_t CLKDiv);
void RCC_PLLConfig(RCC_PLLConfig_TypeDef* PLLConfig);
void RCC_PLLEnable(void);
#endif /* __CSA37FX60_RCC_H */



