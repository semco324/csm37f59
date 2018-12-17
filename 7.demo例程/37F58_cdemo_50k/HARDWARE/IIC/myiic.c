#include "myiic.h"
#include "delay.h"

u16 SlaveAddr;   //�豸��ַ
u8  SlaveAddrLen=1;//�豸��ַ�ֽ���
u16 SubAddr;     //Ƭ�ڵ�ַ
u8  SubAddrLen=2;  //Ƭ�ڵ�ַ�ֽ���
uint8_t IICReadBuf[IIC_SIZE]={0}; //��IIC����IICLen�����ݻ���
uint8_t IICWriteBuf[IIC_SIZE]={0};//��д��IICLen�����ݻ���
uint16_t IICLen; //IIC��������


//��ʼ��IIC 
//PB10-->IIC_SCL PB11-->IIC_SDA  
void IIC_Init(void)
{				     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(IIC_CLOCK,ENABLE);	//��ʹ������IO PORTCʱ�� 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1|RCC_APB1Periph_I2C2,DISABLE);   
	GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN|IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IIC_GPIOX,&GPIO_InitStructure);
 
	IIC_SCL_H;
	IIC_SDA_H;
}
//����IIC��ʼ�ź�
bool IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	delay_us(4);
	if(!READ_SDA) return FALSE; //SDA��Ϊ�͵�ƽ������æ,�˳�
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	if(READ_SDA) return FALSE; //SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	IIC_SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
	return TRUE;
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_H; 
	delay_us(4);			
	IIC_SDA_H;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	IIC_SCL_L;//ʱ�����0 	   
	return TRUE;  
} 

//����ACKӦ��
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
//������ACKӦ��		    
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
	
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL_L;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
        if(((txd&0x80)>>7)){IIC_SDA_H;}
			  else {IIC_SDA_L;}
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_H;
		delay_us(2); 
		IIC_SCL_L;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=0ʱ������ACK��ack=1������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
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
        IIC_Ack();//����ACK
    else
        IIC_NAck(); //����NACK   
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




















