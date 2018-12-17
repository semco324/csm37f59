#include "test_csm.h"

uint8_t ver_info[12]={0};   //版本
uint8_t mesure_info[2]={0}; //频率部位
uint8_t res_val[12]={0};    //RES
uint8_t aly_dat[32];        //成分结果
uint8_t hum_dat[5]={0x02,0xC1,0xAA,0x9E,0x00}; //体重70.5kg 身高170cm 年龄30 性别：男 1 默认模式 0x00
/*
temp=0x35
IIC_WriteDate(0xA0,0x3F5A,&temp,1);//发送睡眠命令

temp=0x53
IIC_WriteDate(0xA0,0x3F5A,&temp,1);//发送唤醒命令
*/

/* 模拟人体电阻阻值示意图
   (1)    (2)
   300    300
       28
   240    240 
   (3)    (4)
Z12 = 600 
Z14 = 568
Z13 = 568
Z23 = 568
Z24 = 568
Z34 = 480 
*/
//Z12 Z14 Z13 Z23 Z24 Z34



uint8_t redy_flg=0;
uint8_t tim_flg=0;
uint8_t flash_redy=0;
uint8_t sta_flg=0;   

void DRDY_Init(void)
{
	//DRDY1
	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(DRDY1_CLOCK,ENABLE);	//先使能外设IO PORTC时钟   
//	GPIO_InitStructure.GPIO_Pin = DRDY1_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //上啦输入
//	GPIO_Init(IIC_GPIOX,&GPIO_InitStructure);
	
	//RESET1 设置输出高
	RCC_APB2PeriphClockCmd(RESET1_CLOCK,ENABLE);	//先使能外设IO PORTC时钟   
	GPIO_InitStructure.GPIO_Pin = RESET1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_Init(RESET1_GPIOX,&GPIO_InitStructure);	
	
	GPIO_SetBits(RESET1_GPIOX,RESET1_PIN);		
	
	//CE1  该引脚是使能CSM37F58电源引脚,一直使能电源
	RCC_APB2PeriphClockCmd(CE1_CLOCK,ENABLE);	//先使能外设IO PORTC时钟   
	GPIO_InitStructure.GPIO_Pin = CE1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_Init(CE1_GPIOX,&GPIO_InitStructure);	
	
	GPIO_SetBits(CE1_GPIOX,CE1_PIN);
}

/*
执行条件 1.tim_flg==1  定时查询时间到
         2.sta_flg==0  CSM37F58处于空闲状态
输出标志 1.redy_flg  1 就绪 0 未就绪
*/

void check_pre(void)
{			
	    uint8_t temp_read=0; 
		/***检查模块是否就绪***/
		if(tim_flg &&(sta_flg==0)) //定时检查
		{
			tim_flg=0;redy_flg=0;
			
		   /*读取版本信息*/  
			if(IIC_ReadDate(0xA0,0x1048,&ver_info[0],12)==TRUE && IIC_ReadDate(0xA0,0x1001,&mesure_info[0],2)==TRUE)
				{ //8 9 10 11
					//sprintf(s,"%02x-%02x-%02x---%02x-%02x",ver_info[4],ver_info[11],ver_info[7],mesure_info[0],mesure_info[1]);  //硬件版本  511字节  算法版本 频率 部位
					//LCD_write_string(0,2,s); //列,行,内容	  
				}
			else
				{  
					//打印读频段信息，部位信息失败
					LCD_write_string(0,1," -------------- ");
          LCD_write_string(0,2,"----------------");	
					LCD_write_string(0,3,"通讯失败--------");
					flash_redy=0;sta_flg=0;					
          M1_ERR();//红灯									
					return;
				}
		
			  IIC_ReadDate(0xA0,0x1013,&temp_read,1); //Z_STATUS
				if((temp_read>>7)&&(temp_read!=0xFF))
				{
						//模块就绪						
						redy_flg=1;	
            if(flash_redy==0) 
						{
							LCD_write_string(0,3,"模块就绪--------");
						}							
				}
				else
				{ 
						//模块正在初始化					
						redy_flg=0;flash_redy=0;sta_flg=0;
					  LCD_write_string(0,3,"初始化中---------");					
				}				
		}	
}


