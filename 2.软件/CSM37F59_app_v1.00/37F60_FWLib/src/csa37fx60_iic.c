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
#include "csa37fx60_iic.h"

/**
  * @brief  I2C 从机模式初始化
  * @param  I2C_InitStruct : I2C 初始化参数，参考iic.h
  * @retval None
  */
  
void I2C_Salve_Init(I2C_InitTypeDef* I2C_InitStruct)
{
    I2C0->I2C_ENABLE &=~BIT(0); //先关闭I2C
    I2C0->I2C_SAR = I2C_InitStruct->I2C_Addr; //设置I2C地址
    
    //使能从机模式 ,禁止主机模式
    I2C0->I2C_CON = 0;//
    I2C0->I2C_CON |= BIT(7);// 地址匹配才产生stop中断
    
    //设置RX FIFO 触发阈值 最大8级(配置寄存器为7)
    if(I2C_InitStruct->I2C_RX_FIFO_Level>8)
    {
        I2C_InitStruct->I2C_RX_FIFO_Level = 8;
    }    
    if(I2C_InitStruct->I2C_RX_FIFO_Level == 0)
    {
        I2C_InitStruct->I2C_RX_FIFO_Level = 1;
    }

    I2C0->I2C_RX_TL = I2C_InitStruct->I2C_RX_FIFO_Level - 1;
    
    //设置TX FIFO 触发阈值 最大8级(配置寄存器为7)
    if(I2C_InitStruct->I2C_TX_FIFO_Level>8)
    {
        I2C_InitStruct->I2C_TX_FIFO_Level = 8;
    }    
    if(I2C_InitStruct->I2C_TX_FIFO_Level == 0)
    {
        I2C_InitStruct->I2C_TX_FIFO_Level = 1;
    } 

    I2C0->I2C_TX_TL = I2C_InitStruct->I2C_TX_FIFO_Level - 1;
    
    //使能I2C
//     I2C0->I2C_ENABLE |= BIT(0); //打开I2C
}

/**
  * @brief  I2C 发送一个字节数据
  * @param  dat : 要发送的数据
  * @retval None
  */
void I2C_SendByte(uint8_t dat)
{
    I2C0->I2C_DATA_CMD = dat;
}

/**
  * @brief  I2C 发送多个字节数据,压入FIFO,最多8个byte
  * @param  dat : 要发送的数据
  * @retval None
  */
void I2C_SendMoreByte(uint8_t *dat, uint8_t num)
{
    uint8_t i;
    
    i = I2C0->I2C_CLR_TX_ABRT; //恢复TX FIFO
        
    for(i=0;i<num;i++)
    {
        I2C0->I2C_DATA_CMD = dat[i];        
    }

}

/**
  * @brief  I2C 获取接收FIFO中保存的数据个数
  * @param  None
  * @retval 返回接收的到字节个数
  */
uint8_t I2C_RxFIFONum(void)
{
    uint8_t temp;
    
    temp = I2C0->I2C_RXFLR & 0x07;
    
    return temp;
}

/**
  * @brief  I2C 读取接收到的一个字节数据
  * @param  None
  * @retval 返回接收的到一个字节数据
  */
uint8_t I2C_ReadByte(void)
{
    uint8_t temp;
    
    temp = I2C0->I2C_DATA_CMD;
    
    return temp;
}

/**
  * @brief  I2C 读取中断状态
  * @param  I2C_IntMode : 需要判断中断类型
  * @retval 0: 没有发生该中断, 1：发生该中断
  */
uint8_t I2C_ReadInt_Stete(I2C_IntMode_TypeDef I2C_IntMode)
{
    uint8_t temp = 0;
    
    switch(I2C_IntMode)
    {
        case I2C_MAT_SAR : //深度睡眠模式，I2C地址匹配
            
            if(I2C0->I2C_INT_STAT & BIT(15))
            {
                temp = 1;
            }
            
            break;
        
        case I2C_RD_REQ : //主控请求数据
        
            if(I2C0->I2C_INT_STAT & BIT(5))
            {
                temp = 1;
            }
        
            break;
        
        case I2C_RX_FULL : //FIFO中数据已满
        
            if(I2C0->I2C_INT_STAT & BIT(2))
            {
                temp = 1;
            }
        
            break;
            
        case I2C_R_STOP:
            
            if(I2C0->I2C_INT_STAT & BIT(9))
            {
                temp = 1;
            }
            break;        
            
        case I2C_R_START:
            
            if(I2C0->I2C_INT_STAT & BIT(10))
            {
                temp = 1;
            }
            break;
            
        case I2C_R_RESTART:
            
            if(I2C0->I2C_INT_STAT & BIT(12))
            {
                temp = 1;
            }
            break;  

            
        default: break;
        
    }
    
    return temp;
}

/**
  * @brief  I2C 关闭使能所有中断类型
  * @param  None
  * @retval None
  */
void I2C_IntAllDisable(void)
{
    I2C0->I2C_INT_MASK = 0;
}

/**
  * @brief  I2C 使能指定中断类型
  * @param  None
  * @retval None
  */
void I2C_IntModeEnable(I2C_IntMode_TypeDef I2C_IntMode)
{
    switch(I2C_IntMode)
    {
        case I2C_RD_REQ :
            I2C0->I2C_INT_MASK |= BIT(5);
            break;
        case I2C_RX_FULL :
            I2C0->I2C_INT_MASK |= BIT(2);
            break;
            
        case I2C_R_START :
            I2C0->I2C_INT_MASK |= BIT(10);
            break;
        
        case I2C_R_STOP :
            I2C0->I2C_INT_MASK |= BIT(9);        
            break;

        case I2C_R_RESTART :
            I2C0->I2C_INT_MASK |= BIT(12);        
            break;
       
        default : break;
    }
}

/**
  * @brief  I2C 清除所有中断状态标志
  * @param  None
  * @retval None
  */
void I2C_ClearAllIntState(void)
{
    uint32_t temp;
    
    temp = I2C0->I2C_CLR_INT;
    
    temp--;//消除警告
    
    //debug 清除地址匹配中断
    temp = I2C0->I2C_CLR_MAT_SAR;
}

/**
  * @brief  I2C 设备使能
  * @param  None
  * @retval None
  */
void I2C_Enable(void)
{
    I2C0->I2C_ENABLE |= BIT(0); //打开I2C
}

/**
  * @brief  I2C 设备关闭
  * @param  None
  * @retval None
  */
void I2C_Disable(void)
{
    I2C0->I2C_ENABLE &= ~BIT(0); //打开I2C
}

/**
  * @brief  I2C 清除指定中断标志
  * @param  None
  * @retval None
  */
void I2C_CleraIntState(I2C_IntMode_TypeDef I2C_IntMode)
{
    uint8_t temp;
    switch(I2C_IntMode)
    {
        case I2C_MAT_SAR :
            temp = I2C0->I2C_CLR_MAT_SAR & BIT(0);
            break;
        
        case I2C_RD_REQ :
            temp = I2C0->I2C_CLR_RD_REQ;
            break;
            
        case I2C_R_START :
            temp = I2C0->I2C_CLR_START_DET ;
            break;
        
        case I2C_R_STOP :
            temp = I2C0->I2C_CLR_STOP_DET ;        
            break;

        case I2C_R_RESTART :
            temp = I2C0->I2C_CLR_RST_DET;        
            break;
        
        default : break;
    }  
    temp++; //去除编译警告
}


