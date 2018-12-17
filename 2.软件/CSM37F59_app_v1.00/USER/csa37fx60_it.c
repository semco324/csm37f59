/**
  ******************************************************************************
  * @file    csa37fx60_it.c 
  * @author  chipsea Application Team
  * @version 
  * @date    
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2017 chipsea</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "csa37fx60_it.h" 

 
//NMI_Handler
void NMI_Handler(void)
{


}
//__asm void wait()
//{
//	BX lr
//}
//HardFault_Handler
void HardFault_Handler(void)
{

//wait();
}

//SVC_Handler
void SVC_Handler(void)
{


}

//PendSV_Handler
void PendSV_Handler(void)
{


}

//SysTick_Handler
void SysTick_Handler(void)
{

	
}

//BOD_IRQHandler
void BOD_IRQHandler(void)
{

		
}

//WDT_IRQHandler
void WDT_IRQHandler(void)
{
//    if(WDT_StateRead(WDT_State_Int)) //检测是否是wdt超时中断
//    {
//        WDT_StateClear(WDT_State_Int); //清除中断标志
//    }

}
#include "CS1258.h"
#include "timer.h" 
#include "fmc.h" 
#include "sleep.h" 
#include "hw_iic.h" 


extern uint8_t wait_out;
//TMR0_IRQHandler
void TMR0_IRQHandler(void) //5ms
{   
	 Timer_ClearIEState(Timer_0);	 
	 wait_out++;
	 if(wait_out>10)
	 {
	   wait_out=10;
	 }
}

//TMR1_IRQHandler
void TMR1_IRQHandler(void)
{
	 
}


//UART0_IRQHandler
void UART0_IRQHandler(void)
{

}

//I2C0_IRQHandler
uint8_t num_data=0; //iic传输数据num
uint16_t user_addr;
uint8_t addr_mat=0; 
extern uint8_t iicErrTime;

void I2C0_IRQHandler(void)
{
		uint8_t tempc;
    iicErrTime=0;
    if(I2C_ReadInt_Stete(I2C_RX_FULL) == 1) //接收到数据
    {	
//					I2C_CleraIntState(I2C_RX_FULL);
					tempc = I2C_ReadByte(); //接收数据
			         
					if(num_data==0)	user_addr=tempc;
					if(num_data==1)	addr_map((user_addr<<8)|tempc);  //得到用户传入地址		
					if(num_data>=2) //得到传入数据
					{
						num_data--;						
				
						if(((addr_flag>>ISCMD)&0x01)) //是命令
						{
									addr_flag=0; //clr all				
							    user_addr=(uint16_t)Log_BASE; //指向无效地址
									EquMent->C_STATUS|=((1<<C_Recv)|(1<<C_Exe)); //收到命令+命令正在执行
                  EquMent->C_STATUS&=~((1<<C_Parm)|(1<<C_Ok)); //默认命令参数合法+执行成功							    
									switch (tempc) 
									{	
										case WAKEUP_PARM:  {addr_flag|=(1<<b_wakeup); } break;//wakeup		
										case ANALYSIS_PARM: addr_flag|=(1<<b_analysis);break;//成分分析							
										case FLASH_PARM:    addr_flag|=(1<<b_flash);   break;//写flash
										case UNLOCK_PARM:   addr_flag|=(1<<b_unlock);  break;//CONFIG_K校准
										case SLEEP_PARM:    addr_flag|=(1<<b_sleep);   break;//sleep
										
										default: tempc=0;EquMent->C_STATUS|=((1<<C_Parm)|(1<<C_Ok));//参数非法+失败
										                 EquMent->C_STATUS&=~(1<<C_Exe);//完成																	 
										break;
									}
						}						
						else //不是命令
						{	
							if( (AddrMap.paddr>=RW_Bank0_L&&AddrMap.paddr<=RW_Bank0_R) || \
													(AddrMap.paddr>=RW_Bank1_L&&AddrMap.paddr<=RW_Bank1_R) )
									{
										switch(AddrMap.paddr)
										{
											case (uint32_t)&EquMent->FREQ:  //FREQ
													if(((addr_flag>>b_flash)&0x01)){addr_flag&=~(1<<b_flash);flash_data=tempc;flash_flag|=(1<<num_freq);}
													else                           { flash_data=0;    flash_flag=0;             }break;	
													
											case (uint32_t)&EquMent->M_PART: //M_PART                                   M_PART的最低2位 so &0x03
													if(((addr_flag>>b_flash)&0x01)){ addr_flag&=~(1<<b_flash);flash_data=tempc&0x03;flash_flag|=(1<<num_m_part);}
													else                           { flash_data=0;    flash_flag=0;               }break;
													
											case (uint32_t)&EquMent->CONFIG_K://CONFIG_K				  
													if(((addr_flag>>b_unlock)&0x01)){ *((uint32_t*)AddrMap.paddr)=tempc; addr_flag&=~(1<<b_unlock);
																													   EquMent->C_STATUS&=~((1<<C_Exe)|(1<<C_Ok));//完成+执行成功
																													}
													else {
													      EquMent->C_STATUS|=(1<<C_Ok);//执行失败
				                        EquMent->C_STATUS&=~(1<<C_Exe);//完成
													     }break;											
											default:*((uint32_t*)AddrMap.paddr)=tempc; EquMent->C_STATUS=0; //存数据											            										
													break;	
										}
									}
						  AddrMap.paddr=AddrMap.paddr+4;	//addr+1
									if(AddrMap.paddr>=WRITE_LAST) AddrMap.paddr=WRITE_LAST; 
						}
					}		
    num_data++;
    }
		
    if(I2C_ReadInt_Stete(I2C_RD_REQ) == 1) //主机读数据请求
    {
					I2C_CleraIntState(I2C_RD_REQ);		
					if(((addr_flag>>ISMODE)&0x01))
					{
					  addr_flag&=~(1<<ISMODE); //无模式查询
						I2C_SendByte(0xA0); //发送DATA			
					}
					else
					{
			    if(AddrMap.paddr>=READ_LAST) AddrMap.paddr=READ_LAST;							
					I2C_SendByte(*((uint32_t*)AddrMap.paddr)); //发送DATA								
					AddrMap.paddr=AddrMap.paddr+4;		//addr+1							
					}						
    }	
		
		if(I2C_ReadInt_Stete(I2C_R_START))// start stop
		{
					I2C_CleraIntState(I2C_R_START);
		      num_data=0;
		}
		
		if(I2C_ReadInt_Stete(I2C_R_STOP))// start stop
		{
					I2C_CleraIntState(I2C_R_STOP);
		      num_data=0;
		}		
		
		if(I2C_ReadInt_Stete(I2C_MAT_SAR) == 1) //
		{
//			    int32_t temp;
					I2C_CleraIntState(I2C_MAT_SAR);
//			    temp = I2C0->I2C_CLR_MAT_SAR & BIT(0); //清除匹配唤醒标志位
		      num_data=0;
			    addr_mat=1;			
		}  
}

//AFE0_IRQHandler
void AFE0_IRQHandler(void)
{

}

//AFE1_IRQHandler
void AFE1_IRQHandler(void)
{

}

//PD_WU_IRQHandler
void PD_WU_IRQHandler(void)
{

}

//Default_IRQHandler
void Default_IRQHandler(void)
{

}


/******************************************************************************/
/*                 CSA37FX60 Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_CSA37FX60.s).                                            */
/******************************************************************************/
