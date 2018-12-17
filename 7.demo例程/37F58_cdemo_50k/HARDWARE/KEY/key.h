#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"


#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)//读取按键0
 
//独立按键按下电平
#define ON_LEVEL    0 

//没有按键按下标记值
#define KEYOFF_VAL 0x00 

//各个独立按键按下标记值
#define KEY0ON_VAL 0x01
//#define KEY1ON_VAL 0x02
//#define KEY2ON_VAL 0x04
//#define KEY3ON_VAL 0x08

#define NONE_PRESS 0 //没有按键按下返回值
#define KEY0_PRES  1 //KEY0按下返回值

void KEY_Init(void);//IO初始化
u8 Key_Scan(u8 mode);  	//按键扫描函数					    
#endif
