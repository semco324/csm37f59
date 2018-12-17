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
 
#include "csa37fx60_gpio.h"

/**
  * @brief  设置GPIO 引脚输入/输出方式，可一次设置多引脚
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @param  GPIO_Mode: IO 模式，输出 GPIO_Mode_OUTPUT or 输入 GPIO_Mode_INPUT
  * @retval None
  */
void GPIO_SetMode(uint16_t GPIO_Pin , GPIOMode_TypeDef GPIO_Mode)
{
    uint8_t i;
    
    for(i=0;i<13;i++)
    {
        if((GPIO_Pin>>i) & 0x0001)
        {
            if(GPIO_Mode==GPIO_Mode_OUTPUT)
            {
                GPIOA->PA_PMD |= (1<<(i<<1));    
            }
            else
            {
                GPIOA->PA_PMD &= ~(1<<(i<<1)); 
            }
        }
    }
    
}
/**
  * @brief  设置GPIO 引脚输出电平，可一次设置多引脚
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @param  is_high: IO 电平，设置0时为低 , 其他为高
  * @retval None
  */ 
void GPIO_WriteBits(uint16_t GPIO_Pin , uint8_t is_high)
{
    uint32_t temp = 0;
    
    temp = GPIOA->PA_DOUT;
    
    if(is_high)
    {
        temp |= GPIO_Pin; 
    }
    else
    {
        temp &= (~GPIO_Pin);
    }
    
    GPIOA->PA_DOUT = temp;
}
/**
  * @brief  读取GPIO 输入电平，一次只可读取一个IO
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @retval GPIO 电平值，0为低电平，1为高电平
  */
uint8_t GPIO_ReadInputDataBit(uint16_t GPIO_Pin)
{
    uint16_t temp;
    
    temp = GPIOA->PA_PIN;
    
    if(temp&GPIO_Pin)
    {
        return 1;
    }
    
    return 0;
}
/**
  * @brief  读取GPIO 引脚输出电平，一次只可读取一个IO
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @retval GPIO 输出电平值，0为低电平，1为高电平
  */
uint8_t GPIO_ReadOutputDataBit(uint16_t GPIO_Pin)
{
    uint16_t temp;
    
    temp = GPIOA->PA_DOUT;
    
    if(temp&GPIO_Pin)
    {
        return 1;
    }
    
    return 0;
}
/**
  * @brief  关闭GPIO 引脚输入通道，可一次设置多引脚
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_CloseInputChannel(uint16_t GPIO_Pin) //关闭输入通道
{
    uint8_t i;
    uint32_t temp = 0;
    
    for(i=0;i<16;i++)
    {
        if((GPIO_Pin>>i) & 0x0001)
        {
            temp |= BIT(i);
        }        
    }
    
    temp <<= 16;
    
    GPIOA->PA_OFFD |= temp;
}
/**
  * @brief  打开GPIO 引脚输入通道，可一次设置多引脚
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_OpenInputChannel(uint16_t GPIO_Pin) //打开输入通道
{
    uint8_t i;
    uint32_t temp;
    
    temp = GPIOA->PA_OFFD;
    temp >>= 16;
    
    for(i=0;i<16;i++)
    {
        if((GPIO_Pin>>i) & 0x0001)
        {
            temp &= ~BIT(i);
        }        
    }
    
    temp <<= 16;
    
    GPIOA->PA_OFFD = temp;
    
}
/**
  * @brief  设置GPIO 引脚输出写保护，可一次设置多引脚
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_DisWriteOutput(uint16_t GPIO_Pin) //输出写保护
{
    uint8_t i;
    
    for(i=0;i<16;i++)
    {
        if((GPIO_Pin>>i) & 0x0001)
        {
            GPIOA->PA_DMASK |= (1<<i);
        }
    }    
}
/**
  * @brief  关闭GPIO 引脚输出写保护，可一次设置多引脚
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_EnWriteOutput(uint16_t GPIO_Pin) //允许写输出
{
    uint8_t i;
    
    for(i=0;i<16;i++)
    {
        if((GPIO_Pin>>i) & 0x0001)
        {
            GPIOA->PA_DMASK &= ~(1<<i);
        }
    }      
}
/**
  * @brief  使能GPIO 引脚上拉电阻，可一次设置多引脚
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_EnPullUp(uint16_t GPIO_Pin) //开启上拉使能
{
    uint8_t i;
    
    for(i=0;i<16;i++)
    {
        if((GPIO_Pin>>i) & 0x0001)
        {
            GPIOA->PA_PUEN |= (1<<i);
        }
    }
    
}
/**
  * @brief  关闭GPIO 引脚上拉电阻，可一次设置多引脚
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_DisPullUp(uint16_t GPIO_Pin) //关闭上拉使能
{
    uint8_t i;
    
    for(i=0;i<16;i++)
    {
        if((GPIO_Pin>>i) & 0x0001)
        {
            GPIOA->PA_PUEN &= ~(1<<i);
        }
    }
}
/**
  * @brief  使能GPIO 引脚输入施密特触发方式，可一次设置多引脚
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_EnTYP(uint16_t GPIO_Pin) //使能施密特触发器
{
    uint8_t i;
    
    for(i=0;i<16;i++)
    {
        if((GPIO_Pin>>i) & 0x0001)
        {
            GPIOA->PA_TYPEn &= ~(1<<i);
        }
    }    
}
/**
  * @brief  关闭GPIO 引脚输入施密特触发方式，可一次设置多引脚
  * @param  GPIO_Pin: 要设置的GPIO 引脚号 GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_DisTYP(uint16_t GPIO_Pin)  //关闭施密特触发器
{
    uint8_t i;
    
    for(i=0;i<16;i++)
    {
        if((GPIO_Pin>>i) & 0x0001)
        {
            GPIOA->PA_TYPEn |= (1<<i);
        }
    }
}
