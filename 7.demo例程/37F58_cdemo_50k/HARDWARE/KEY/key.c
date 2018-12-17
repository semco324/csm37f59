#include "key.h"
#include "delay.h"
uint8_t Cur_Keyval=0; //��ǰ�������ֵ
uint8_t Pre_Keyval=0; //�ϴΰ������ֵ
uint8_t key_on=0;     //�������� 1��ʾ�Ѿ����� 

//������ʼ������ 
//PC4 ���ó�����
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTCʱ��

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;//PC4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOC5	
} 

//��ð������ֵ
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


//��������
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
	static uint8_t key_up=1; //�����ɿ���־
	if(mode)key_up=1; //1 ֧������
	
	Get_Keyval();
	Key_filter();
	if(key_up && key_on)
	{
	 key_up=0;
	 if(Cur_Keyval==KEY0ON_VAL) return KEY0_PRES;//��������
//	 else if(Cur_Keyval==KEY1ON_VAL) return KEY1_PRES;
		
	}
	else if(Cur_Keyval == KEYOFF_VAL)
	{
	  key_up=1;
	}
	return NONE_PRESS;
}
