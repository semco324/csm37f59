#include "key.h"

void key_init(void)
{
  RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_GPIO , ENABLE); //ʹ��GPIO clock
	GPIO_SetMode(KEY|DRDY_KEY,GPIO_Mode_INPUT);
	GPIO_EnPullUp(KEY|DRDY_KEY);
}


