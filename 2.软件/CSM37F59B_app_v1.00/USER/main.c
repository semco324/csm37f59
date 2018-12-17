/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from  CHIPSEA.
 *
 *            (C) COPYRIGHT 2015 SHENZHEN CHIPSEA TECHNOLOGIES CO.,LTD.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from CHIPSEA.
 *
 *      Release Information : CSA37FX60 Main function
 *-----------------------------------------------------------------------------
 */
//-------------------------------------------------------------------------------//
/*
	@project  CSM37F58 单频算法50k
	@brief    
  @detaile
	@author
	@data     修改信息见README.txt
	@version  v3.69
*/
#include "csa37fx60.h"
#include "absacc.h"

#include "hw_iic.h" 
#include "addr_map.h"
#include "timer.h"
#include "CS1258.h"
#include "uart.h"    
#include "fmc.h"
#include "analysis.h"
#include "sleep.h"
#include "wdt.h"
 
//__align(4) uint8_t FMC_Data[512];     //最后区缓存
//__align(4) uint8_t Temp_FMC_Data[512];//中转比较用
//__align(4) uint8_t Default_Data[32]=                //出厂默认
//									{0x08,0xff,0xff,0xff,  //FREQ           0
//									 0x02,0xff,0xff,0xff,  //M_PART         4
//									 0x00,0xff,0xff,0xff,  //FREQ1K_VAL_H  8
//									 0x00,0xff,0xff,0xff,  //FREQ1K_VAL_L  12
//									 0x00,0xff,0xff,0xff,  //FREQ2K_VAL_H  16
//									 0x00,0xff,0xff,0xff,  //FREQ2K_VAL_L  20
//									 0x00,0xff,0xff,0xff,  //FREQ3K_VAL_H  24
//									 0x00,0xff,0xff,0xff};//FREQ3K_VAL_L  28
//int32_t x=0; 

//const unsigned int CONFIG0 __at (0x00300000) = 0xE7FFFFFE; //WDT(disabled),Delay(500us),APROM,IAP(disabled)
////const unsigned int CONFIG0 __at (0x00300000) = 0xE7FFFF3E; //WDT(disabled),Delay(500us),LDROM,IAP(enabled)
//const unsigned int CONFIG1 __at (0x00300004) = 0xFFFFEE00; 

int main (void) 
{   				
		uint8_t m=1,n=1,k=1; //m,阻抗分析初始化 n校准初始化 k,心率初始化	


	  User_FMC_Init(); 
  	Clr_All_Block_Ram(); 
	  RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_GPIO,ENABLE);SetDRDYOutput(DRDY_IO);SetDRDY(0);  
		IIC_Init(); 
    delay_init();		
    timer0_init();
		load_fmc_data(); 
	  load_id_data();
    User_WDT_Init();
	
		no_use_peripherals(); 
	    
	  tab_ref_test();
		Reset_CS125x();
		InitCS125x(); 
	
    while(1) 
    {				
     /*****************获得参考**********************/			
 		 GetRef01ADC(f_cnt);  
					
		 /*****************测量模式**********************/			
		 if(((EquMent->STATUS>>ON_OFF)&0x01))  //允许测量
		 {
				 //if(((EquMent->CONFIG_K>>CK)&0x01)) //测量过程中禁止校准模式
					      EquMent->CONFIG_K&=~(1<<CK);
								EquMent->STATUS&=~(1<<H_BR);
			 
			   if(m) {m=0;
					       //设备配置区
					      EquMent->Z_STATUS&=0xC0;//clr Z12,34,14,13,23,24
					      EquMent->ERR_STATUS=0;
					      EquMent->C_STATUS=0;
				        EquMent->F_STATUS=0;  //频率状态
					      Clr_UserBIAPart_Ram();//用户测试BIA
					      Clr_Analysis_Ram();   //成分分析结果
					      Clr_ADCVal_Ram();     //测量过程数据
					      Clr_RESVal_Ram();     //真实电阻
					      Clr_UsrInfo_ResF1();Clr_UsrInfo_ResF2();Clr_UsrInfo_ResF3();			      
					      BIA_FLAG&=~(1<<GetBodyDone); //
			          }		 
			 SetDRDY(1);
				_CS1258bug();							
		   GetBodyRes();					
		 }
		 else{m=1;}	 

		 /*****************工厂模式**********************/	
		 
		 if(((EquMent->CONFIG_K>>CK)&0x01))//工厂校准模式
		 {
		       //if(((EquMent->STATUS>>ON_OFF)&0x01))//校准过程中禁止测量模式
									EquMent->STATUS&=~(1<<ON_OFF);
									EquMent->STATUS&=~(1<<H_BR);
			 
					 if(n){n=0;		
					       EquMent->Z_STATUS&=0xC0;//clr Z12,34,14,13,23,24
					       EquMent->ERR_STATUS=0;
				         EquMent->F_STATUS=0;  //频率状态
							   EquMent->F1CV_FLAG=0;
						     EquMent->F2CV_FLAG=0;
						     EquMent->F3CV_FLAG=0;					 
					       Clr_UserBIAPart_Ram();//用户测试BIA					     
					       Clr_ADCVal_Ram();     //测量过程数据
					       Clr_RESVal_Ram();     //真实电阻
						     BIA_FLAG&=~(1<<CalKDone); //
				         Parm_Rational();          //检查参数合理性
								 }
					if(!((EquMent->ERR_STATUS>>Err_Parm)&0x01))
					{
					SetDRDY(1);						
					_CS1258bug();						
		      Calibrate_K();
					}
		 }
		 else{n=1;}
		 
		 //if(n==1 && m==1)PowerDownCS125x();
	  /*****************自检模式*********************/	
		 
		#ifdef HR_MODE
	  /*****************心率模式*********************/	
		 if(((EquMent->STATUS>>H_BR)&0x01))  //允许测量心率
		 {
		     EquMent->CONFIG_K&=~(1<<CK);   //clr 校准
			   EquMent->STATUS&=~(1<<ON_OFF); //clr 测脂
			 
			   if(k){k=0;
					     Analys->BH=0;  
					     CS125X_XLCL_Initial_Per();//25k,80hz,14		
               CS125X_XLCL_Initial();		 
               delay_ms(5);
					     /////////
					 #ifdef UART_HR
							System_SetGPIOReuse(Reuse_PA11, GPIO_Mode);
							GPIO_EnPullUp(GPIO_PA11); //开启上拉使能  
							GPIO_SetMode(GPIO_PA11,GPIO_Mode_OUTPUT); 
					 #endif
					     /////////
					     SetDRDY(1);					     
				      }
				   Analys->BH = HRI();
							
			 	  if(Analys->BH !=0)	//得到结果
				  {					 				 
						 EquMent->STATUS&=~(1<<H_BR);
						 SendDataToAddr(ADDR_AFE_SYS,0xCE); //SYS 写0xCE 关闭BIM		
						 InitCS125x();   //恢复1258		
						 SetDRDY(0);
						 ///////////
						#ifdef UART_HR
						 GPIO_DisPullUp(GPIO_PA11); //关闭上拉使能
						 GPIO_SetMode(GPIO_PA11,GPIO_Mode_INPUT);	
						 System_SetGPIOReuse(Reuse_PA11, SWCLK); 
						#endif
						 ///////////
				  }										
		 }
		 else{k=1;}
		 
		#endif
		/*****************命令解析*********************/	
			Check_Flash_Cmd(flash_data); //flash 
		  analysis_parm();//analysis	  
      check_sleep(); //sleep		 
			//x++;
		  WDT_TimeReload(); //重载计数值	
    }   
}
	


