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
    Flag_WaitTime = 1;//100ms��ʱʱ�䵽    
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
	
    if(I2C_ReadInt_Stete(I2C_R_START) == 1) //start �ź�
    {    
			I2C_CleraIntState(I2C_R_START);
        if(IIC_ReCount < 2) //IIC_ReCount��Ϊ0˵��ǰ����ܹ����ݣ����С��2˵����д��ַ��δ�Ϸ�
        {IIC_HostRWAddr = 0xF1F1;}  
            
        IIC_ReCount = 0;
        IIC_ReDataFinsh = 0;       
    }
		
    if(I2C_ReadInt_Stete(I2C_R_STOP) == 1) //stop �ź�
    {
			  I2C_CleraIntState(I2C_R_STOP);
//			  IIC_ReCount = 0;
        IIC_ReDataFinsh = 1;   //���ݽ�����ɱ����λ      
    }
		
		//////////////////////////////////////////////////////
		
    if(I2C_ReadInt_Stete(I2C_RX_FULL) == 1) //���յ�����
		{
			I2C_CleraIntState(I2C_RX_FULL);
				temp = I2C_ReadByte();
		
				if(IIC_ReCount<2) {IIC_Buf[IIC_ReCount] = temp;}//ǰ�����ֽ�Ϊ������ַ
				else //����
				{
           Code_IIC_Buf0[IIC_ReCount-2] = temp;  
           IIC_WriteflashCmd = 1;				
				}
				IIC_ReCount++;
				
				if(IIC_ReCount>=513) {IIC_ReCount = 513;}//��ֹ���
        if(IIC_ReCount==2)  {IIC_HostRWAddr = (IIC_Buf[0]<<8) | (IIC_Buf[1]);}//����������ַ
		}	
		
    if(I2C_ReadInt_Stete(I2C_RD_REQ) == 1) //��������������
    {
        I2C_CleraIntState(I2C_RD_REQ);
        if(IIC_HostRWAddr == 0xF1F1){for(i=0;i<4;i++){read_buf[i] = 0xff;}}       //��֮ǰû�з��ͼĴ�����ַ��ֻ������1λ
			  else
				{  
					  if(IIC_HostRWAddr <= 0xefff) //apromѰַ��Χ
						{
		//						    FMC_ReadPage((IIC_HostRWAddr+IIC_ReCount), 4, read_buf); //��һ��4��byte 
									FMC_ReadPage((IIC_HostRWAddr+IIC_ReCount), 4, REread_buf);	
//									if((IIC_HostRWAddr+IIC_ReCount)>=0xEC00)
									{
										read_buf[0]=REread_buf[0];
										read_buf[1]=REread_buf[1];
										read_buf[2]=REread_buf[2];
										read_buf[3]=REread_buf[3]; //[0xEC00~0xEE00) У����������  
									}		
//									else
//									{
//										read_buf[0]=REread_buf[3];
//										read_buf[1]=REread_buf[2];
//										read_buf[2]=REread_buf[1];
//										read_buf[3]=REread_buf[0]; //������������bin 							
//									}
										IIC_ReCount += 4;	
						}
						 if(IIC_HostRWAddr == 0xf000) //boot mode
						{
									for(i=0;i<4;i++){read_buf[i] =0xB0;}
						}
             if(IIC_HostRWAddr == 0xffff)//��ȡ�汾�ű��
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
