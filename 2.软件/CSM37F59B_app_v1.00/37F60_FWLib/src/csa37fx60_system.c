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
 
#include "csa37fx60_system.h"

/**
  * @brief  �����ܱ����ļĴ���
  * @param  None
  * @retval None
  */
void Reg_WRProtDisable(void)
{
    GCR->REGWRPROT = 0x59;
    GCR->REGWRPROT = 0x16;
    GCR->REGWRPROT = 0x88;
}
/**
  * @brief  �����ܱ����ļĴ���
  * @param  None
  * @retval None
  */
void Reg_WRProtEnable(void)
{
    GCR->REGWRPROT = 0x00;
}


/**
  * @brief  ��ȡIC ���豸ID
  * @param  None
  * @retval PDID
  */
uint32_t System_ReadChipPDID(void)
{
    uint32_t temp;
    
    temp = GCR->PDID;
    
    return temp; 
}

/**
  * @brief  ��ȡIC �� CPU ID
  * @param  None
  * @retval Chip ID
  */
uint32_t System_ReadChipCPUID(void)
{
    uint32_t temp;
    
    temp = SCB->CPUID;
    
    return temp; 
}

/**
  * @brief  �¶ȴ�������ʼ��
  * @param  TempSensor_Clk: ��������ʱ��Ƶ��,ȡֵ��Χ�ο� system.h /TempSensorClk_TypeDef
  * @param  NewState: ����ʹ��ѡ�� , ʹ��: ENABLE  �ر�: DISABLE
  * @retval None
  */

void System_TempSensorInit( TempSensorClk_TypeDef TempSensor_Clk , FunctionalState NewState)
{   
    uint8_t temp;
    
    if( NewState == ENABLE )
    {
        temp = TempSensor_Clk<<2;
        temp |= 0x01; 
    }
    else
    {
        temp = 0;
    }
    
    GCR->TEMP_CR = temp;
}
/**
  * @brief  �¶ȴ�����ת��ʹ��
  * @param  None
  * @retval None
  */
void System_TempSensorStartChange(void)
{
    GCR->TEMP_CR &= ~BIT(1);
    GCR->TEMP_CR |= BIT(1);
}
/**
  * @brief  ��ȡ�¶ȴ���������״̬
  * @param  None
  * @retval 1: ����ת��  0:ת�����
  */
uint8_t System_TempSensorBusy(void)
{
    uint8_t temp;
    
    temp = GCR->TEMP_CR;
    
    if(temp & 0x80) 
    {
        return 0;
    }    

    return 1 ;
}


/**
  * @brief  ��ȡ�¶ȴ������¶�ֵ
  * @param  None
  * @retval �¶����ݼĴ�����ֵ
  */
uint16_t System_ReadTempSensorData(void)
{
    uint16_t temp;
    
    temp = GCR->TEMP_DR;
    
    return temp;
}

/**
  * @brief  �����λʹ��
  * @param  Reset_Mode: ѡ��λ���ͣ� ȡֵ��Χ�ο� system.h /ResetMode_TypeDef
  * @retval None
  */
void System_Reset(ResetMode_TypeDef Reset_Mode)
{
    Reg_WRProtDisable(); //�����Ĵ�������
    
    switch(Reset_Mode)
    {
        case MCU_Reset :
            
            RSTMU->IPRSTC1 |= BIT(2); 
            break;

        case CPU_Reset :
            
            RSTMU->IPRSTC1 |= BIT(1); 
            break;

         case Chip_Reset :
             
            RSTMU->IPRSTC1 |= BIT(0); 
            break;
        
        default: break;
    }
    
    Reg_WRProtEnable(); //�ָ��Ĵ�������
}

/**
  * @brief  GPIO �๦������
  * @param  GPIO_x: ѡ��Ҫ���õ�GPIO���� ��ȡֵ��Χ�ο� system.h /GPIO_Sel_TypeDef
  * @param  Reuse_Mode: ѡ��Ҫ���õĹ���ģʽ��ȡֵ��Χ�ο�  system.h /GPIO_ReuseMode_TypeDef
  * @retval None
  */
void System_SetGPIOReuse(GPIO_Sel_TypeDef GPIO_x, GPIO_ReuseMode_TypeDef Reuse_Mode)
{
    uint32_t temp;
    
    temp = GCR->PA_MFP;
    
    switch(GPIO_x)
    {
        case Reuse_PA2 :
        
            if(Reuse_Mode == UART_RXD)
            {
                temp |= BIT(4);
            }
            else //GPIO
            {
                temp &= ~BIT(4);
            }
        
            break;
        case Reuse_PA3 :
            
            if(Reuse_Mode == UART_TXD)
            {
                temp |= BIT(6);
            }
            else //GPIO
            {
                temp &= ~BIT(6);
            }
            
            break;
        case Reuse_PA9 :
        
            if(Reuse_Mode == AFE_CLK)
            {
                temp |= BIT(19) | BIT(18);
            }
            else if(Reuse_Mode == UART_TXD)
            {
                temp |= BIT(19);
                temp &= ~BIT(18);
            }
            else if(Reuse_Mode == I2C_SCL)
            {
                temp &= ~BIT(19);
                temp |= BIT(18);
            }
            else  //GPIO
            {
                temp &= ~BIT(19);
                temp &= ~BIT(18);
            }
            
            break;
        case Reuse_PA10 :
            
            if(Reuse_Mode == AFE_DAT)
            {
                temp |= BIT(21) | BIT(20);
            }
            else if(Reuse_Mode == UART_RXD)
            {
                temp |= BIT(21);
                temp &= ~BIT(20);
            }
            else if(Reuse_Mode == I2C_SDA)
            {
                temp &= ~BIT(21);
                temp |= BIT(20);
            }
            else  //GPIO
            {
                temp &= ~BIT(21);
                temp &= ~BIT(20);
            }
            
            break;
        case Reuse_PA11 :
            
            if(Reuse_Mode == SWCLK)
            {
                temp |= BIT(22) ;
            }
            else 
            {
                temp &= ~BIT(22);
            }
            
            break;
        case Reuse_PA12 :
            
            if(Reuse_Mode == SWDIO)
            {
                temp |= BIT(24) ;
            }
            else 
            {
                temp &= ~BIT(24);
            }
            break;
        
        default: break;
    }
    
    GCR->PA_MFP = temp;
}


