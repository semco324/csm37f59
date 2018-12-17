#include "myiic.h"
#include "delay.h"

u16 SlaveAddr;   //设备地址
u8  SlaveAddrLen=1;//设备地址字节数
u16 SubAddr;     //片内地址
u8  SubAddrLen=2;  //片内地址字节数
uint8_t IICReadBuf[IIC_SIZE]={0}; //从IIC读到IICLen个数据缓存
uint8_t IICWriteBuf[IIC_SIZE]={0};//待写入IICLen个数据缓存
uint16_t IICLen; //IIC操作长度


//初始化IIC 
//PB10-->IIC_SCL PB11-->IIC_SDA  
void IIC_Init(void)
{				     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(IIC_CLOCK,ENABLE);	//先使能外设IO PORTC时钟 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1|RCC_APB1Periph_I2C2,DISABLE);   
	GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN|IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IIC_GPIOX,&GPIO_InitStructure);
 
	IIC_SCL_H;
	IIC_SDA_H;
}
//产生IIC起始信号
bool IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	delay_us(4);
	if(!READ_SDA) return FALSE; //SDA线为低电平则总线忙,退出
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	if(READ_SDA) return FALSE; //SDA线为高电平则总线出错,退出
	IIC_SCL_L;//钳住I2C总线，准备发送或接收数据 
	return TRUE;
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_H; 
	delay_us(4);			
	IIC_SDA_H;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA_H;delay_us(1);	   
	IIC_SCL_H;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
				delay_us(1);
		if(ucErrTime>250)
		{
			IIC_Stop();
			return FALSE;
		}
	}
	IIC_SCL_L;//时钟输出0 	   
	return TRUE;  
} 

//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT();
	delay_us(2);
	IIC_SDA_L;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
	delay_us(2);
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT();
	delay_us(2);
	IIC_SDA_H;
	delay_us(2);
	IIC_SCL_H;
	delay_us(2);
	IIC_SCL_L;
	delay_us(2);
}		
	
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_L;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
        if(((txd&0x80)>>7)){IIC_SDA_H;}
			  else {IIC_SDA_L;}
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL_H;
		delay_us(2); 
		IIC_SCL_L;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=0时，发送ACK，ack=1，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
	IIC_SCL_L; 
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L; 
        delay_us(2);
		IIC_SCL_H;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(2); //delay_us(1); 
  }					 
    if (!ack)
        IIC_Ack();//发送ACK
    else
        IIC_NAck(); //发送NACK   
    return receive;
}



bool IIC_WriteDate(uint8_t SlaveAddr,uint16_t SubAddr,uint8_t *pWriteData,uint16_t Len)
{
	 uint16_t i=0;
	
	 IIC_Start();
	
	 if(SlaveAddrLen==2)
	 {
	 IIC_Send_Byte(((SlaveAddr&0xFF00)>>8));
	 if(IIC_Wait_Ack()==FALSE) return FALSE;	
	 delay_us(30);		 
	 }		 
	 IIC_Send_Byte(SlaveAddr&0x00FE);
	 if(IIC_Wait_Ack()==FALSE) return FALSE;	
	 delay_us(30);
	
	
	 if(SubAddrLen==2)
	 {
	  IIC_Send_Byte(((SubAddr&0xFF00)>>8));
    if(IIC_Wait_Ack()==FALSE) return FALSE;	
    delay_us(30);
	 }	 
	 IIC_Send_Byte((SubAddr&0x00FF));
   if(IIC_Wait_Ack()==FALSE) return FALSE;	
	 delay_us(30);
	 
	 
	 for(i=0;i<Len;i++)
	 {
		IIC_Send_Byte((pWriteData[i]));
		if(IIC_Wait_Ack()==FALSE) return FALSE;	
		  delay_us(30);
	 }
	 IIC_Stop();
	 return TRUE;		  
}

bool IIC_ReadDate(uint8_t SlaveAddr,uint16_t SubAddr,uint8_t *pReadData,uint16_t Len)
{
	   uint8_t i=0;
	  
	   if(IIC_Start()==FALSE)  return FALSE;    //Start
	
		 if(SlaveAddrLen==2)
		 {
		 IIC_Send_Byte(((SlaveAddr&0xFF00)>>8));
		 if(IIC_Wait_Ack()==FALSE) return FALSE;	
		 delay_us(30);		 
		 }		 
		 IIC_Send_Byte(SlaveAddr&0x00FE);
		 if(IIC_Wait_Ack()==FALSE) return FALSE;	
		 delay_us(30);
	
	  if(SubAddrLen==2)
	  {
	    IIC_Send_Byte(((SubAddr&0xFF00)>>8));
      if(IIC_Wait_Ack()==FALSE) return FALSE;		
			delay_us(30);
	  }		
	  IIC_Send_Byte((SubAddr&0x00FF));
    if(IIC_Wait_Ack()==FALSE) return FALSE;	
		delay_us(30);
		
		IIC_Start();
		
		if(SlaveAddrLen==2)
		{
		IIC_Send_Byte(((SlaveAddr&0xFF00)>>8));
		if(IIC_Wait_Ack()==FALSE) return FALSE;	
		delay_us(30);		 
		}		 
		IIC_Send_Byte(((SlaveAddr&0x00FE)|0x01));
		if(IIC_Wait_Ack()==FALSE) return FALSE;	
		delay_us(30);
		
		for(i=0;i<(Len-1);i++)
		{
		   pReadData[i]=IIC_Read_Byte(0);
			 delay_us(30);
		}
		pReadData[Len-1]=IIC_Read_Byte(1);
		delay_us(30);
		IIC_Stop();
	  return TRUE;				
}



bool IIC_StateCheck(uint8_t SlaveAddr)
{
	  if(IIC_Start()==FALSE){IIC_Stop();return FALSE;}
	
		if(SlaveAddrLen==2)
		{
		IIC_Send_Byte(((SlaveAddr&0xFF00)>>8));
		if(IIC_Wait_Ack()==FALSE) {IIC_Stop(); return FALSE;}	
		delay_us(30);		 
		}		 
		IIC_Send_Byte(SlaveAddr&0x00FE);
		if(IIC_Wait_Ack()==FALSE) {IIC_Stop(); return FALSE;}	
		delay_us(30);

    IIC_Stop();
	  return TRUE;	
}




















