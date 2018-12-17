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
 
#include "csa37fx60_rcc.h"
#include "csa37fx60_system.h"


/**
  * @brief  内部时钟开关控制
  * @param  RCC_InsideRC : 选择内部时钟类型，参考rcc.h 内部时钟选择
  * @param  NewState : ENABLE 使能 DISABLE 关闭
  * @retval None
  */
void RCC_InsideRCCmd(uint32_t RCC_InsideRC , FunctionalState NewState)
{
    uint8_t i;
    
    Reg_WRProtDisable(); //解除写保护
    
    for(i=0;i<5;i++)
    {
        if(RCC_InsideRC & BIT(i))
        {
            if(NewState==ENABLE)
            {
                CLKMU->CLKCON |= (1<<i);  
            }
            else
            {
                CLKMU->CLKCON &= ~(1<<i);  
            }
        }
    }    
    
    Reg_WRProtEnable(); //恢复写保护
}
/**
  * @brief  AHB 外设时钟开关
  * @param  RCC_AHBPeriph : 选择外设类型，参考rcc.h AHB外设选择
  * @param  NewState : ENABLE 使能 DISABLE 关闭
  * @retval None
  */
void RCC_AHBPerophClOCKCmd(uint32_t RCC_AHBPeriph , FunctionalState NewState)
{
    uint8_t i;
    
    for(i=0;i<5;i++)
    {
        if((RCC_AHBPeriph>>i) & 0x0001)
        {
            if(NewState==ENABLE)
            {
                CLKMU->AHBCLK |= (1<<i);  
            }
            else
            {
                CLKMU->AHBCLK &= ~(1<<i);  
            }
        }
    }
}
/**
  * @brief  APB 外设时钟开关
  * @param  RCC_APBPeriph : 选择外设类型，参考rcc.h APB外设选择
  * @param  NewState : ENABLE 使能 DISABLE 关闭
  * @retval None
  */
void RCC_APBPerophClOCKCmd(uint32_t RCC_APBPeriph , FunctionalState NewState)
{
    uint8_t i;
    
    Reg_WRProtDisable(); //设置看门狗时需要解锁寄存器保护
    
    for(i=0;i<32;i++)
    {
        if(RCC_APBPeriph & BIT(i))
        {
            if(NewState==ENABLE)
            {
                CLKMU->APBCLK |= BIT(i);  
            }
            else
            {
                CLKMU->APBCLK &= ~BIT(i);  
            }
        }
    }
    
    Reg_WRProtEnable();  //恢复寄存器保护
}

/**
  * @brief  读取内部时钟状态标志
  * @param  RCC_CLKState : 选择时钟类型，参考rcc.h 时钟源状态选择
  * @retval 1: 稳定or成功   0: 不稳定or未使能or失败
  */
uint8_t RCC_GetClkStatus(RCC_CLKState_TypeDef RCC_CLKState)
{
    uint8_t temp = 0;
    
    switch(RCC_CLKState)
    {
        case RCC_CLKState_HIRC :
            
            if( CLKMU->CLKSTATUS & BIT(4) )
            {
                temp = 1;
            }
            
            break;
        
        case RCC_CLKState_LIRC : 
            
            if( CLKMU->CLKSTATUS & BIT(3) )
            {
                temp = 1;
            }
            
            break;
        
        case RCC_CLKState_PLL : 
            
            if( CLKMU->CLKSTATUS & BIT(2) )
            {
                temp = 1;
            }
            
            break;
        
        case CLK_SW_State : 
            
            if( (CLKMU->CLKSTATUS & BIT(7)) == 0 ) //时钟切换成功时为0 
            {
                temp = 1;
            }
            
            break;
        
        default:

            break;
    }
    
    return temp;
}

/**
  * @brief  SysTick 时钟选择
  * @param  RCC_CLKSource : 选择时钟类型，参考rcc.h 时钟源选择
  * @retval None
  */
void RCC_SysTickCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource)
{
    uint32_t temp = 0;
    
    Reg_WRProtDisable(); //解除写保护
    
    switch(RCC_CLKSource)
    {
        case RCC_CLKSource_HCLK_Div2 :
        
            temp = BIT(4) | BIT(3);
        
            break;
        
        case RCC_CLKSource_HIRC_Div2 :
            
            temp = BIT(5) | BIT(4) | BIT(3);
            
            break;
        
        default: //默认 LIRC
        
            temp = BIT(5) | BIT(3);
        
            break;
    }
    
    temp |= (CLKMU->CLKSEL0 & 0x07);
    
    CLKMU->CLKSEL0 = temp;
    
    Reg_WRProtEnable();  //恢复寄存器保护
}

/**
  * @brief  HCLK 时钟选择
  * @param  RCC_CLKSource : 选择时钟类型，参考rcc.h 时钟源选择
  * @retval None
  */
