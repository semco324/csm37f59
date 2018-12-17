#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"  
#include "myiic.h"
#include "test_csm.h"
#include "bsp_TiMbase.h"
#include "lcd.h"
#include "exti.h"

/*
CSM37F58 50K单频使用demo例程
占用资源：
DRDY 接 双边沿中断PB12 
TIM6
*/
uint8_t k1[2];
 int main(void)
 {  
	uint8_t s[30];
	delay_init();	//延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组设置	 
	LCD_Init();  //LCD12864显示初始化
	LED_Init();	 //初始化与LED连接的硬件接口	
	KEY_Init();	 //按键初始化	
  IIC_Init();  //初始化IIC的IO口		
	DRDY_Init(); //	 
	delay_ms(1000);
	EXTI_M1_Config();//设置与DRDY引脚相连引脚为外部双边沿触发中断
  BASIC_TIM_Init();//
	 
	 IIC_ReadDate(0xA0,0x100D,k1,2);//k
	 sprintf(s,"CSM37F58  K:%04X",((k1[0]<<8)+k1[1]));
	 LCD_write_string(0,0,s);//列,行,内容//du k

	  //LCD_write_string(0,0,"CSM37F58 50KDemo");//列,行,内容
	  LCD_write_string(0,1," -------------- ");
	  LCD_write_string(0,2,"----------------");//列,行,内容
		LCD_write_string(0,3,"----------------");//列,行,内容
		LcdUpdate();
	
 	while(1)
	{
		check_pre();  //检查就绪
		measure();    //进行测量
	  dis_part();   //显示测量部位
		get_result(); //获得成分结果
	  LcdUpdate();		
	}	   										    			    
}

