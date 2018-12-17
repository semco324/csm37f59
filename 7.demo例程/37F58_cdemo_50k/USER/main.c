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
CSM37F58 50K��Ƶʹ��demo����
ռ����Դ��
DRDY �� ˫�����ж�PB12 
TIM6
*/
uint8_t k1[2];
 int main(void)
 {  
	uint8_t s[30];
	delay_init();	//��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������	 
	LCD_Init();  //LCD12864��ʾ��ʼ��
	LED_Init();	 //��ʼ����LED���ӵ�Ӳ���ӿ�	
	KEY_Init();	 //������ʼ��	
  IIC_Init();  //��ʼ��IIC��IO��		
	DRDY_Init(); //	 
	delay_ms(1000);
	EXTI_M1_Config();//������DRDY������������Ϊ�ⲿ˫���ش����ж�
  BASIC_TIM_Init();//
	 
	 IIC_ReadDate(0xA0,0x100D,k1,2);//k
	 sprintf(s,"CSM37F58  K:%04X",((k1[0]<<8)+k1[1]));
	 LCD_write_string(0,0,s);//��,��,����//du k

	  //LCD_write_string(0,0,"CSM37F58 50KDemo");//��,��,����
	  LCD_write_string(0,1," -------------- ");
	  LCD_write_string(0,2,"----------------");//��,��,����
		LCD_write_string(0,3,"----------------");//��,��,����
		LcdUpdate();
	
 	while(1)
	{
		check_pre();  //������
		measure();    //���в���
	  dis_part();   //��ʾ������λ
		get_result(); //��óɷֽ��
	  LcdUpdate();		
	}	   										    			    
}

