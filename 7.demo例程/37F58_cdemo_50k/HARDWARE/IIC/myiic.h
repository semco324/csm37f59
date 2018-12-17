#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}
//#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;}
//#define SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;} 
//#define SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}
////////////////////////////////////////////////////////////////////////////////// 	  

//PB10-->IIC_SCL PB11-->IIC_SDA  
#define IIC_GPIOX   GPIOB
#define IIC_CLOCK   RCC_APB2Periph_GPIOB
#define IIC_SCL_PIN GPIO_Pin_10
#define IIC_SDA_PIN GPIO_Pin_11
#define IIC_SIZE 512
extern u16 SlaveAddr;   //设备地址
extern u8  SlaveAddrLen;//设备地址字节数
extern u16 SubAddr;     //片内地址
extern u8  SubAddrLen;  //片内地址字节数

extern uint8_t IICReadBuf[IIC_SIZE]; //从IIC读到IICLen个数据缓存
extern uint8_t IICWriteBuf[IIC_SIZE];//待写入IICLen个数据缓存
extern uint16_t IICLen; //IIC操作长度

//IO方向设置  

#define SDA_IN()  {\
	GPIO_InitTypeDef GPIO_InitStructure;\
	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;\
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;\
	GPIO_Init(IIC_GPIOX,&GPIO_InitStructure);\
}
#define SDA_OUT() {\
	GPIO_InitTypeDef GPIO_InitStructure;\
	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;\
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;\
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;\
	GPIO_Init(IIC_GPIOX,&GPIO_InitStructure);\
}


//IO操作函数	 IIC_SCL_H
#define IIC_SCL_L  GPIO_ResetBits(IIC_GPIOX,IIC_SCL_PIN) //SCL
#define IIC_SCL_H  GPIO_SetBits(IIC_GPIOX,IIC_SCL_PIN)
#define IIC_SDA_L  GPIO_ResetBits(IIC_GPIOX,IIC_SDA_PIN) //SDA	
#define IIC_SDA_H  GPIO_SetBits(IIC_GPIOX,IIC_SDA_PIN)
#define READ_SDA   GPIO_ReadInputDataBit(IIC_GPIOX,IIC_SDA_PIN)  //输入SDA 
#define READ_SCL   GPIO_ReadInputDataBit(IIC_GPIOX,IIC_SCL_PIN)  //输入SCL

typedef enum{
 TRUE  = 0,
 FALSE = 1
}bool;

//IIC所有操作函数

void IIC_Init(void);                //初始化IIC的IO口				 
bool IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
bool IIC_StateCheck(uint8_t SlaveAddr);

//void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
//u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
bool IIC_WriteDate(uint8_t SlaveAddr,uint16_t SubAddr,uint8_t *pWriteData,uint16_t Len);
bool IIC_ReadDate(uint8_t SlaveAddr,uint16_t SubAddr,uint8_t *pReadData,uint16_t Len);
#endif
















