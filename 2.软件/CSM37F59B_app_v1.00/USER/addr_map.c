
#include "addr_map.h"

AddrMap_TypeDef AddrMap;
/**
  * @brief  ��ַӳ�� �����û�����ĸߵ�ַ�͵͵�ַ�ҵ��ڲ���Ӧ�ĵ�ַ
  * @param  uint16_t user_addr
	          �û�����ߵ�ַ���͵�ַ
  * @retval �ڲ���ַ
  */
uint8_t addr_flag=0;

uint32_t a[64+24+128+128+128+128+24+128] __at(0x20001000);

void addr_map(uint16_t user_addr)
{
	uint32_t temp;
	
	addr_flag&=~(1<<ISCMD);  //Ĭ���ǵ�ַ
		
	temp=user_addr+SRAM_BASE;	//+0x20000000
								
	if(temp==(SRAM_BASE+USER_CMD))
	{
		addr_flag|=(1<<ISCMD);  //������
//		AddrMap.paddr=temp;
	  return;
	}
	else if(temp==(SRAM_BASE+MODE_CMD))
	{
		addr_flag|=(1<<ISMODE);  //��ģʽ
//		AddrMap.paddr=temp;
	  return;
	}	
	
	//�豸������(RW)0x20001000~0x2000103F
	else if(temp>=U_EquipmentConfig_BASE && temp<=U_EquipmentConfig_END)
	{
		AddrMap.paddr=((temp-U_EquipmentConfig_BASE)<<2) + EquipmentConfig_BASE;
		return;
	}
	//�豸��Ϣ��(R)0x20001040~0x20001057
	else if(temp>=U_EquipmentInfo_BASE && temp<=U_EquipmentInfo_END)
	{
		AddrMap.paddr=((temp-U_EquipmentInfo_BASE)<<2) + EquipmentInfo_BASE;	
		return;
	}
	//�û���Ϣ��(RW)0x20001058~0x200010D7
	else if(temp>=U_UserInfo_BASE && temp<=U_UserInfo_END)
	{
		AddrMap.paddr=((temp-U_UserInfo_BASE)<<2) + UserInfo_BASE;		
		return;
	}
	//�û�����BIA(R)0x200010D8~0x20001157
	else if(temp>=U_UserBIAPart_BASE && temp<=U_UserBIAPart_END)
	{
		AddrMap.paddr=((temp-U_UserBIAPart_BASE)<<2) + UserBIAPart_BASE;		
		return;
	}
	//�ɷֽ��(R)0x20001158~0x200011D7
	else if(temp>=U_Analysis_BASE && temp<=U_Analysis_END)
	{
		AddrMap.paddr=((temp-U_Analysis_BASE)<<2) + Analysis_BASE;		
		return;
	}
	//���Թ�������(R)0x200011D8~0x20001257
	else if(temp>=U_ADCVal_BASE && temp<=U_ADCVal_END)
	{
		AddrMap.paddr=((temp-U_ADCVal_BASE)<<2) + ADCVal_BASE;	
//		AddrMap.paddr=Log_BASE;	
		return;
	}
	//log
	else if(temp>=U_Log_BASE && temp<=U_Log_END)
	{
		AddrMap.paddr=Log_BASE;
		return;
	}
	//��ʵ������(R)0x20001270~0x200012EF
	else if(temp>=U_RESVal_BASE && temp<=U_RESVal_END)
	{
		AddrMap.paddr=((temp-U_RESVal_BASE)<<2) + RESVal_BASE;		
//		AddrMap.paddr=Log_BASE;	
		return;
	}	
	else
		AddrMap.paddr=Log_BASE;
		return;
}

// ����data 
//void addr_data(uint8_t data)
//{
//	uint32_t* temp;
//	
//	temp=(uint32_t*)AddrMap->paddr;
//	
//	*temp=data;
//	
//  AddrMap->paddr++;
//}


//���ram
void Clr_All_Block_Ram(void)
{
		uint32_t* clear_start;  //��ʼָ��
	  clear_start=(uint32_t*)EquipmentConfig_BASE; //ָ��ʼaddr	
	  do{
		*clear_start++=0;
		}while(LastBlock_BASE+(Sizeof_LastBlock<<2)-4-(uint32_t)clear_start);
		*clear_start++=0;

}

void Clr_UserBIAPart_Ram(void)
{
		uint32_t* clear_start;  //��ʼָ��
	  clear_start=(uint32_t*)UserBIAPart_BASE; //ָ��ʼaddr	
	  do{
		*clear_start++=0;
		}while(UserBIAPart_END-(uint32_t)clear_start);
		*clear_start++=0;
}


void Clr_Analysis_Ram(void)
{
		uint32_t* clear_start;  //��ʼָ��
	  clear_start=(uint32_t*)Analysis_BASE; //ָ��ʼaddr	
	  do{
		*clear_start++=0;
		}while(Analysis_END-(uint32_t)clear_start);
		*clear_start++=0;

}

//ע��123Ƶ���ڶ� r0 r1������
void Clr_ADCVal_Ram(void)
{
		uint32_t* clear_start;  //��ʼָ��
	  //1Ƶ
	  clear_start=&ADCVal->Freq1_Z12_AD_H;
	  do{
		*clear_start++=0;
		}while((uint32_t)&ADCVal->Freq1_Z12_AD_H+(12<<2)-(uint32_t)clear_start);
		
	  //2Ƶ
		clear_start=&ADCVal->Freq2_Z12_AD_H;
	  do{
		*clear_start++=0;
		}while((uint32_t)&ADCVal->Freq2_Z12_AD_H+(12<<2)-(uint32_t)clear_start);
		
	  //3Ƶ
		clear_start=&ADCVal->Freq3_Z12_AD_H;
	  do{
		*clear_start++=0;
		}//while((uint32_t)&ADCVal->Freq3_Z12_AD_H+(12<<2)-(uint32_t)clear_start);	
		while(ADCVal_END-(uint32_t)clear_start);	
		*clear_start++=0;
}

void Clr_RESVal_Ram(void)
{
		uint32_t* clear_start;  //��ʼָ��
	  clear_start=(uint32_t*)RESVal_BASE; //ָ��ʼaddr	
	  do{
		*clear_start++=0;
		}while(RESVal_END-(uint32_t)clear_start);
		*clear_start++=0;
}


void Clr_UsrInfo_ResF1(void)
{
	 uint32_t* clear_start;  //��ʼָ��

		 clear_start=&UsrInfo->F1_All_Res_H;
		 do{
			 *clear_start++=0;
		 }while((uint32_t)&UsrInfo->F1_All_Res_H+(12<<2) -(uint32_t)clear_start);
	   *clear_start++=0;
}

void Clr_UsrInfo_ResF2(void)
{
	 uint32_t* clear_start;  //��ʼָ��

		 clear_start=&UsrInfo->F2_All_Res_H;
		 do{
			 *clear_start++=0;
		 }while((uint32_t)&UsrInfo->F2_All_Res_H+(12<<2) -(uint32_t)clear_start);
	   *clear_start++=0;
}

void Clr_UsrInfo_ResF3(void)
{
	 uint32_t* clear_start;  //��ʼָ��

		 clear_start=&UsrInfo->F3_All_Res_H;
		 do{
			 *clear_start++=0;
		 }while((uint32_t)&UsrInfo->F3_All_Res_H+(12<<2) -(uint32_t)clear_start);
	   *clear_start++=0;
}
