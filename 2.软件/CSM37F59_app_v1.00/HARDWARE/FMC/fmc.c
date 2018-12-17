#include "fmc.h"
#include "addr_map.h"
#include "CS1258.h"
/**
  * @brief  fmc��ʼ��
  * @param  None
  * @retval None
  */

uint8_t flash_data=0;//Ҫд��flash������ FREQ PART
uint8_t flash_flag=0;

__align(4) uint8_t FMC_Data[512];     //���������
__align(4) uint8_t Temp_FMC_Data[512];//��ת�Ƚ���
__align(4) uint8_t Default_Data[32]=                //����Ĭ��
									{0x08,0xff,0xff,0xff,  //FREQ           0
									 0x02,0xff,0xff,0xff,  //M_PART         4
									 0x00,0xff,0xff,0xff,  //FREQ1K_VAL_H  8
									 0x00,0xff,0xff,0xff,  //FREQ1K_VAL_L  12
									 0x00,0xff,0xff,0xff,  //FREQ2K_VAL_H  16
									 0x00,0xff,0xff,0xff,  //FREQ2K_VAL_L  20
									 0x00,0xff,0xff,0xff,  //FREQ3K_VAL_H  24
									 0x00,0xff,0xff,0xff};//FREQ3K_VAL_L  28
void User_FMC_Init(void)
{
    FMC_InitTypeDef FMC_InitStruct;
	  RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_ISP , ENABLE);
      
    FMC_InitStruct.ISP_Freq = ISP_Freq_24MHz;
    FMC_InitStruct.Enter_DeepStandby = DISABLE;
    FMC_InitStruct.APROM_Update = ENABLE;
    FMC_InitStruct.LDROM_Update = ENABLE;
    FMC_InitStruct.CFG_Update = DISABLE;
    
    FMC_Init(&FMC_InitStruct);
}

//���� 
//[FREQ] [M_PART] [FREQ1K_VAL] [FREQ2K_VAL] [FREQ3K_VAL]
void load_fmc_data(void)
{	
	  uint16_t i;	  
	  //����freq��part��k1H��k1L��k2H��k2L��k3H��k3L (8)
    FMC_ReadPage(FMC_ADDR,32,FMC_Data); //������ 0xEE00 32byte
	
	  if(FMC_Data[0]==0xff || (FMC_Data[24]==0xff && FMC_Data[28]==0xff)) //����Ĭ������ 
		{
			FMC_ReadPage(FMC_ADDR,512,FMC_Data); //�ȶ�����������������			
		  FMC_ErasePage(FMC_ADDR);             //����	512
			
			for(i=0;i<32;i+=4)//��Ĭ�����ݸ���
			{
			  FMC_Data[i]=Default_Data[i];
			}
			
			FMC_WritePage(FMC_ADDR,512,FMC_Data);//д����    
			FMC_ReadPage (FMC_ADDR,512,FMC_Data);//������
		}
		
		//load
		EquMent->FREQ         = FMC_Data[0];  //freq
		EquMent->M_PART       = FMC_Data[4];  //part
		EquMent->FREQ1K_VAL_H = FMC_Data[8];  //1Ƶkֵ H
		EquMent->FREQ1K_VAL_L = FMC_Data[12]; //1Ƶkֵ L
		EquMent->FREQ2K_VAL_H = FMC_Data[16]; //2Ƶkֵ H
		EquMent->FREQ2K_VAL_L = FMC_Data[20]; //2Ƶkֵ L
		EquMent->FREQ3K_VAL_H = FMC_Data[24]; //3Ƶkֵ H
		EquMent->FREQ3K_VAL_L = FMC_Data[28]; //3Ƶkֵ L
}