void RCC_HCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource, RCC_HCLKDIV_TypeDef CLKDiv)
{
    uint32_t temp = 0;
    
    Reg_WRProtDisable(); //解除写保护
    
    switch(RCC_CLKSource)
    {
        case RCC_CLKSource_PLL :
        
            temp = BIT(1);
        
            break;
        
        case RCC_CLKSource_LIRC :
            
            temp = BIT(1) | BIT(0) ;
            
            break;
        
        default: //默认 HIRC
        
            temp = BIT(2) | BIT(1) | BIT(0);    
        
            break;
    }
    
    temp |= (CLKMU->CLKSEL0 & 0xf8); 
    
    CLKMU->CLKSEL0 = temp;
    
    Reg_WRProtEnable();  //恢复寄存器保护
    
    //设置分频系数
    temp = CLKMU->CLKDIV;
    
    temp &= 0xfffffff0; 
    temp |= CLKDiv; 
    
    CLKMU->CLKDIV = temp;
}

/**
  * @brief  Timer1 时钟选择
  * @param  RCC_CLKSource : 选择时钟类型，参考rcc.h 时钟源选择
  * @retval None
  */
void RCC_Timer1CLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource)
{
    uint32_t temp = 0;
    
    switch(RCC_CLKSource)
    {
        case RCC_CLKSource_HCLK :
            
            temp = BIT(5) ;

            break;
        
        case RCC_CLKSource_HIRC :
        
            temp = BIT(5) | BIT(4) ;

            break;    
        
        case RCC_CLKSource_LIRC :

            temp = BIT(6) | BIT(5) | BIT(4) ;

            break;    
        
        default:
            break;
    }

    temp |= (CLKMU->CLKSEL1 & 0x0f);
    
    CLKMU->CLKSEL1 = temp;     
}

/**
  * @brief  Timer0 时钟选择
  * @param  RCC_CLKSource : 选择时钟类型，参考rcc.h 时钟源选择
  * @retval None
  */
void RCC_Timer0CLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource)
{
    uint32_t temp;
    
    switch(RCC_CLKSource)
    {
        case RCC_CLKSource_HCLK :
            
            temp = BIT(1) ;

            break;
        
        case RCC_CLKSource_HIRC :
        
            temp = BIT(1) | BIT(0) ;

            break;    
        
        case RCC_CLKSource_LIRC :

            temp = BIT(2) | BIT(1) | BIT(0) ;

            break;    
        
        default:
            break;
    }

    temp |= (CLKMU->CLKSEL1 & 0xf0);
    
    CLKMU->CLKSEL1 = temp;       
}


/**
  * @brief  UART 时钟源设置
  * @param  RCC_CLKSource : 选择时钟类型，参考rcc.h 时钟源选择
  * @param  CLKDiv : 选择时钟分频系数，UART时钟频率 = UART时钟源频率 / (CLKDiv + 1)
  * @retval None
  */
void RCC_UARTCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource , uint8_t CLKDiv)
{
    uint32_t temp;
    uint32_t temp2;
    
    temp = CLKMU->CLKSEL2;
    
    //设置时钟源
    switch(RCC_CLKSource)
    {
        case RCC_CLKSource_HIRC:
                temp |= (BIT(17) | BIT(16));  
                break;
        
        case RCC_CLKSource_PLL:
                temp &= ~BIT(17);  
                temp |= BIT(16); 
                break;
        
        case RCC_CLKSource_HCLK:
                temp |= BIT(17);
                temp &= ~BIT(16);      
                break;
        
        default:break;
    }   
    
    CLKMU->CLKSEL2 = temp;  
    
    //设置分频系数
    temp = CLKMU->CLKDIV;
    
    temp2 = CLKDiv & 0x0f;
    temp &= 0xfffff0ff;
    temp |= (temp2<<8);
    
    CLKMU->CLKDIV = temp;    
    
}
/**
  * @brief  ADC 时钟源设置
  * @param  RCC_CLKSource : 选择时钟类型，参考rcc.h 时钟源选择
  * @param  CLKDiv : 选择时钟分频系数，ADC时钟频率 = ADC时钟源频率 / (CLKDiv + 1)
  * @retval None
  */
