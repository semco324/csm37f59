

#include "uiic.h" 
#include "boot.h" 
/*PA9-SCL PA10-SDA*/
void User_IIC_Init(void)
{
    I2C_InitTypeDef I2C_InitStruct;
	
    RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_GPIO , ENABLE); //使能GPIO clock	
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_I2C , ENABLE);
    
    NVIC_IRQxEnable(IRQ_I2C);
    NVIC_IRQPriorityConfig(IRQ_I2C , 0);
    
    System_SetGPIOReuse(Reuse_PA10,I2C_SDA);
    System_SetGPIOReuse(Reuse_PA9,I2C_SCL);
    
    I2C_IntAllDisable();
    I2C_IntModeEnable(I2C_RD_REQ);
    I2C_IntModeEnable(I2C_RX_FULL);
    I2C_IntModeEnable(I2C_R_START);
    I2C_IntModeEnable(I2C_R_STOP);
//    I2C_IntModeEnable(I2C_R_RESTART);
    
    I2C_InitStruct.I2C_Addr = 0x50;
    I2C_InitStruct.I2C_RX_FIFO_Level = 1;
    I2C_InitStruct.I2C_TX_FIFO_Level = 8;
    
    I2C_Salve_Init(&I2C_InitStruct);
    I2C_Enable();

    IIC_HostRWAddr = 0;//主机读写地址
    IIC_ReCount = 0;   //从机接受数据计数
    IIC_WriteflashCmd = 0;//主机读写标志
    IIC_ReDataFinsh = 0;  //从机接受完成标志

}
