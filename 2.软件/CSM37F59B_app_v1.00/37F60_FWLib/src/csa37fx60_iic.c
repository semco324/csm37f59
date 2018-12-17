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
  * @brief  I2C �ӻ�ģʽ��ʼ��
  * @param  I2C_InitStruct : I2C ��ʼ���������ο�iic.h
  * @retval None
  */
  
void I2C_Salve_Init(I2C_InitTypeDef* I2C_InitStruct)
{
    I2C0->I2C_ENABLE &=~BIT(0); //�ȹر�I2C
    I2C0->I2C_SAR = I2C_InitStruct->I2C_Addr; //����I2C��ַ
    
    //ʹ�ܴӻ�ģʽ ,��ֹ����ģʽ
    I2C0->I2C_CON = 0;//
    I2C0->I2C_CON |= BIT(7);// ��ַƥ��Ų���stop�ж�
    
    //����RX FIFO ������ֵ ���8��(���üĴ���Ϊ7)
    if(I2C_InitStruct->I2C_RX_FIFO_Level>8)
    {
        I2C_InitStruct->I2C_RX_FIFO_Level = 8;
    }    
    if(I2C_InitStruct->I2C_RX_FIFO_Level == 0)
    {
        I2C_InitStruct->I2C_RX_FIFO_Level = 1;
    }

    I2C0->I2C_RX_TL = I2C_InitStruct->I2C_RX_FIFO_Level - 1;
    
    //����TX FIFO ������ֵ ���8��(���üĴ���Ϊ7)
    if(I2C_InitStruct->I2C_TX_FIFO_Level>8)
    {
        I2C_InitStruct->I2C_TX_FIFO_Level = 8;
    }    
    if(I2C_InitStruct->I2C_TX_FIFO_Level == 0)
    {
        I2C_InitStruct->I2C_TX_FIFO_Level = 1;
    } 

    I2C0->I2C_TX_TL = I2C_InitStruct->I2C_TX_FIFO_Level - 1;
    
    //ʹ��I2C
//     I2C0->I2C_ENABLE |= BIT(0); //��I2C
}

/**
  * @brief  I2C ����һ���ֽ�����
  * @param  dat : Ҫ���͵�����
  * @retval None
  */
void I2C_SendByte(uint8_t dat)
{
    I2C0->I2C_DATA_CMD = dat;
}

/**
  * @brief  I2C ���Ͷ���ֽ�����,ѹ��FIFO,���8��byte
  * @param  dat : Ҫ���͵�����
  * @retval None
  */
void I2C_SendMoreByte(uint8_t *dat, uint8_t num)
{
    uint8_t i;
    
    i = I2C0->I2C_CLR_TX_ABRT; //�ָ�TX FIFO
        
    for(i=0;i<num;i++)
    {
        I2C0->I2C_DATA_CMD = dat[i];        
    }

}

/**
  * @brief  I2C ��ȡ����FIFO�б�������ݸ���
  * @param  None
  * @retval ���ؽ��յĵ��ֽڸ���
  */
uint8_t I2C_RxFIFONum(void)
{
    uint8_t temp;
    
    temp = I2C0->I2C_RXFLR & 0x07;
    
    return temp;
}

/**
  * @brief  I2C ��ȡ���յ���һ���ֽ�����
  * @param  None
  * @retval ���ؽ��յĵ�һ���ֽ�����
  */
uint8_t I2C_ReadByte(void)
{
    uint8_t temp;
    
    temp = I2C0->I2C_DATA_CMD;
    
    return temp;
}

/**
  * @brief  I2C ��ȡ�ж�״̬
  * @param  I2C_IntMode : ��Ҫ�ж��ж�����
  * @retval 0: û�з������ж�, 1���������ж�
  */
uint8_t I2C_ReadInt_Stete(I2C_IntMode_TypeDef I2C_IntMode)
{
    uint8_t temp = 0;
    
    switch(I2C_IntMode)
    {
        case I2C_MAT_SAR : //���˯��ģʽ��I2C��ַƥ��
            
            if(I2C0->I2C_INT_STAT & BIT(15))
            {
                temp = 1;
            }
            
            break;
        
        case I2C_RD_REQ : //������������
        
            if(I2C0->I2C_INT_STAT & BIT(5))
            {
                temp = 1;
            }
        
            break;
        
        case I2C_RX_FULL : //FIFO����������
        
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
  * @brief  I2C �ر�ʹ�������ж�����
  * @param  None
  * @retval None
  */
void I2C_IntAllDisable(void)
{
    I2C0->I2C_INT_MASK = 0;
}

/**
  * @brief  I2C ʹ��ָ���ж�����
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
  * @brief  I2C ��������ж�״̬��־
  * @param  None
  * @retval None
  */
void I2C_ClearAllIntState(void)
{
    uint32_t temp;
    
    temp = I2C0->I2C_CLR_INT;
    
    temp--;//��������
    
    //debug �����ַƥ���ж�
    temp = I2C0->I2C_CLR_MAT_SAR;
}

/**
  * @brief  I2C �豸ʹ��
  * @param  None
  * @retval None
  */
void I2C_Enable(void)
{
    I2C0->I2C_ENABLE |= BIT(0); //��I2C
}

/**
  * @brief  I2C �豸�ر�
  * @param  None
  * @retval None
  */
void I2C_Disable(void)
{
    I2C0->I2C_ENABLE &= ~BIT(0); //��I2C
}

/**
  * @brief  I2C ���ָ���жϱ�־
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
    temp++; //ȥ�����뾯��
}


