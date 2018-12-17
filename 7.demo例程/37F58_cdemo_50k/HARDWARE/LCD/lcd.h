#ifndef __LCD_H
#define __LCD_H		
#include "sys.h"	 
  
 
//extern char		LcdFlash;
extern char		LcdCharBuf[4][16];		

 
//-----------------LCD端口定义---------------- //   
//PA5-LCD_CLK	 PA6-LCD_DA				 
#define		LCD1T1_DA 				PAout(6) 	
#define		LCD1T1_CLK 				PAout(5)
#define 	READ_LCD1T1_DA   	PAin(6)  //输入SDA 
#define LCD1T1_DA_IN()    {GPIOA->CRL&=0XF0FFFFFF;GPIOE->CRH|=(uint32_t)8<<(4*6);} 
#define LCD1T1_DA_OUT()   {GPIOA->CRL&=0XF0FFFFFF;GPIOE->CRH|=(uint32_t)3<<(4*6);} 
	    															  
	    															  
void LCD_Init(void);																								 
void LCD_Clear(void);
void LcdVPrint(const char *pStr, uint8_t y, uint8_t x);
void LcdUpdate(void);
void LCD_write_string(uint8_t lx, uint8_t cy, uint8_t *p);
void LCDdisp_Process(void);
uint8_t lcd_read_reg(void);

#endif  
	 
	 



