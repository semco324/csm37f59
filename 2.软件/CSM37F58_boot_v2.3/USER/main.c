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
// 示例工程文件说明:
// 1. startup_CSA37FX60.s 为启动代码;
// 2. absacc.h            提供了修改绝对地址中数据的功能；
// 3. csa37fx60.h         芯片寄存器映射文件；
// V2.1 
// V2.2 BOOT 地址修改
//  #define  BOOT_ADDR  0x0000EE60//0x0000EE3C
//  #define N_BOOT  24//15
// V2.3 修复4字节对齐问题
//-------------------------------------------------------------------------------//

#include "csa37fx60.h"
#include "absacc.h"

#include "uiic.h" 
#include "utimer.h"
#include "ufmc.h"
#include "boot.h"
__align(4) uint8_t first_buf[512]={0}; //第1块512内容 
__align(4) uint8_t temp[4]={0};
uint8_t ok=0;

const unsigned int CONFIG0 __at (0x00300000) = 0xE7FFFF3E; //WDT(disabled),Delay(500us),LDROM,IAP(enabled)
const unsigned int CONFIG1 __at (0x00300004) = 0xFFFFEE00; 

 
int main (void) 
{   
		User_IIC_Init();      //初始化iic /*PA9-SCL PA10-SDA*/
	  timer0_init();		    //tim0
	  User_FMCInit();       //fmc  
//	  load_boot_ver();    //写boot ver 放在这里就不行，！！！
	
	  Flag_WaitTime = 0;
	  ok=0;
	
    RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_GPIO , ENABLE);SetDRDYOutput(DRDY_IO);SetDRDY(0);  
	
	  GetAPROM_ID(); //读取flash aprom 版本号		
    while(1) 
    {	
				if(Flag_WaitTime &&(ok==0)) //100ms 时间到切换APROM &&  aprom ok
				{
					SetDRDY(0);
					
					FMC_ReadPage(BOOT_ADDR,4,first_buf); //boot	1
	        if(first_buf[0]==LDROM_MAJOR)    //如果读到就是boot版本直接APROM
			    {
					  FMC_SwitchROM(FMC_APROM); 
					}
		
					load_boot_ver();		//updata			
					FMC_SwitchROM(FMC_APROM); 				
				}
				else//等待主控升级
				{
				  IIC_CmdProc(); //iic 命令 or 数据处理		
				}					
	  }
}






