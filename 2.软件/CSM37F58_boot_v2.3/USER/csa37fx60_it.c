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
#include "utimer.h" 
 
////NMI_Handler
//void NMI_Handler(void)
//{


//}

////HardFault_Handler
//void HardFault_Handler(void)
//{


//}

////SVC_Handler
//void SVC_Handler(void)
//{


//}

////PendSV_Handler
//void PendSV_Handler(void)
//{


//}

////SysTick_Handler
//void SysTick_Handler(void)
//{

//	
//}

////BOD_IRQHandler
//void BOD_IRQHandler(void)
//{

//		
//}

////WDT_IRQHandler
//void WDT_IRQHandler(void)
//{


//}
#include "utimer.h" 
//TMR0_IRQHandler
void TMR0_IRQHandler(void)
{  
    Timer_ClearIEState(Timer_0);   
    Flag_WaitTime = 1;//100ms定时时间到    
}

////TMR1_IRQHandler
//void TMR1_IRQHandler(void)
//{

//}


////UART0_IRQHandler
//void UART0_IRQHandler(void)
//{

//}

//I2C0_IRQHandler
#include "boot.h" 

void I2C0_IRQHandler(void)
{
    uint8_t temp = 0;
    uint16_t i = 0;   
    __align(4) uint8_t read_buf[4];
	  __align(4) uint8_t REread_buf[4];
	
    if(I2C_ReadInt_Stete(I2C_R_START) == 1) //start 信号
    {    
			I2C_CleraIntState(I2C_R_START);
        if(IIC_ReCount < 2) //IIC_ReCount不为0说明前面接受过数据，如果小于2说明读写地址尚未合法
        {IIC_HostRWAddr = 0xF1F1;}  
            
        IIC_ReCount = 0;
        IIC_ReDataFinsh = 0;       
    }
		
    if(I2C_ReadInt_Stete(I2C_R_STOP) == 1) //stop 信号
    {
			  I2C_CleraIntState(I2C_R_STOP);
//			  IIC_ReCount = 0;
        IIC_ReDataFinsh = 1;   //数据接收完成标记置位      
    }
		
		//////////////////////////////////////////////////////
		
    if(I2C_ReadInt_Stete(I2C_RX_FULL) == 1) //接收到数据
		{
			I2C_CleraIntState(I2C_RX_FULL);
				temp = I2C_ReadByte();
		
				if(IIC_ReCount<2) {IIC_Buf[IIC_ReCount] = temp;}//前两个字节为操作地址
				else //数据
				{
           Code_IIC_Buf0[IIC_ReCount-2] = temp;  
           IIC_WriteflashCmd = 1;				
				}
				IIC_ReCount++;
				
				if(IIC_ReCount>=513) {IIC_ReCount = 513;}//防止溢出
        if(IIC_ReCount==2)  {IIC_HostRWAddr = (IIC_Buf[0]<<8) | (IIC_Buf[1]);}//解析操作地址
		}	
		
    if(I2C_ReadInt_Stete(I2C_RD_REQ) == 1) //主机读数据请求
    {
        I2C_CleraIntState(I2C_RD_REQ);
        if(IIC_HostRWAddr == 0xF1F1){for(i=0;i<4;i++){read_buf[i] = 0xff;}}       //读之前没有发送寄存器地址或只发送了1位
			  else
				{  
					  if(IIC_HostRWAddr <= 0xefff) //aprom寻址范围
						{
		//						    FMC_ReadPage((IIC_HostRWAddr+IIC_ReCount), 4, read_buf); //读一次4个byte 
									FMC_ReadPage((IIC_HostRWAddr+IIC_ReCount), 4, REread_buf);	
//									if((IIC_HostRWAddr+IIC_ReCount)>=0xEC00)
									{
										read_buf[0]=REread_buf[0];
										read_buf[1]=REread_buf[1];
										read_buf[2]=REread_buf[2];
										read_buf[3]=REread_buf[3]; //[0xEC00~0xEE00) 校验区不调整  
									}		
//									else
//									{
//										read_buf[0]=REread_buf[3];
//										read_buf[1]=REread_buf[2];
//										read_buf[2]=REread_buf[1];
//										read_buf[3]=REread_buf[0]; //程序区调整回bin 							
//									}
										IIC_ReCount += 4;	
						}
						 if(IIC_HostRWAddr == 0xf000) //boot mode
						{
									for(i=0;i<4;i++){read_buf[i] =0xB0;}
						}
             if(IIC_HostRWAddr == 0xffff)//读取版本号标记
            {
							  FMC_ReadPage(0xEDFC, 4, read_buf);
                read_buf[0]= APROM_Major;
                read_buf[1]= APROM_Minor;               
                read_buf[2]= LDROM_MAJOR;
             // read_buf[3]= LDROM_MINOR;//checksum
            } 						
				}
			I2C_SendMoreByte(read_buf, 4);
			IIC_WriteflashCmd = 0;	
		}    	  
}

////AFE0_IRQHandler
//void AFE0_IRQHandler(void)
//{

//}

////AFE1_IRQHandler
//void AFE1_IRQHandler(void)
//{

//}

////PD_WU_IRQHandler
//void PD_WU_IRQHandler(void)
//{

//}

////Default_IRQHandler
//void Default_IRQHandler(void)
//{

//}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
