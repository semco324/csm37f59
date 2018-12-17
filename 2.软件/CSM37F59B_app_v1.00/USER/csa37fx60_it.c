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
//    if(WDT_StateRead(WDT_State_Int)) //����Ƿ���wdt��ʱ�ж�
//    {
//        WDT_StateClear(WDT_State_Int); //����жϱ�־
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
uint8_t num_data=0; //iic��������num
uint16_t user_addr;
uint8_t addr_mat=0; 
extern uint8_t iicErrTime;

void I2C0_IRQHandler(void)
{
		uint8_t tempc;
    iicErrTime=0;
    if(I2C_ReadInt_Stete(I2C_RX_FULL) == 1) //���յ�����
    {	
//					I2C_CleraIntState(I2C_RX_FULL);
					tempc = I2C_ReadByte(); //��������
			         
					if(num_data==0)	user_addr=tempc;
					if(num_data==1)	addr_map((user_addr<<8)|tempc);  //�õ��û������ַ		
					if(num_data>=2) //�õ���������
					{
						num_data--;						
				
						if(((addr_flag>>ISCMD)&0x01)) //������
						{
									addr_flag=0; //clr all				
							    user_addr=(uint16_t)Log_BASE; //ָ����Ч��ַ
									EquMent->C_STATUS|=((1<<C_Recv)|(1<<C_Exe)); //�յ�����+��������ִ��
                  EquMent->C_STATUS&=~((1<<C_Parm)|(1<<C_Ok)); //Ĭ����������Ϸ�+ִ�гɹ�							    
									switch (tempc) 
									{	
										case WAKEUP_PARM:  {addr_flag|=(1<<b_wakeup); } break;//wakeup		
										case ANALYSIS_PARM: addr_flag|=(1<<b_analysis);break;//�ɷַ���							
										case FLASH_PARM:    addr_flag|=(1<<b_flash);   break;//дflash
										case UNLOCK_PARM:   addr_flag|=(1<<b_unlock);  break;//CONFIG_KУ׼
										case SLEEP_PARM:    addr_flag|=(1<<b_sleep);   break;//sleep
										
										default: tempc=0;EquMent->C_STATUS|=((1<<C_Parm)|(1<<C_Ok));//�����Ƿ�+ʧ��
										                 EquMent->C_STATUS&=~(1<<C_Exe);//���																	 
										break;
									}
						}						
						else //��������
						{	
							if( (AddrMap.paddr>=RW_Bank0_L&&AddrMap.paddr<=RW_Bank0_R) || \
													(AddrMap.paddr>=RW_Bank1_L&&AddrMap.paddr<=RW_Bank1_R) )
									{
										switch(AddrMap.paddr)
										{
											case (uint32_t)&EquMent->FREQ:  //FREQ
													if(((addr_flag>>b_flash)&0x01)){addr_flag&=~(1<<b_flash);flash_data=tempc;flash_flag|=(1<<num_freq);}
													else                           { flash_data=0;    flash_flag=0;             }break;	
													
											case (uint32_t)&EquMent->M_PART: //M_PART                                   M_PART�����2λ so &0x03
													if(((addr_flag>>b_flash)&0x01)){ addr_flag&=~(1<<b_flash);flash_data=tempc&0x03;flash_flag|=(1<<num_m_part);}
													else                           { flash_data=0;    flash_flag=0;               }break;
													
											case (uint32_t)&EquMent->CONFIG_K://CONFIG_K				  
													if(((addr_flag>>b_unlock)&0x01)){ *((uint32_t*)AddrMap.paddr)=tempc; addr_flag&=~(1<<b_unlock);
																													   EquMent->C_STATUS&=~((1<<C_Exe)|(1<<C_Ok));//���+ִ�гɹ�
																													}
													else {
													      EquMent->C_STATUS|=(1<<C_Ok);//ִ��ʧ��
				                        EquMent->C_STATUS&=~(1<<C_Exe);//���
													     }break;											
											default:*((uint32_t*)AddrMap.paddr)=tempc; EquMent->C_STATUS=0; //������											            										
													break;	
										}
									}
						  AddrMap.paddr=AddrMap.paddr+4;	//addr+1
									if(AddrMap.paddr>=WRITE_LAST) AddrMap.paddr=WRITE_LAST; 
						}
					}		
    num_data++;
    }
		
    if(I2C_ReadInt_Stete(I2C_RD_REQ) == 1) //��������������
    {
					I2C_CleraIntState(I2C_RD_REQ);		
					if(((addr_flag>>ISMODE)&0x01))
					{
					  addr_flag&=~(1<<ISMODE); //��ģʽ��ѯ
						I2C_SendByte(0xA0); //����DATA			
					}
					else
					{
			    if(AddrMap.paddr>=READ_LAST) AddrMap.paddr=READ_LAST;							
					I2C_SendByte(*((uint32_t*)AddrMap.paddr)); //����DATA								
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
//			    temp = I2C0->I2C_CLR_MAT_SAR & BIT(0); //���ƥ�份�ѱ�־λ
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
