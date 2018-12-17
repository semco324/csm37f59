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
  * @brief  �ڲ�ʱ�ӿ��ؿ���
  * @param  RCC_InsideRC : ѡ���ڲ�ʱ�����ͣ��ο�rcc.h �ڲ�ʱ��ѡ��
  * @param  NewState : ENABLE ʹ�� DISABLE �ر�
  * @retval None
  */
void RCC_InsideRCCmd(uint32_t RCC_InsideRC , FunctionalState NewState)
{
    uint8_t i;
    
    Reg_WRProtDisable(); //���д����
    
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
    
    Reg_WRProtEnable(); //�ָ�д����
}
/**
  * @brief  AHB ����ʱ�ӿ���
  * @param  RCC_AHBPeriph : ѡ���������ͣ��ο�rcc.h AHB����ѡ��
  * @param  NewState : ENABLE ʹ�� DISABLE �ر�
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
  * @brief  APB ����ʱ�ӿ���
  * @param  RCC_APBPeriph : ѡ���������ͣ��ο�rcc.h APB����ѡ��
  * @param  NewState : ENABLE ʹ�� DISABLE �ر�
  * @retval None
  */
void RCC_APBPerophClOCKCmd(uint32_t RCC_APBPeriph , FunctionalState NewState)
{
    uint8_t i;
    
    Reg_WRProtDisable(); //���ÿ��Ź�ʱ��Ҫ�����Ĵ�������
    
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
    
    Reg_WRProtEnable();  //�ָ��Ĵ�������
}

/**
  * @brief  ��ȡ�ڲ�ʱ��״̬��־
  * @param  RCC_CLKState : ѡ��ʱ�����ͣ��ο�rcc.h ʱ��Դ״̬ѡ��
  * @retval 1: �ȶ�or�ɹ�   0: ���ȶ�orδʹ��orʧ��
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
            
            if( (CLKMU->CLKSTATUS & BIT(7)) == 0 ) //ʱ���л��ɹ�ʱΪ0 
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
  * @brief  SysTick ʱ��ѡ��
  * @param  RCC_CLKSource : ѡ��ʱ�����ͣ��ο�rcc.h ʱ��Դѡ��
  * @retval None
  */
void RCC_SysTickCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource)
{
    uint32_t temp = 0;
    
    Reg_WRProtDisable(); //���д����
    
    switch(RCC_CLKSource)
    {
        case RCC_CLKSource_HCLK_Div2 :
        
            temp = BIT(4) | BIT(3);
        
            break;
        
        case RCC_CLKSource_HIRC_Div2 :
            
            temp = BIT(5) | BIT(4) | BIT(3);
            
            break;
        
        default: //Ĭ�� LIRC
        
            temp = BIT(5) | BIT(3);
        
            break;
    }
    
    temp |= (CLKMU->CLKSEL0 & 0x07);
    
    CLKMU->CLKSEL0 = temp;
    
    Reg_WRProtEnable();  //�ָ��Ĵ�������
}

/**
  * @brief  HCLK ʱ��ѡ��
  * @param  RCC_CLKSource : ѡ��ʱ�����ͣ��ο�rcc.h ʱ��Դѡ��
  * @retval None
  */
void RCC_HCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource, RCC_HCLKDIV_TypeDef CLKDiv)
{
    uint32_t temp = 0;
    
    Reg_WRProtDisable(); //���д����
    
    switch(RCC_CLKSource)
    {
        case RCC_CLKSource_PLL :
        
            temp = BIT(1);
        
            break;
        
        case RCC_CLKSource_LIRC :
            
            temp = BIT(1) | BIT(0) ;
            
            break;
        
        default: //Ĭ�� HIRC
        
            temp = BIT(2) | BIT(1) | BIT(0);    
        
            break;
    }
    
    temp |= (CLKMU->CLKSEL0 & 0xf8); 
    
    CLKMU->CLKSEL0 = temp;
    
    Reg_WRProtEnable();  //�ָ��Ĵ�������
    
    //���÷�Ƶϵ��
    temp = CLKMU->CLKDIV;
    
    temp &= 0xfffffff0; 
    temp |= CLKDiv; 
    
    CLKMU->CLKDIV = temp;
}

