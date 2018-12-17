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
  * @brief  ����GPIO ��������/�����ʽ����һ�����ö�����
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @param  GPIO_Mode: IO ģʽ����� GPIO_Mode_OUTPUT or ���� GPIO_Mode_INPUT
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
  * @brief  ����GPIO ���������ƽ����һ�����ö�����
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @param  is_high: IO ��ƽ������0ʱΪ�� , ����Ϊ��
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
  * @brief  ��ȡGPIO �����ƽ��һ��ֻ�ɶ�ȡһ��IO
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @retval GPIO ��ƽֵ��0Ϊ�͵�ƽ��1Ϊ�ߵ�ƽ
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
  * @brief  ��ȡGPIO ���������ƽ��һ��ֻ�ɶ�ȡһ��IO
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @retval GPIO �����ƽֵ��0Ϊ�͵�ƽ��1Ϊ�ߵ�ƽ
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
  * @brief  �ر�GPIO ��������ͨ������һ�����ö�����
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_CloseInputChannel(uint16_t GPIO_Pin) //�ر�����ͨ��
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
  * @brief  ��GPIO ��������ͨ������һ�����ö�����
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_OpenInputChannel(uint16_t GPIO_Pin) //������ͨ��
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
  * @brief  ����GPIO �������д��������һ�����ö�����
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_DisWriteOutput(uint16_t GPIO_Pin) //���д����
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
  * @brief  �ر�GPIO �������д��������һ�����ö�����
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_EnWriteOutput(uint16_t GPIO_Pin) //����д���
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
  * @brief  ʹ��GPIO �����������裬��һ�����ö�����
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_EnPullUp(uint16_t GPIO_Pin) //��������ʹ��
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
  * @brief  �ر�GPIO �����������裬��һ�����ö�����
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_DisPullUp(uint16_t GPIO_Pin) //�ر�����ʹ��
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
  * @brief  ʹ��GPIO ��������ʩ���ش�����ʽ����һ�����ö�����
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_EnTYP(uint16_t GPIO_Pin) //ʹ��ʩ���ش�����
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
  * @brief  �ر�GPIO ��������ʩ���ش�����ʽ����һ�����ö�����
  * @param  GPIO_Pin: Ҫ���õ�GPIO ���ź� GPIO_PA1~GPIO_PA12
  * @retval None
  */
void GPIO_DisTYP(uint16_t GPIO_Pin)  //�ر�ʩ���ش�����
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
