
#include "analysis.h"

//��Ƶ50k�㷨
//1.�ֲ�---��ͨ
//2.�ֲ�---�˶�
//3.�Ų�---��ͨ
//4.�Ų�---�˶�
//5.ȫ��---��ͨ
//6.ȫ��---�˶�
//7.�����㷨


		//�������
	 uint8_t B_SP_Mode; //ģʽ
	 uint8_t B_SEX; //�Ա� 1 man 0 weman
	 uint8_t B_Age; //����
	 uint16_t  B_H;   //��� cm
	 uint16_t  B_Wt;  //���� kg   
	 uint16_t  B_Z_12;
	 uint16_t  B_Z_13;
	 uint16_t  B_Z_14;
	 uint16_t  B_Z_23;
	 uint16_t  B_Z_24;
	 uint16_t  B_Z_34;

BOOL analysis_parm(void)
{	
	if((addr_flag>>b_analysis)&0x01)  //if 1
	{
			addr_flag&=~(1<<b_analysis);
			
		//1.�ֱ�����ߡ����ء����䡢�Ա��迹�������
		  B_SEX=(UsrInfo->SAGE&0x80)>>7; 
			B_Age=UsrInfo->SAGE&0x7F;
			B_H=(uint16_t)UsrInfo->HT; 
			B_Wt=(uint16_t)get2byte(UsrInfo->WTH,UsrInfo->WTL,L); //kg 		
      B_SP_Mode=0x00;
		
//      B_Z_12=get2byte(RESVal->F1_Z12_RES_H,RESVal->F1_Z12_RES_L,L)/10.0;
//		  B_Z_13=get2byte(RESVal->F1_Z13_RES_H,RESVal->F1_Z13_RES_L,L)/10.0;
//		  B_Z_14=get2byte(RESVal->F1_Z14_RES_H,RESVal->F1_Z14_RES_L,L)/10.0;
//		  B_Z_23=get2byte(RESVal->F1_Z23_RES_H,RESVal->F1_Z23_RES_L,L)/10.0;
//		  B_Z_34=get2byte(RESVal->F1_Z34_RES_H,RESVal->F1_Z34_RES_L,L)/10.0;
//		  B_Z_24=get2byte(RESVal->F1_Z24_RES_H,RESVal->F1_Z24_RES_L,L)/10.0;
      B_Z_12=get2byte(UsrBIAP->Freq1_Z12_Res_H,UsrBIAP->Freq1_Z12_Res_L,L)/10.0;
		  B_Z_13=get2byte(UsrBIAP->Freq1_Z13_Res_H,UsrBIAP->Freq1_Z13_Res_L,L)/10.0;
		  B_Z_14=get2byte(UsrBIAP->Freq1_Z14_Res_H,UsrBIAP->Freq1_Z14_Res_L,L)/10.0;
		  B_Z_23=get2byte(UsrBIAP->Freq1_Z23_Res_H,UsrBIAP->Freq1_Z23_Res_L,L)/10.0;
		  B_Z_34=get2byte(UsrBIAP->Freq1_Z34_Res_H,UsrBIAP->Freq1_Z34_Res_L,L)/10.0;
		  B_Z_24=get2byte(UsrBIAP->Freq1_Z24_Res_H,UsrBIAP->Freq1_Z24_Res_L,L)/10.0;
			
		//2.���������Χ�ж� ��� ���� ���� �迹 Ƶ��(50k)    
	  if(B_Wt>WEIGHT_MAX || B_Wt<WEIGHT_MIN ||\
			 B_H>HT_MAX || B_H<HT_MIN ||\
		   B_Age>AGE_MAX || B_Age<AGE_MIN ||\
		   B_Z_34>(RES_MAX/10) || B_Z_34<(RES_MIN/10) ||\
			 B_Z_24>(RES_MAX/10) || B_Z_24<(RES_MIN/10) ||\
		   B_Z_23>(RES_MAX/10) || B_Z_23<(RES_MIN/10) ||\
		   B_Z_14>(RES_MAX/10) || B_Z_14<(RES_MIN/10) ||\
		   B_Z_13>(RES_MAX/10) || B_Z_13<(RES_MIN/10) ||\
		   B_Z_12>(RES_MAX/10) || B_Z_12<(RES_MIN12/10) ||\
		   freq[0]!=__50KHz
			) //W H Age Z f ��Χ	   		   		
		  {
				EquMent->ERR_STATUS|=(1<<Err_Parm);//��������Ƿ�
				EquMent->C_STATUS|=(1<<C_Ok);   //ִ��ʧ��
				EquMent->C_STATUS&=~(1<<C_Exe); //���
				return FALSE;
			}
			
		//3.�㷨ѡ��
		if(test_sta==HAND_1)
		{
			 //��ͨ
			 //�˶�Ա	
			return TRUE;
		}
		else if(test_sta==LEG_1)
		{
			 //��ͨ
			 //�˶�Ա	
			return TRUE;		
		}
		else if(test_sta==BODY_1)
		{
			   //C_BIA_C432(B_SP_Mode,B_SEX,B_Age,B_H,B_Wt,B_Z_12,B_Z_13,B_Z_14,B_Z_23,B_Z_24,B_Z_34); //ȫ����ͨ
         if( C_BIAS_V433(B_SEX,B_Age,B_H,B_Wt,B_Z_12,B_Z_13,B_Z_14,B_Z_23,B_Z_24,B_Z_34) >0 )     //; //ȫ����ͨ
				 {
						EquMent->ERR_STATUS|=(1<<Err_Parm);//��������Ƿ�
						EquMent->C_STATUS|=(1<<C_Ok);   //ִ��ʧ��
						EquMent->C_STATUS&=~(1<<C_Exe); //���
						return FALSE;				 
				 }
				 
			   EquMent->C_STATUS&=~((1<<C_Exe)|(1<<C_Ok));//���+ִ�гɹ�
				 //������� 
			
			   //�ɷ���� 6
				 Analys->BFP_H = get1byte((uint32_t)(B_BFP*10),HL);
				 Analys->BFP_L = get1byte((uint32_t)(B_BFP*10),LL);     //��֬��*10  

				 Analys->SLM_H = get1byte((uint32_t)(B_SLM*10),HL);  
				 Analys->SLM_L = get1byte((uint32_t)(B_SLM*10),LL);  	//������ *

				 Analys->BMC_H = get1byte((uint32_t)(B_BMC*10),HL);  
				 Analys->BMC_L = get1byte((uint32_t)(B_BMC*10),LL);	  //������ *		

				 Analys->BWP_H = get1byte((uint32_t)(B_BWP*10),HL);  
				 Analys->BWP_L = get1byte((uint32_t)(B_BWP*10),LL);  	//��ˮ����
				 
				 Analys->PP_H = get1byte((uint32_t)(B_PP*10),HL);  
				 Analys->PP_L = get1byte((uint32_t)(B_PP*10),LL);		 //�������� ���������û����м��� ������ = ���� * B_PP

				 Analys->SMM_H = get1byte((uint32_t)(B_SMM*10),HL);  
				 Analys->SMM_L = get1byte((uint32_t)(B_SMM*10),LL);      //��������

				 //Analys->TF_H= get1byte((uint32_t)(B_TF*10),HL);  
				 //Analys->TF_L= get1byte((uint32_t)(B_TF*10),LL); 		//��ˮ�� �û����м��� ��ˮ�� = ���� * B_BWP			
			
				 //Analys->LBM_H = get1byte((uint32_t)(B_LBM*10),HL);  
				 //Analys->LBM_L = get1byte((uint32_t)(B_LBM*10),LL);	 //ȥ֬���� �û����м��� ȥ֬���� = ���� - ���� * B_BFR
			
				 //Analys->FM_H = get1byte((uint32_t)(B_FM*10),HL);  
				 //Analys->FM_L = get1byte((uint32_t)(B_FM*10),LL);  	  //֬����  �û����м��� ֬���� = ���� * B_BFR
			
			
         //������ܲ��� 9
				 Analys->BMR_H = get1byte(B_BMR,HL);  
				 Analys->BMR_L = get1byte(B_BMR,LL);				            //������л

				 Analys->VFR_H = get1byte((uint32_t)(B_VFR*10),HL);  
				 Analys->VFR_L = get1byte((uint32_t)(B_VFR*10),LL);    //����֬���ȼ�	

				 Analys->MA = B_MA;                                    //��������	

				 Analys->BMI_H = get1byte((uint32_t)(B_BMI*10),HL);  
				 Analys->BMI_L = get1byte((uint32_t)(B_BMI*10),LL);    //����ָ��
							
				 Analys->SBC = B_SBC;                                  //��������

				 Analys->BW_H= get1byte((uint32_t)(B_BW*10),HL);  
				 Analys->BW_L= get1byte((uint32_t)(B_BW*10),LL);	     //��׼����	

				 if(B_WC>0)                                            //���ؿ���
				 {
				 Analys->WC_H= get1byte((uint32_t)(B_WC*10),HL);  
				 Analys->WC_L= get1byte((uint32_t)(B_WC*10),LL);			 
				 }
				 else
				 {
				 Analys->WC_H= get1byte((uint32_t)(B_WC*(-10)),HL)+0x80;  
				 Analys->WC_L= get1byte((uint32_t)(B_WC*(-10)),LL);			 
				 }

				 if(B_MC>0)                                         //�������	
				 {
				 Analys->MC_H= get1byte((uint32_t)(B_MC*10),HL);  
				 Analys->MC_L= get1byte((uint32_t)(B_MC*10),LL);			 
				 }
				 else
				 {
				 Analys->MC_H= get1byte((uint32_t)(B_MC*(-10)),HL)+0x80;  
				 Analys->MC_L= get1byte((uint32_t)(B_MC*(-10)),LL);			 
         }

				 if(B_FC>0)                                         //֬������
				 {
				 Analys->FC_H= get1byte((uint32_t)(B_FC*10),HL);  
				 Analys->FC_L= get1byte((uint32_t)(B_FC*10),LL);			 
				 }
				 else
				 {
				 Analys->FC_H= get1byte((uint32_t)(B_FC*(-10)),HL)+0x80;  
				 Analys->FC_L= get1byte((uint32_t)(B_FC*(-10)),LL);			 
				 }
				 
         //�ڶβ��� 10
				 Analys->RAFP_H= get1byte((uint32_t)(B_RAFP*10),HL);  
				 Analys->RAFP_L= get1byte((uint32_t)(B_RAFP*10),LL);//Z2 ��֬��

				 Analys->LAFP_H= get1byte((uint32_t)(B_LAFP*10),HL);  
				 Analys->LAFP_L= get1byte((uint32_t)(B_LAFP*10),LL);//Z1 ��֬��			 

				 Analys->RLFP_H= get1byte((uint32_t)(B_RLFP*10),HL);  
				 Analys->RLFP_L= get1byte((uint32_t)(B_RLFP*10),LL);//Z4 ��֬��

				 Analys->LLFP_H= get1byte((uint32_t)(B_LLFP*10),HL);  
				 Analys->LLFP_L= get1byte((uint32_t)(B_LLFP*10),LL);//Z3 ��֬��
				 
				 Analys->TFP_H= get1byte((uint32_t)(B_TFP*10),HL);  
				 Analys->TFP_L= get1byte((uint32_t)(B_TFP*10),LL);//Z5 ��֬��	 


				 Analys->RAMM_H= get1byte((uint32_t)(B_RAMM*10),HL);  
				 Analys->RAMM_L= get1byte((uint32_t)(B_RAMM*10),LL);//Z2 ������

				 Analys->LAMM_H= get1byte((uint32_t)(B_LAMM*10),HL);  
				 Analys->LAMM_L= get1byte((uint32_t)(B_LAMM*10),LL);//Z1 ������
				 
				 Analys->RLMM_H= get1byte((uint32_t)(B_RLMM*10),HL);  
				 Analys->RLMM_L= get1byte((uint32_t)(B_RLMM*10),LL);//Z4 ������
				 
				 Analys->LLMM_H= get1byte((uint32_t)(B_LLMM*10),HL);  
				 Analys->LLMM_L= get1byte((uint32_t)(B_LLMM*10),LL);//Z3 ������
				 
				 Analys->TMM_H= get1byte((uint32_t)(B_TMM*10),HL);  
				 Analys->TMM_L= get1byte((uint32_t)(B_TMM*10),LL);//Z5 ������
									 
				 Analys->WHR_H= get1byte((uint32_t)(B_WHR*100),HL);  
				 Analys->WHR_L= get1byte((uint32_t)(B_WHR*100),LL);//���α�				 


				 //Analys->EXF_H= get1byte((uint32_t)(B_EXF*10),HL);  
				 //Analys->EXF_L= get1byte((uint32_t)(B_EXF*10),LL);	 //ϸ����Һ	
				 
				 //Analys->INF_H= get1byte((uint32_t)(B_INF*10),HL);  
				 //Analys->INF_L= get1byte((uint32_t)(B_INF*10),LL);   //ϸ����Һ	  
				 			 
				 
				 //Analys->EE_H= get1byte((uint32_t)(B_EE*10),HL);  
				 //Analys->EE_L= get1byte((uint32_t)(B_EE*10),LL);	   //ˮ�׶�	
				 
				 //Analys->OD_H= get1byte((uint32_t)(B_OD*10),HL);  
				 //Analys->OD_L= get1byte((uint32_t)(B_OD*10),LL);	   //���ֶ�		 
				 
				 
				 //Analys->BM_H= get1byte((uint32_t)(B_BM*10),HL);  
				 //Analys->BM_L= get1byte((uint32_t)(B_BM*10),LL);    //��׼���� 
				 
				 
				 	 
				 //Analys->TW_H= get1byte((uint32_t)(B_TW*10),HL);  
				 //Analys->TW_L= get1byte((uint32_t)(B_TW*10),LL);        //Ŀ������
				 
				 		 
				 //Analys->JW_H= get1byte((uint32_t)(B_JW*10),HL);  
				 //Analys->JW_L= get1byte((uint32_t)(B_JW*10),LL);			 //��Χ
				 
				 //Analys->WL_H= get1byte((uint32_t)(B_WL*10),HL);  
				 //Analys->WL_L= get1byte((uint32_t)(B_WL*10),LL);			 //��Χ
				 
				 //Analys->HL_H= get1byte((uint32_t)(B_HL*10),HL);  
				 //Analys->HL_L= get1byte((uint32_t)(B_HL*10),LL);			 //��Χ
				 
				 
				 
				 //Analys->XW_H= get1byte((uint32_t)(B_XW*10),HL);  
				 //Analys->XW_L= get1byte((uint32_t)(B_XW*10),LL);			 //��Χ
				 
				 //Analys->RAW_H= get1byte((uint32_t)(B_RAW*10),HL);  
				 //Analys->RAW_L= get1byte((uint32_t)(B_RAW*10),LL);			 //Z2 ���ϱ�Χ
				 
				 //Analys->LAW_H= get1byte((uint32_t)(B_LAW*10),HL);  
				 //Analys->LAW_L= get1byte((uint32_t)(B_LAW*10),LL);			 //Z1 ���ϱ�Χ
				 
				 //Analys->RLW_H= get1byte((uint32_t)(B_RLW*10),HL);  
				 //Analys->RLW_L= get1byte((uint32_t)(B_RLW*10),LL);			 //Z4 �Ҵ���Χ
				 
				 //Analys->LLW_H= get1byte((uint32_t)(B_LLW*10),HL);  
				 //Analys->LLW_L= get1byte((uint32_t)(B_LLW*10),LL);			 //Z3 �Ҵ���Χ
				 
				 UsrBIAP->Freq1_Z12_Res_H=UsrBIAP->Freq1_Z12_Res_L=0;
				 UsrBIAP->Freq1_Z34_Res_H=UsrBIAP->Freq1_Z34_Res_L=0;	

				 return TRUE;		 	 
		}	 
	}
  return TRUE;	
}


