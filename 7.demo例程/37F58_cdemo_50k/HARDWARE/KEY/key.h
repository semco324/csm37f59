#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)//��ȡ����0
 
//�����������µ�ƽ
#define ON_LEVEL    0 

//û�а������±��ֵ
#define KEYOFF_VAL 0x00 

//���������������±��ֵ
#define KEY0ON_VAL 0x01
//#define KEY1ON_VAL 0x02
//#define KEY2ON_VAL 0x04
//#define KEY3ON_VAL 0x08

#define NONE_PRESS 0 //û�а������·���ֵ
#define KEY0_PRES  1 //KEY0���·���ֵ

void KEY_Init(void);//IO��ʼ��
u8 Key_Scan(u8 mode);  	//����ɨ�躯��					    
#endif
