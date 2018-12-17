#include "key.h"
#include "delay.h"
uint8_t Cur_Keyval=0; //当前按键标记值
uint8_t Pre_Keyval=0; //上次按键标记值
uint8_t key_on=0;     //抖动变量 1表示已经抖动 

//按键初始化函数 
//PC4 设置成输入
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能PORTC时钟

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;//PC4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOC5	
} 

//获得按键标记值
void Get_Keyval(void)
{
	if(KEY0==ON_LEVEL)
		Cur_Keyval|= KEY0ON_VAL;
	else
		Cur_Keyval&=~KEY0ON_VAL;
	
//	if(KEY1==ON_LEVEL)
//		Cur_Keyval|= KEY1ON_VAL;
//	else
//		Cur_Keyval&=~KEY1ON_VAL;
}


//按键抖动
void Key_filter(void)
{
	if(Cur_Keyval == Pre_Keyval && Cur_Keyval != KEYOFF_VAL)
		{key_on=1;}
	else
		{key_on=0;}
	
	Pre_Keyval=Cur_Keyval;
}


uint8_t Key_Scan(uint8_t mode)
{
	static uint8_t key_up=1; //按键松开标志
	if(mode)key_up=1; //1 支持连按
	
	Get_Keyval();
	Key_filter();
	if(key_up && key_on)
	{
	 key_up=0;
	 if(Cur_Keyval==KEY0ON_VAL) return KEY0_PRES;//解析按键
//	 else if(Cur_Keyval==KEY1ON_VAL) return KEY1_PRES;
		
	}
	else if(Cur_Keyval == KEYOFF_VAL)
	{
	  key_up=1;
	}
	return NONE_PRESS;
}
