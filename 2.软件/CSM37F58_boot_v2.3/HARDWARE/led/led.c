#include "led.h"

void led_init(void)
{
  RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_GPIO , ENABLE); //ʹ��GPIO clock
	GPIO_SetMode(LED0|LED1|LED2|DRDY|ERR|IIC,GPIO_Mode_OUTPUT);
	GPIO_WriteBits(LED0|LED1|LED2|DRDY|ERR|IIC,0);
}