#ifdef HR_MODE

uint8_t CS125X_XLCL_MODE(uint32_t B_HR_ADC);

//Tx
#ifdef UART_HR
void simuart_sendbyte(uint8_t dat)
{
	     uint8_t j=0;
	
	     SIM_TX_L; //st
	     delay_us(5);
	    
	     for(;j<8;j++)
	     {
						if(((dat>>j)&0x01)) {SIM_TX_H;}
					else {SIM_TX_L;}
					delay_us(5);
			 }
	     
        SIM_TX_H;  //end
			  delay_us(5);
}
#endif

void CS125X_XLCL_Initial_Per(void)
{
			SetFATSDAOutput(FAT_SDA);//���� FAT SDA���		
			SendDataToAddr(ADDR_AFE_ADC1,0x60);//ADC1 0x60  80hz 
	
	    if(test_sta == HAND_1 || test_sta ==HAND_2 || test_sta == HAND_3)				
				{
					SendDataToAddr(ADDR_AFE_BIM0,0x14);//12	  
				}				
			else
			  {
					SendDataToAddr(ADDR_AFE_BIM0,0xBE);//34	  
				} 
			SendDataToAddr(ADDR_AFE_BIM1,0x02);//25k	
	
			SendDataToAddr(ADDR_AFE_SYS,0xCF);//SYS д0xCF ��BIM
			B_temp_XLCL = 0;
}

