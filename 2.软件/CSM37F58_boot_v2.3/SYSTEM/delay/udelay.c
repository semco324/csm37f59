#include "udelay.h"


static uint8_t  fac_us=0;							//us����
static uint16_t fac_ms=0;							//ms����

//��ʼ����ʱ����
void delay_init(void)
{
	RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_SysTick , ENABLE); //��systickʱ��
	RCC_SysTickCLKSourceConfig(RCC_CLKSource_HIRC_Div2);        //STCLKѡ��HIRC/2 12Mhz
	fac_us=SysTickClock/2000000;   //1us  2��Ƶ 
	fac_ms=(uint16_t)fac_us*1000;  //1ms
}

//��ʱn us 
void delay_us(uint32_t nus)
{
		uint32_t temp;	 
	  SYST->SYST_CSR=0;
	
		SYST->SYST_RVR=(uint32_t)nus*fac_us;//ʱ�����
	  SYST->SYST_CVR=0;                   //��ռ�����ֵ
	  SYST->SYST_CSR|=BIT(0);             //��ʼ����
	  do
		{
		  temp=SYST->SYST_CSR;
		}while(!(temp&(1<<16)));		//�ȴ�ʱ�䵽��
	  SYST->SYST_CSR&=~BIT(0);             //�رռ���
	  SYST->SYST_CVR=0;                   //��ռ�����ֵ
}

//��ʱn ms 
//SYST->SYST_RVR��24bit 
//nms<=0xffffff*2*1000/SysTickClock
//SysTickClock ��λhz ,nms ��λms
//24MHz�� nms<=1398
void delay_ms(uint32_t nms)
{
		uint32_t temp;	 
	  SYST->SYST_CSR=0;
	
		SYST->SYST_RVR=(uint32_t)nms*fac_ms; //ʱ�����
	  SYST->SYST_CVR=0;                    //��ռ�����ֵ
	  SYST->SYST_CSR|=BIT(0);              //��ʼ����
	  do
		{
		  temp=SYST->SYST_CSR;
		}//while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��
		while(!(temp&(1<<16)));
	  SYST->SYST_CSR&=~BIT(0);             //�رռ���
	  SYST->SYST_CVR=0;                   //��ռ�����ֵ
}

