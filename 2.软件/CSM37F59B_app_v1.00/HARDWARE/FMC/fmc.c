#include "fmc.h"
#include "addr_map.h"
#include "CS1258.h"
/**
  * @brief  fmc初始化
  * @param  None
  * @retval None
  */

uint8_t flash_data=0;//要写入flash的数据 FREQ PART
uint8_t flash_flag=0;

__align(4) uint8_t FMC_Data[512];     //最后区缓存
__align(4) uint8_t Temp_FMC_Data[512];//中转比较用
__align(4) uint8_t Default_Data[32]=                //出厂默认
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

//加载 
//[FREQ] [M_PART] [FREQ1K_VAL] [FREQ2K_VAL] [FREQ3K_VAL]
void load_fmc_data(void)
{	
	  uint16_t i;	  
	  //加载freq、part、k1H、k1L、k2H、k2L、k3H、k3L (8)
    FMC_ReadPage(FMC_ADDR,32,FMC_Data); //读数据 0xEE00 32byte
	
	  if(FMC_Data[0]==0xff || (FMC_Data[24]==0xff && FMC_Data[28]==0xff)) //则用默认数据 
		{
			FMC_ReadPage(FMC_ADDR,512,FMC_Data); //先读出来保存其他数据			
		  FMC_ErasePage(FMC_ADDR);             //擦除	512
			
			for(i=0;i<32;i+=4)//用默认数据更新
			{
			  FMC_Data[i]=Default_Data[i];
			}
			
			FMC_WritePage(FMC_ADDR,512,FMC_Data);//写数据    
			FMC_ReadPage (FMC_ADDR,512,FMC_Data);//读数据
		}
		
		//load
		EquMent->FREQ         = FMC_Data[0];  //freq
		EquMent->M_PART       = FMC_Data[4];  //part
		EquMent->FREQ1K_VAL_H = FMC_Data[8];  //1频k值 H
		EquMent->FREQ1K_VAL_L = FMC_Data[12]; //1频k值 L
		EquMent->FREQ2K_VAL_H = FMC_Data[16]; //2频k值 H
		EquMent->FREQ2K_VAL_L = FMC_Data[20]; //2频k值 L
		EquMent->FREQ3K_VAL_H = FMC_Data[24]; //3频k值 H
		EquMent->FREQ3K_VAL_L = FMC_Data[28]; //3频k值 L
}

//type=0,8
//type=1,16
BOOL Cmd_WriteTypeByteToFlash(uint16_t data,uint8_t flash_num,uint8_t type)
{     
	 if(type==0){ //data是8bit
	  	FMC_ReadPage(FMC_ADDR,512,FMC_Data);      //读数据
	    FMC_ErasePage(FMC_ADDR);                      //擦除
	
	    Temp_FMC_Data[flash_num]=FMC_Data[flash_num]=(uint8_t)data; //用data更新
	    FMC_WritePage(FMC_ADDR,512,FMC_Data); //写数据  
			
	    FMC_ReadPage(FMC_ADDR,512,FMC_Data); //再读数据

	    if(FMC_Data[flash_num]!=Temp_FMC_Data[flash_num]) //不等
			{
				  EquMent->C_STATUS|=(1<<C_Ok);//执行失败
				  EquMent->C_STATUS&=~(1<<C_Exe);//完成
				  return FALSE;
			}
		  EquMent->C_STATUS&=~((1<<C_Exe)|(1<<C_Ok));//完成+执行成功
		 return TRUE;  
	}
	 else{   //data是16bit	 
	  	FMC_ReadPage(FMC_ADDR,512,FMC_Data);      //读数据
	    FMC_ErasePage(FMC_ADDR);                      //擦除
	    //先存高8再存低8
	    Temp_FMC_Data[flash_num]=FMC_Data[flash_num]=(uint8_t)(data>>8); //用data高8更新
		  Temp_FMC_Data[(flash_num+4)]=FMC_Data[(flash_num+4)]=(uint8_t)(data&0xff); //用data低8更新
	    FMC_WritePage(FMC_ADDR,512,FMC_Data); //写数据  
			
	    FMC_ReadPage(FMC_ADDR,512,FMC_Data); //再读数据

	    if(FMC_Data[flash_num]!=Temp_FMC_Data[flash_num] || FMC_Data[(flash_num+4)]!=Temp_FMC_Data[(flash_num+4)]) //不等
			{
				  EquMent->C_STATUS|=(1<<C_Ok);//执行失败
				  EquMent->C_STATUS&=~(1<<C_Exe);//完成
				  return FALSE;
			}
		  EquMent->C_STATUS&=~((1<<C_Exe)|(1<<C_Ok));//完成+执行成功
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
			
			EquMent->Z_STATUS&=~(1<<Z_REDY); //clr 模块就绪标志		
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

//加载ID号 14
void load_id_data(void)
{
	__align(4) uint8_t ID_Data[4]; //ID 号
	
	uint8_t i;	

	uint32_t* p=(uint32_t* )EquInfo;
	
	for(i=0;i<8;i++) //N_M_HH~N_S_LL 8个
	{
	FMC_ReadPage((ID_ADDR+(i<<2)),4,ID_Data); //mcu 1258 （8）
	*(p+i) = ID_Data[0];
	}
  
	EquInfo->HW_VER = 0x01; //硬件版本号
	EquInfo->S_BODY = 0x01; //50k 全身算法普通版本
	
	//加载aprom主板本、副版本、boot版本、校验区511
	FMC_ReadPage(APROM_ADDR,4,ID_Data); //加载aprom主板本、副版本 1 2 
	EquInfo->APROM_H=ID_Data[0];
	EquInfo->APROM_L=ID_Data[1];
	
	FMC_ReadPage(BOOT_ADDR,4,ID_Data); //boot	1 ?????????????????????
	EquInfo->BOOT_VER=ID_Data[0];
	
	FMC_ReadPage(CHECK_ADDR,4,ID_Data); //校验区511 4
	EquInfo->CHECK_SUM=ID_Data[3];	
	
  //加载算法版本信息
	///
}