uint8_t HRI(void)
{
		Timer_Enable(Timer_0); //�򿪶�ʱ��5ms		 
	  //waiting for ready
		wait_out=0;
	  while(GetFATSDAInputStatus(FAT_SDA)==0)  //SDA==0
		 {
		    if(wait_out>5) //100ms
				{
					SendDataToAddr(ADDR_AFE_SYS,0xCE); //SYS д0xCE �ر�BIM		
					return 0;
				}
		 }
		wait_out=0;
	  while(GetFATSDAInputStatus(FAT_SDA)==1)  //SDA==1
		 {
		    if(wait_out>5) //100ms
				{
					SendDataToAddr(ADDR_AFE_SYS,0xCE); //SYS д0xCE �ر�BIM		
					return 0;
				}
		 } 
	  Timer_Disable(Timer_0);//�رն�ʱ��
		 
	  currentADC=ReadADC();                     //read AD
    ///////////		 
		#ifdef UART_HR
		simuart_sendbyte(0x5a); 
		simuart_sendbyte(((currentADC>>16)&0xff)); //H
		simuart_sendbyte(((currentADC>>8)&0xff)); //M
		simuart_sendbyte((currentADC&0xff)); //L
		#endif
		///////////
    return  CS125X_XLCL_MODE(currentADC);
}

#endif
