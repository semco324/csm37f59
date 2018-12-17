#include "sleep.h"


//uint8_t timer_wakeup=0; //定时唤醒  0--睡眠  1--唤醒
//uint8_t tim_wakeup_flag=0; //定时唤醒标志

void check_sleep(void)
{
	  int32_t work_cnt; //唤醒后工作一段时间
	  
		PWR_DeepSleep_InitTypeDef PWR_InitStruct;
	
	  work_cnt=0;
	   if((addr_flag>>b_sleep)&0x01)  //sleep cmd
		 {			 
			      //clr sleep cmd
						addr_flag&=~(1<<b_sleep);	
				 
						EquMent->C_STATUS&=~((1<<C_Exe)|(1<<C_Ok));//完成+执行成功		
           
						PowerDownCS125x();
			 
      			SetDRDY(1); 	    
						Timer_Disable(Timer_0);//关tim
						User_WDT_DISABLE(); //关wdt
			 
					  GPIO_EnPullUp(GPIO_PA11|GPIO_PA12); //开启上拉使能  
			 		 
						PWR_InitStruct.Mode = DeepSleep_Mode2;
						PWR_InitStruct.WakeUp_IntEn = ENABLE;
						PWR_InitStruct.WakeUp_DelayEn = DISABLE;
			 
//			      timer_wakeup=tim_wakeup_flag=0;

						while(1)
						{
							
							//if(timer_wakeup==0)				
							{					            		
							PWR_EnterSleepMode(&PWR_InitStruct, WFI_Mode);
							}						
//              work_cnt++;	
//							timer_wakeup=1;
//              if(work_cnt>100000)
//							{
//								timer_wakeup=0; 
//								work_cnt=0;								
//							}	
						  for(work_cnt=0;work_cnt<100000;work_cnt++);
							
						  if(addr_mat)//if((addr_flag>>b_wakeup)&0x01)//if((addr_flag>>b_wakeup)&0x01) //唤醒
							{		
								  GPIO_DisPullUp(GPIO_PA11|GPIO_PA12); //关闭上拉使能
								  
									_CS1258bug();								
									addr_mat=0;addr_flag&=~(1<<b_wakeup);							  
								  
								  SetDRDY(0);
//								Timer_Disable(Timer_1);//关timer1
								  User_WDT_Init();
									break;								
							}					
						}					
				    timer0_init();					
			      Timer_Enable(Timer_0);
		 }	 	 
}	



void no_use_peripherals(void)
{
	  AFEx_ADPowerClose(AFE0);
		AFEx_ADPowerClose(AFE1);
	  GPIO_CloseInputChannel(GPIO_PA3|GPIO_PA4|GPIO_PA5|
													 GPIO_PA6|GPIO_PA7|GPIO_PA8); //关闭输入通道
		//set io 	
		GPIO_SetMode(GPIO_PA3|GPIO_PA4|GPIO_PA5|GPIO_PA6|GPIO_PA7,GPIO_Mode_OUTPUT);
		GPIO_WriteBits(GPIO_PA3|GPIO_PA4|GPIO_PA5|GPIO_PA6|GPIO_PA7,0);	 
}

////    PowerDownCS125x();
//	  SetFATCS(FAT_CS); //cs=1
//		
//	  SetFATSDAOutput(FAT_SDA);	
//		SetFATSDA(FAT_SDA);
//		while(1);