//type=0,8
//type=1,16
BOOL Cmd_WriteTypeByteToFlash(uint16_t data,uint8_t flash_num,uint8_t type)
{     
	 if(type==0){ //data��8bit
	  	FMC_ReadPage(FMC_ADDR,512,FMC_Data);      //������
	    FMC_ErasePage(FMC_ADDR);                      //����
	
	    Temp_FMC_Data[flash_num]=FMC_Data[flash_num]=(uint8_t)data; //��data����
	    FMC_WritePage(FMC_ADDR,512,FMC_Data); //д����  
			
	    FMC_ReadPage(FMC_ADDR,512,FMC_Data); //�ٶ�����

	    if(FMC_Data[flash_num]!=Temp_FMC_Data[flash_num]) //����
			{
				  EquMent->C_STATUS|=(1<<C_Ok);//ִ��ʧ��
				  EquMent->C_STATUS&=~(1<<C_Exe);//���
				  return FALSE;
			}
		  EquMent->C_STATUS&=~((1<<C_Exe)|(1<<C_Ok));//���+ִ�гɹ�
		 return TRUE;  
	}
	 else{   //data��16bit	 
	  	FMC_ReadPage(FMC_ADDR,512,FMC_Data);      //������
	    FMC_ErasePage(FMC_ADDR);                      //����
	    //�ȴ��8�ٴ��8
	    Temp_FMC_Data[flash_num]=FMC_Data[flash_num]=(uint8_t)(data>>8); //��data��8����
		  Temp_FMC_Data[(flash_num+4)]=FMC_Data[(flash_num+4)]=(uint8_t)(data&0xff); //��data��8����
	    FMC_WritePage(FMC_ADDR,512,FMC_Data); //д����  
			
	    FMC_ReadPage(FMC_ADDR,512,FMC_Data); //�ٶ�����

	    if(FMC_Data[flash_num]!=Temp_FMC_Data[flash_num] || FMC_Data[(flash_num+4)]!=Temp_FMC_Data[(flash_num+4)]) //����
			{
				  EquMent->C_STATUS|=(1<<C_Ok);//ִ��ʧ��
				  EquMent->C_STATUS&=~(1<<C_Exe);//���
				  return FALSE;
			}
		  EquMent->C_STATUS&=~((1<<C_Exe)|(1<<C_Ok));//���+ִ�гɹ�
		 return TRUE;  	 
	 }
}

void Check_Flash_Cmd(uint8_t data)
{
		if((flash_flag>>num_freq)&0x01) //0
		{
			flash_flag&=~(1<<num_freq);
			if(Cmd_WriteTypeByteToFlash(data,(N_FREQ<<2),0)==FALSE)
				return;
			
			EquMent->FREQ=FMC_Data[(N_FREQ<<2)];			
		  tab_ref_test();
			
			EquMent->Z_STATUS&=~(1<<Z_REDY); //clr ģ�������־		
			BIA_FLAG&=~(1<<GetRef); 		
//      BIA_FLAG&=~(1<<Enable_init);	
			
		}
			
		if((flash_flag>>num_m_part)&0x01) //1
		{
			flash_flag&=~(1<<num_m_part);
			if(Cmd_WriteTypeByteToFlash(data,(N_PART<<2),0)==FALSE)
				return;
			
			EquMent->M_PART=FMC_Data[(N_PART<<2)];			
		  tab_ref_test();	
			
		}

}

//����ID�� 14
void load_id_data(void)
{
	__align(4) uint8_t ID_Data[4]; //ID ��
	
	uint8_t i;	

	uint32_t* p=(uint32_t* )EquInfo;
	
	for(i=0;i<8;i++) //N_M_HH~N_S_LL 8��
	{
	FMC_ReadPage((ID_ADDR+(i<<2)),4,ID_Data); //mcu 1258 ��8��
	*(p+i) = ID_Data[0];
	}
  
	EquInfo->HW_VER = 0x01; //Ӳ���汾��
	EquInfo->S_BODY = 0x01; //50k ȫ���㷨��ͨ�汾
	
	//����aprom���屾�����汾��boot�汾��У����511
	FMC_ReadPage(APROM_ADDR,4,ID_Data); //����aprom���屾�����汾 1 2 
	EquInfo->APROM_H=ID_Data[0];
	EquInfo->APROM_L=ID_Data[1];
	
	FMC_ReadPage(BOOT_ADDR,4,ID_Data); //boot	1 ?????????????????????
	EquInfo->BOOT_VER=ID_Data[0];
	
	FMC_ReadPage(CHECK_ADDR,4,ID_Data); //У����511 4
	EquInfo->CHECK_SUM=ID_Data[3];	
	
  //�����㷨�汾��Ϣ
	///
}
