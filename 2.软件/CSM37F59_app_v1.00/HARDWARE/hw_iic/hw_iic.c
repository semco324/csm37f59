
#include "hw_iic.h" 
uint8_t iicErrTime; //iic �����Իָ���
/*PA9-SCL PA10-SDA*/
void Init_IIC_GPIO(void)
{
    RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_GPIO , ENABLE); //ʹ��GPIO clock	
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_I2C , ENABLE); //��iic ʱ��		
	
    System_SetGPIOReuse(Reuse_PA10,I2C_SDA); //����PA10 Ϊ sda����
    System_SetGPIOReuse(Reuse_PA9,I2C_SCL); //���� PA9Ϊscl����   
	
    NVIC_IRQxEnable(IRQ_I2C); //ʹ��iic�ж�
    NVIC_IRQPriorityConfig(IRQ_I2C , 0); //����iic �ж����ȼ�
}


void IIC_Init(void)
{
		I2C_InitTypeDef I2C_InitStruct;
	  iicErrTime=0;
		Init_IIC_GPIO();
	
    I2C_IntAllDisable(); //�ر�ȫ��iic�ж�����
    I2C_IntModeEnable(I2C_RD_REQ); //��iic �����������ж�
    I2C_IntModeEnable(I2C_RX_FULL); //��iic ���ݽ����ж�
    I2C_IntModeEnable(I2C_R_START);
    I2C_IntModeEnable(I2C_R_STOP);
	  I2C_IntModeEnable(I2C_MAT_SAR);
	
//    I2C_IntModeEnable(I2C_R_RESTART);
    
    I2C_InitStruct.I2C_Addr = 0x50; //����iic��ַ(7bit ��������дλ) 
    I2C_InitStruct.I2C_RX_FIFO_Level = 1; //���ý���FIFO��С
    I2C_InitStruct.I2C_TX_FIFO_Level = 8; //���÷���FIFO��С
    
    I2C_Salve_Init(&I2C_InitStruct); //��ʼ��iic
    I2C_Enable(); //ʹ��
}

//-----------------------------------------------------------------------------
//IIC�����Իָ�
//-----------------------------------------------------------------------------
void IIC_Resume(void)
{
    if (I2C0->I2C_STATUS&BIT(6))
    {
        iicErrTime++;      
    }
    
    if(iicErrTime>1)
    {
        //��ʼ��iic
        Reg_WRProtDisable(); //�����Ĵ�������
    
        RSTMU->IPRSTC2 |= BIT(8); 

        Reg_WRProtEnable(); //�ָ��Ĵ�������
        Reg_WRProtDisable(); //�����Ĵ�������
        
        RSTMU->IPRSTC2 &= ~BIT(8);

        Reg_WRProtEnable(); //�ָ��Ĵ�������
        IIC_Init();
    }
}