/**
  * @brief  Timer1 ʱ��ѡ��
  * @param  RCC_CLKSource : ѡ��ʱ�����ͣ��ο�rcc.h ʱ��Դѡ��
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
  * @brief  Timer0 ʱ��ѡ��
  * @param  RCC_CLKSource : ѡ��ʱ�����ͣ��ο�rcc.h ʱ��Դѡ��
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
  * @brief  UART ʱ��Դ����
  * @param  RCC_CLKSource : ѡ��ʱ�����ͣ��ο�rcc.h ʱ��Դѡ��
  * @param  CLKDiv : ѡ��ʱ�ӷ�Ƶϵ����UARTʱ��Ƶ�� = UARTʱ��ԴƵ�� / (CLKDiv + 1)
  * @retval None
  */
void RCC_UARTCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource , uint8_t CLKDiv)
{
    uint32_t temp;
    uint32_t temp2;
    
    temp = CLKMU->CLKSEL2;
    
    //����ʱ��Դ
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
    
    //���÷�Ƶϵ��
    temp = CLKMU->CLKDIV;
    
    temp2 = CLKDiv & 0x0f;
    temp &= 0xfffff0ff;
    temp |= (temp2<<8);
    
    CLKMU->CLKDIV = temp;    
    
}
/**
  * @brief  ADC ʱ��Դ����
  * @param  RCC_CLKSource : ѡ��ʱ�����ͣ��ο�rcc.h ʱ��Դѡ��
  * @param  CLKDiv : ѡ��ʱ�ӷ�Ƶϵ����ADCʱ��Ƶ�� = ADCʱ��ԴƵ�� / (CLKDiv + 1)
  * @retval None
  */
void RCC_ADCCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource , uint8_t CLKDiv)
{
    uint32_t temp;
    uint32_t temp2;
    
    //����ʱ��Դ
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

    //���÷�Ƶϵ��
    temp = CLKMU->CLKDIV;
    
    temp2 = CLKDiv;
    temp &= 0xff00ffff;
    temp |= (temp2<<16);
    
    CLKMU->CLKDIV = temp;
    
}
/**
  * @brief  WWDT ʱ��Դ����
  * @param  RCC_CLKSource : ѡ��ʱ�����ͣ��ο�rcc.h ʱ��Դѡ��
  * @retval None
  */
void RCC_WWDTCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource)
{
    uint32_t temp;
    
    Reg_WRProtDisable(); //���д����
    
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
    
    Reg_WRProtEnable(); //�ָ�д����
}
/**
  * @brief  WDT ʱ��Դ����
  * @param  RCC_CLKSource : ѡ��ʱ�����ͣ��ο�rcc.h ʱ��Դѡ��
  * @retval None
  */
void RCC_WDTCLKSourceConfig(RCC_CLKSource_TypeDef RCC_CLKSource)
{
    uint32_t temp;
    
    Reg_WRProtDisable(); //���д����
    
    temp = CLKMU->CLKSEL2;
    
    //����ǰ��Ҫ�Ᵽ��
    
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
    
    Reg_WRProtEnable(); //�ָ�д����

}
/**
  * @brief  PCLK ʱ�ӷ�Ƶ����
  * @param  CLKDiv : ѡ��ʱ�ӷ�Ƶϵ��(0~15) �ݲ�֧�� 1  PCLKƵ�� = PCLKԴƵ��/(CLKDiv+1)
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
	
	  if(CLKDiv==1) CLKDiv=0;  //�ݲ�֧��0001
  
    temp = CLKMU->CLKDIV;
    
    temp &= 0xffffff0f;
    temp |= (CLKDiv<<4); 
    
    CLKMU->CLKDIV = temp;
}

/**
  * @brief  HCLK ʱ�ӷ�Ƶ����
  * @param  CLKDiv : ѡ��ʱ�ӷ�Ƶϵ��(0~15) 
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
  * @brief  PLL ʱ������
  * @param  PLLConfig :  �ο�rcc.h RCC_PLLConfig_TypeDef
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
  * @brief  PLL ʹ��
  * @param  None
  * @retval None
  */
void RCC_PLLEnable(void)
{    
    CLKMU->PLLCON |= BIT(19);   
}

/**
  * @brief  PLL �ر�
  * @param  None
  * @retval None
  */
void RCC_PLLDisable(void)
{    
    CLKMU->PLLCON &= ~BIT(19);   
}
