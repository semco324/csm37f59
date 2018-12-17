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
  * @brief  解锁受保护的寄存器
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
  * @brief  保护受保护的寄存器
  * @param  None
  * @retval None
  */
void Reg_WRProtEnable(void)
{
    GCR->REGWRPROT = 0x00;
}


/**
  * @brief  读取IC 的设备ID
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
  * @brief  读取IC 的 CPU ID
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
  * @brief  温度传感器初始化
  * @param  TempSensor_Clk: 设置外设时钟频率,取值范围参考 system.h /TempSensorClk_TypeDef
  * @param  NewState: 功能使能选择 , 使能: ENABLE  关闭: DISABLE
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
  * @brief  温度传感器转换使能
  * @param  None
  * @retval None
  */
void System_TempSensorStartChange(void)
{
    GCR->TEMP_CR &= ~BIT(1);
    GCR->TEMP_CR |= BIT(1);
}
/**
  * @brief  读取温度传感器工作状态
  * @param  None
  * @retval 1: 正在转换  0:转换完成
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
  * @brief  读取温度传感器温度值
  * @param  None
  * @retval 温度数据寄存器数值
  */
uint16_t System_ReadTempSensorData(void)
{
    uint16_t temp;
    
    temp = GCR->TEMP_DR;
    
    return temp;
}

/**
  * @brief  软件复位使能
  * @param  Reset_Mode: 选择复位类型， 取值范围参考 system.h /ResetMode_TypeDef
  * @retval None
  */
void System_Reset(ResetMode_TypeDef Reset_Mode)
{
    Reg_WRProtDisable(); //解锁寄存器保护
    
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
    
    Reg_WRProtEnable(); //恢复寄存器保护
}

/**
  * @brief  GPIO 多功能设置
  * @param  GPIO_x: 选择要设置的GPIO引脚 ，取值范围参考 system.h /GPIO_Sel_TypeDef
  * @param  Reuse_Mode: 选择要设置的功能模式，取值范围参考  system.h /GPIO_ReuseMode_TypeDef
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


