#include <stdio.h> 
#include <string.h>
#include "lcd.h"  
#include "delay.h" 
 

 
#define LCD_CLR						0x01				 
#define LCD_REST					0x02			 
#define LCD_NO_SHIFT   		0x06				 
#define LCD_SHIFT      		0x07				 
#define LCD_NO_FLASH   		0x0C			 
#define LCD_HIDE       		0x08				 
#define LCD_FLASH      		0x0D			 
#define LCD_SH         		0x14			 
#define LCD_MODE					0x30			 

#define LCD_COMMD					0xF8			 
#define LCD_DATA					0xFA			 

#define LCD_EX_MODE				0x34			 
#define LCD_DRAW_ON				0x36			 

static	const	uint8_t	Line[4] = {0,2,1,3};	 
				char		LcdCharBuf[4][16];	
			  //char		LcdFlash;

/******************************************************************************
* @brief   虚拟打印到buffer
******************************************************************************/
void LcdVPrint(const char *pStr, uint8_t y, uint8_t x)
{	
	while(*pStr)
	{
		LcdCharBuf[Line[y]][x] = *pStr++;		 
		if(++x > 15)
		{
			x = 0;
			if(++y > 3)
			{
				return;
			}
		}
	}
}


static uint8_t LCD_RD_BYTE(void)
{
	uint8_t i;
	uint8_t temp=0;
		LCD1T1_DA_IN();
	
		for(i=0;i<8;i++)
		{
			LCD1T1_CLK=0; 
			delay_us(1); 
			temp<<=1;
			if(READ_LCD1T1_DA) temp++;
			LCD1T1_CLK=1; 
			delay_us(1); 
		}
	return temp;
}

static void LCD_WR_BYTE(u8 val)
{ 
	u8 i; 
		for(i=0;i<8;i++)
		{ 
			LCD1T1_CLK=0; 
			delay_us(1);  
			if (val & 0x80)	{
				LCD1T1_DA = 1; 
			}	else	{
			LCD1T1_DA = 0; 
			}
			val <<= 1;		 
			LCD1T1_CLK=1;   
			delay_us(1); 
		}
		LCD1T1_CLK=0; 
		LCD1T1_DA=0;
} 
		   
static void LcdWrite(uint8_t Data,uint8_t Command)
{
	uint32_t	i;
	
	LCD_WR_BYTE(Command);
	i = 200;//1000,500,100,ok  50--error
	while (i--);
	
	LCD_WR_BYTE(Data & 0xF0);
	i = 200;//100_CAJ12864_OK
	while (i--);
	
	LCD_WR_BYTE( Data<<4 );
	i = 200;//100_CAJ12864_OK
	while (i--);
}

/******************************************************************************
* @file     lcd.c
* @author		hzheng
* @version  v0.1
* @date      2014-10-9
* @brief   //清屏函数
******************************************************************************/
void LCD_Clear(void)
{
	memset(LcdCharBuf,' ',64);
	//LcdWrite(LCD_CLR,LCD_COMMD);
} 

/******************************************************************************
* @file     lcd.c
* @author		hzheng
* @version  v0.1
* @date     2014-10-9
* @brief    LCD初始化
******************************************************************************/
void LCD_Init(void)
{ 										  
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;//PA5-LCD_CLK	 PA6-LCD_DA				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	LCD1T1_CLK=0; 
	LCD1T1_DA=0;
	 
	delay_ms(150);//do not delete
	LcdWrite(LCD_MODE,LCD_COMMD);	/// 
	delay_ms(5);//1
	LcdWrite(LCD_MODE,LCD_COMMD);	 //
	delay_ms(5);
	LcdWrite(LCD_NO_FLASH,LCD_COMMD); // display on
	delay_ms(5);	
	LcdWrite(LCD_CLR,LCD_COMMD);	//display clear	 
	delay_ms(5);//15
	LcdWrite(LCD_NO_SHIFT,LCD_COMMD); // 
	delay_ms(5); 

	LCD_Clear();

}  

/******************************************************************************
* @file     lcd.c
* @author		hzheng
* @version  v0.1
* @date     2014-10-9
* @brief    刷新显示
******************************************************************************/
void LcdUpdate(void)
{
	char	*p;
	char  i;
	
	p = (char*)LcdCharBuf;
	LcdWrite(0x80, LCD_COMMD);
	for(i = 4*16; i != 0; i--)
	{
		LcdWrite(*p++, LCD_DATA);
	}	
}

 /******************************************************************************
* @file     lcd.c
* @author		hzheng
* @version  v0.1
* @date     2014-10-9
* @brief   虚拟打印内容到buffer
				   lx-列号   cy-行号(0~3)   p-显示内容
******************************************************************************/
void LCD_write_string(uint8_t lx, uint8_t cy, uint8_t *p) //列,行,内容
{	 
	LcdVPrint((const char *)p,cy,lx);	
}

 
/*
 * read lcd data
 */
uint8_t lcd_read_reg(void)
{
	uint8_t value;
	uint8_t hi,lo;
	
	LcdWrite(0x30,0xfc);
	hi = LCD_RD_BYTE();
	lo = LCD_RD_BYTE();
	
	value = (hi&0xf0) + (lo&0x0f);
	
	return value;
}
 


//void LCDdisp_Process(void)
//{
//	if(LcdFlash)
//	{
//		__set_PRIMASK(1); 
//		LcdFlash=0; 
//		
//	  LcdUpdate();
//		__set_PRIMASK(0); 
//	}
//}

 



