
#include "hw_iic.h" 
uint8_t iicErrTime; //iic 挂死自恢复用
/*PA9-SCL PA10-SDA*/
void Init_IIC_GPIO(void)
{
    RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_GPIO , ENABLE); //使能GPIO clock	
    RCC_APBPerophClOCKCmd(RCC_APBPeriph_I2C , ENABLE); //打开iic 时钟		
	
    System_SetGPIOReuse(Reuse_PA10,I2C_SDA); //设置PA10 为 sda功能
    System_SetGPIOReuse(Reuse_PA9,I2C_SCL); //设置 PA9为scl功能   
	
    NVIC_IRQxEnable(IRQ_I2C); //使能iic中断
    NVIC_IRQPriorityConfig(IRQ_I2C , 0); //设置iic 中断优先级
}


void IIC_Init(void)
{
		I2C_InitTypeDef I2C_InitStruct;
	  iicErrTime=0;
		Init_IIC_GPIO();
	
    I2C_IntAllDisable(); //关闭全部iic中断类型
    I2C_IntModeEnable(I2C_RD_REQ); //打开iic 主机读请求中断
    I2C_IntModeEnable(I2C_RX_FULL); //打开iic 数据接收中断
    I2C_IntModeEnable(I2C_R_START);
    I2C_IntModeEnable(I2C_R_STOP);
	  I2C_IntModeEnable(I2C_MAT_SAR);
	
//    I2C_IntModeEnable(I2C_R_RESTART);
    
    I2C_InitStruct.I2C_Addr = 0x50; //设置iic地址(7bit 不包含读写位) 
    I2C_InitStruct.I2C_RX_FIFO_Level = 1; //设置接收FIFO大小
    I2C_InitStruct.I2C_TX_FIFO_Level = 8; //设置发送FIFO大小
    
    I2C_Salve_Init(&I2C_InitStruct); //初始化iic
    I2C_Enable(); //使能
}

//-----------------------------------------------------------------------------
//IIC挂死自恢复
//-----------------------------------------------------------------------------
void IIC_Resume(void)
{
    if (I2C0->I2C_STATUS&BIT(6))
    {
        iicErrTime++;      
    }
    
    if(iicErrTime>1)
    {
        //初始化iic
        Reg_WRProtDisable(); //解锁寄存器保护
    
        RSTMU->IPRSTC2 |= BIT(8); 

        Reg_WRProtEnable(); //恢复寄存器保护
        Reg_WRProtDisable(); //解锁寄存器保护
        
        RSTMU->IPRSTC2 &= ~BIT(8);

        Reg_WRProtEnable(); //恢复寄存器保护
        IIC_Init();
    }
}