void RCC_ADCCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource , uint8_t CLKDiv)
{
    uint32_t temp;
    uint32_t temp2;
    
    //设置时钟源
    temp = CLKMU->CLKSEL2;
    
    switch(RCC_CLKSource)
    {
        case RCC_CLKSource_HIRC2:
                temp &= ~BIT(5);  
                temp &= ~BIT(4); 
                break;
        
        case RCC_CLKSource_PLL:
                temp &= ~BIT(5);  
                temp |= BIT(4); 
                break;
        
        case RCC_CLKSource_HCLK:
                temp |= BIT(5);
                temp &= ~BIT(4);      
                break;
        case RCC_CLKSource_HIRC:
                temp |= BIT(5);
                temp |= BIT(4);   
                break;
        
        default:break;
    }   
    
    CLKMU->CLKSEL2 = temp; 

    //设置分频系数
    temp = CLKMU->CLKDIV;
    
    temp2 = CLKDiv;
    temp &= 0xff00ffff;
    temp |= (temp2<<16);
    
    CLKMU->CLKDIV = temp;
    
}
/**
  * @brief  WWDT 时钟源设置
  * @param  RCC_CLKSource : 选择时钟类型，参考rcc.h 时钟源选择
  * @retval None
  */
void RCC_WWDTCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource)
{
    uint32_t temp;
    
    Reg_WRProtDisable(); //解除写保护
    
    temp = CLKMU->CLKSEL2;
    
    switch(RCC_CLKSource)
    {
        case RCC_CLKSource_HCLK_Div2048:
                temp |= BIT(3); 
                temp &= ~BIT(2); 
                break;
        
        default: //LIRC
                temp &= ~BIT(3);  
                temp &= ~BIT(2);    
                break;
    }   
    
    CLKMU->CLKSEL2 = temp;  
    
    Reg_WRProtEnable(); //恢复写保护
}
/**
  * @brief  WDT 时钟源设置
  * @param  RCC_CLKSource : 选择时钟类型，参考rcc.h 时钟源选择
  * @retval None
  */
void RCC_WDTCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource)
{
    uint32_t temp;
    
    Reg_WRProtDisable(); //解除写保护
    
    temp = CLKMU->CLKSEL2;
    
    //设置前需要解保护
    
    switch(RCC_CLKSource)
    {
        case RCC_CLKSource_LIRC:
                temp &= ~BIT(1);  
                temp &= ~BIT(0);  
                break;
        
        case RCC_CLKSource_HCLK_Div2048:
                temp |= BIT(1);  
                temp &= ~BIT(0);  
                break;
        
        default: break;
    }   
    
    CLKMU->CLKSEL2 = temp;  
    
    Reg_WRProtEnable(); //恢复写保护

}
/**
  * @brief  PCLK 时钟分频设置
  * @param  CLKDiv : 选择时钟分频系数(0~15) 暂不支持 1  PCLK频率 = PCLK源频率/(CLKDiv+1)
  * @retval None
  */
//void RCC_PCLKConfig(uint8_t CLKDiv)
//{
//    uint32_t temp;
//    
//    CLKDiv &= 0x0f;
//    
//    temp = CLKMU->CLKDIV;
//    
//    temp &= 0xffffff0f;
//    temp |= (CLKDiv<<4); 
//    
//    CLKMU->CLKDIV = temp;
//}
void RCC_PCLKConfig(uint8_t CLKDiv)
{   

		uint32_t temp;
	
	  if(CLKDiv==1) CLKDiv=0;  //暂不支持0001
  
    temp = CLKMU->CLKDIV;
    
    temp &= 0xffffff0f;
    temp |= (CLKDiv<<4); 
    
    CLKMU->CLKDIV = temp;
}

/**
  * @brief  HCLK 时钟分频设置
  * @param  CLKDiv : 选择时钟分频系数(0~15) 
  * @retval None
  */
void RCC_HCLKConfig(uint8_t CLKDiv)
{
    uint32_t temp;
    
    temp = CLKMU->CLKDIV;
    
    temp &= 0xfffffff0;
    temp |= CLKDiv; 
    
    CLKMU->CLKDIV = temp;
}

/**
  * @brief  PLL 时钟设置
  * @param  PLLConfig :  参考rcc.h RCC_PLLConfig_TypeDef
  * @retval None
  */
void RCC_PLLConfig(RCC_PLLConfig_TypeDef* PLLConfig)
{
    
    uint32_t temp = 0;
    
    temp |= ((PLLConfig->PLL_SRC&0x01)<<2) | ((PLLConfig->PLL_OE&0x01)<<1) | (PLLConfig->PLL_BP&0x01) ;
    temp <<= 8;
    
    temp |= ((PLLConfig->PLL_OUTDV)<<4) | ((PLLConfig->PLL_INDV)<<4);
    temp <<= 8;
    
    temp |= PLLConfig->PLL_FBDV;
    
    CLKMU->PLLCON = temp;
    
}

/**
  * @brief  PLL 使能
  * @param  None
  * @retval None
  */
void RCC_PLLEnable(void)
{    
    CLKMU->PLLCON |= BIT(19);   
}

/**
  * @brief  PLL 关闭
  * @param  None
  * @retval None
  */
void RCC_PLLDisable(void)
{    
    CLKMU->PLLCON &= ~BIT(19);   
}