/*
执行条件 1.redy_flg==1 就绪 
         2.sta_flg==0  CSM37F58处于空闲状态
         3.按键按下(可替换成判稳成功)
输出标志 
*/
void measure(void)
{
	   uint8_t cmd=0x80;
	   uint8_t key_flag=0;
		if(redy_flg &&(sta_flg==0))
		{
				key_flag=Key_Scan(0);//检查按键		
				if(key_flag==KEY0_PRES)	
				{  
					//写入人体参数
					IIC_WriteDate(0xA0,0x1058,hum_dat,5);
					
					flash_redy=0;sta_flg=0;M1_NONE();					
					LCD_write_string(0,1," -------------- ");
					LCD_write_string(0,2,"----------------");
					LCD_write_string(0,3,"----------------");
					
          if(IIC_WriteDate(0xA0,0x1000,&cmd,1)==TRUE) //发送测量命令 STATUS
					{
						sta_flg=1;   
					}	
					else
					{
						  flash_redy=1;sta_flg=0;
					    LCD_write_string(0,3,"发送测量错误----");	
						  M1_ERR();
      		}
				}
    }
}

//显示已经测量部位
void dis_part(void)
{
	 uint8_t temp;
     if(sta_flg==2) //正在测量中
		{
			 IIC_ReadDate(0xA0,0x1013,&temp,1);//Z_STATUS
			 if((temp>>5)&0x01) LCD_write_string(0,1," LH-");//左手1
			 else LCD_write_string(0,1," ---");
			
			 if((temp>>4)&0x01) LCD_write_string(13,1,"LL "); //左脚
			 else LCD_write_string(13,1,"-- ");
			
			 if((temp>>3)&0x01) LCD_write_string(10,1,"RL-");//右脚
			 else LCD_write_string(10,1,"---");
				
			 if((temp>>2)&0x01) LCD_write_string(4,1,"RH-");//右手1
			 else LCD_write_string(4,1,"---");
				
			 if((temp>>1)&0x01) LCD_write_string(7,1,"TR-");//腹部
			 else LCD_write_string(7,1,"---");
				
			 if((temp>>0)&0x01) 
			 {
				 LCD_write_string(0+1,1," ------------- ");
				 LcdUpdate();
				 delay_ms(1000);
				 LCD_write_string(0+1,1," LH-RH-TR-RH-LL ");//全身
				 LcdUpdate();
			 } 			 		
		}
}
/* (1)    (2)
   300    300
       28
   240    240 
   (3)    (4)
*/
//获得测量结果
void get_result(void)
{			
	uint8_t err_flag=0;		
	uint8_t aly_cmd=0x04;		
	uint8_t s[30];
		if(sta_flg==3)  //测量完成
		{
			//显示测量完成
			IIC_ReadDate(0xA0,0x1014,&err_flag,1);
			if(err_flag==0)
			{			
				IIC_WriteDate(0xA0,0x3F5A,&aly_cmd,1);//发送计算成分命令
				delay_ms(10);				
				if(IIC_ReadDate(0xA0,0x1158,&aly_dat[0],32)==FALSE)//读成分结果
				{
					LCD_write_string(0,3,"通讯失败--------");
			  	flash_redy=1;sta_flg=0;	
          M1_ERR();//红灯					
					return ;
				}
				IIC_ReadDate(0xA0,(0x10D8),&res_val[0],12);
				
//				//显示成分  体脂百分比  蛋白质
				sprintf(s,"BFP:%.1f PP:%.1f",(((aly_dat[0x18]<<8)+aly_dat[0x19])*0.1),
																					(((aly_dat[0x12]<<8)+aly_dat[0x13])*0.1));


				LCD_write_string(0,2,s); //列,行,内容	  
				
				sprintf(s,"OK!%d-%d-%d",((res_val[2]<<8)|res_val[3]),
																((res_val[6]<<8)|res_val[7]),
																((res_val[10]<<8)|res_val[11]));	 //左手 左脚 躯干
				
				LCD_write_string(0,3,s);//列,行,内容	
				flash_redy=1;	sta_flg=0;		
				M1_OK();
			}
			else
			{
				//报错处理	
        //具体错误显示	
				flash_redy=1;	sta_flg=0;
				M1_ERR();
				if((err_flag>>7)&0x01) {LCD_write_string(0,3,"内短错误--------");return;}
				if((err_flag>>6)&0x01) {LCD_write_string(0,3,"下限错误--------");return;}
				if((err_flag>>5)&0x01) {LCD_write_string(0,3,"上限错误--------");return;}
				if((err_flag>>4)&0x01) {LCD_write_string(0,3,"站姿错误--------");return;}
			}				
		}		
}

