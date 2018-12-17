#include "udelay.h"


static uint8_t  fac_us=0;							//us基数
static uint16_t fac_ms=0;							//ms基数

//初始化延时函数
void delay_init(void)
{
	RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_SysTick , ENABLE); //打开systick时钟
	RCC_SysTickCLKSourceConfig(RCC_CLKSource_HIRC_Div2);        //STCLK选择HIRC/2 12Mhz
	fac_us=SysTickClock/2000000;   //1us  2分频 
	fac_ms=(uint16_t)fac_us*1000;  //1ms
}

//延时n us 
void delay_us(uint32_t nus)
{
		uint32_t temp;	 
	  SYST->SYST_CSR=0;
	
		SYST->SYST_RVR=(uint32_t)nus*fac_us;//时间加载
	  SYST->SYST_CVR=0;                   //清空计数初值
	  SYST->SYST_CSR|=BIT(0);             //开始计数
	  do
		{
		  temp=SYST->SYST_CSR;
		}while(!(temp&(1<<16)));		//等待时间到达
	  SYST->SYST_CSR&=~BIT(0);             //关闭计数
	  SYST->SYST_CVR=0;                   //清空计数初值
}

//延时n ms 
//SYST->SYST_RVR是24bit 
//nms<=0xffffff*2*1000/SysTickClock
//SysTickClock 单位hz ,nms 单位ms
//24MHz下 nms<=1398
void delay_ms(uint32_t nms)
{
		uint32_t temp;	 
	  SYST->SYST_CSR=0;
	
		SYST->SYST_RVR=(uint32_t)nms*fac_ms; //时间加载
	  SYST->SYST_CVR=0;                    //清空计数初值
	  SYST->SYST_CSR|=BIT(0);              //开始计数
	  do
		{
		  temp=SYST->SYST_CSR;
		}//while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达
		while(!(temp&(1<<16)));
	  SYST->SYST_CSR&=~BIT(0);             //关闭计数
	  SYST->SYST_CVR=0;                   //清空计数初值
}

