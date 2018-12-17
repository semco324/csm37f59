#include "boot.h"

/* APROM
������[0xEE00~0xEFFF]    
У����[0xEC00~0xEE00)    1*512=0.5KB
������[0x0000~0xEC00)   118*512=59KB
*/
//���APROM�汾��

 uint8_t APROM_Major,APROM_Minor; //APROM ���汾 ���汾

 __align(4) uint8_t Code_IIC_Buf0[512];//APROM���򻺴�
 __align(4) uint8_t Code_IIC_Buf1[512];//APROM��黺��
 
 
// uint8_t ReCode_IIC_Buf0[512];//APROM���򻺴�_Re


 uint16_t IIC_ReCount=0; //iic���ܼ���
 uint16_t IIC_HostRWAddr=0;//boot ��д��ַ

 uint8_t  IIC_ReDataFinsh;   //IIC ���ݽ�����ɱ��
 uint8_t  IIC_WriteflashCmd; //IICдflash����
 uint8_t  IIC_Buf[16];       //iic��ַ����

 uint8_t  Flag_APROMCheckOK;
 uint8_t  Flag_Erase=0;


void load_boot_ver(void)
{	 
		FMC_ReadPage(FMC_ADDR,512,first_buf); //�ȶ�����������������		
		first_buf[(N_BOOT<<2)]=LDROM_MAJOR;   //����boot
	
		FMC_ErasePage(FMC_ADDR);             //����	512	   
		FMC_WritePage(FMC_ADDR,512,first_buf); //д����  
}

			
			
void GetAPROM_ID(void)
{
	 uint16_t i;

	 
	 FMC_ReadPage(CHECK_ADDR, 4, temp); //��APROM ���汾 ���汾 ���屾xor ���汾xor
	 
	 APROM_Major = 0xff;
   APROM_Minor = 0xff; //Ĭ����0xff
	
	 Flag_APROMCheckOK = 0;
	
	 temp[2] ^=0xff;
   temp[3] ^=0xff;   //������У������	
	
	if((temp[0]==(temp[2])) && (temp[1]==(temp[3]))) //У��ͨ����aprom�汾��У����ȷ
	{
			APROM_Major = temp[0];
			APROM_Minor = temp[1];  

			Flag_APROMCheckOK = 1;		
			Timer_Enable(Timer_0); //ʹ��100ms ��ʱ
		  return;
	}  
	//
	FMC_ReadPage(0x0000, 512, first_buf); //��512
	
	if(temp[0]==0xff && temp[1]==0xff) //У����ff
	{
		 for(i=0;i<512;i++)
		  {
			   if(first_buf[i]==0xff) 
				  {
					 if(i==511)
					 {
						 Flag_APROMCheckOK = 0;		
						 Timer_Disable(Timer_0); //ʧ��100ms ��ʱ
						 return;
					 }
					}
					else
					{
						Flag_APROMCheckOK = 1;		
						Timer_Enable(Timer_0); //ʹ��100ms ��ʱ
						return;  
					}
			}  			
	}	
}

//iic �������ط��͵ĵ�ַ�����ݶ�flash���в�д
void IIC_HostWriteData(uint8_t *buf, uint16_t size,uint16_t addr)
{
    uint32_t addr_base = 0x00000000;    
    addr_base += addr;   
    if(size>512)size = 512;
 
    FMC_ErasePage(addr_base);
    FMC_WritePage(addr_base, size, buf) ;     
}

//void re_bin(uint8_t *buf,uint8_t *rebuf,uint16_t n)
//{
//	uint16_t i;
//	uint8_t t;
//  for(i=0;i<512;i+=4)
//	{	
//		  t=buf[i+3];  
//		  rebuf[i+3]=buf[i];
//		  rebuf[i]=t;

//		  t=buf[i+2];  
//		  rebuf[i+2]=buf[i+1];
//		  rebuf[i+1]=t;	
////	  rebuf[i]=buf[i+1]<<8 | buf[i+1]>>8; //16bit
////		rebuf[i+1]=buf[i]<<8 | buf[i]>>8;
//	}
//}

void APROM_UpdateProc(void)
{   
		uint8_t i;
    uint16_t j;
    uint8_t sum;
    uint8_t code_Error = 0;
    //******************************************
    if(IIC_HostRWAddr<CHECK_ADDR) //����Ӧ�ó�����
    {
//			 if(IIC_HostRWAddr==0xEC00)
//			 {
//  			IIC_HostWriteData(Code_IIC_Buf0, 512,IIC_HostRWAddr);   
//			 }	
//      else	
//			 {
//				re_bin(Code_IIC_Buf0,ReCode_IIC_Buf0,512);//����		 
//       	IIC_HostWriteData(ReCode_IIC_Buf0, (IIC_ReCount-2),IIC_HostRWAddr); 
					IIC_HostWriteData(Code_IIC_Buf0, (IIC_ReCount-2),IIC_HostRWAddr);			
//			 }				 
    }
		else if(IIC_HostRWAddr == CHECK_ADDR)
		{   
			   
        
			  //У����ܵ���У��������
			  sum=0;
			  for(j=0;j<511;j++) {sum+=Code_IIC_Buf0[j];} //У�����ۼӺ�(�������1��)
			
			  if(sum==Code_IIC_Buf0[511]) //�ȱȽ�У�����Լ���У��ֵ
				{
					   //�Ƚϼ���ÿһ��У���
				    for(i=0;i<Code_IIC_Buf0[4];i++)  //Code_IIC_Buf0[4] APROM����θ���
					     {  
							       FMC_ReadPage((0x0000 + 0x0200*i), 512, Code_IIC_Buf1);
								     sum=0;
								     for(j=0;j<512;j++) {sum += Code_IIC_Buf1[j];}
										 if(sum!=Code_IIC_Buf0[5+i])
										 {
										     code_Error = 1;
											 //дff 
//											 	 SetDRDY(0);
											   FMC_EraseMorePage(0x00000000, 119); //��0x0000_0000 ��ʼ��119��block 
											   break;
										 }						 
							 }
						if(code_Error==0) 
						   {    //code_Error==0,����У����
						        IIC_HostWriteData(Code_IIC_Buf0, (IIC_ReCount-2),CHECK_ADDR); 
							      GetAPROM_ID();
						   }
				}	
				else
				{
					code_Error = 1;
					//дff 
//				SetDRDY(0);
  				FMC_EraseMorePage(0x00000000, 119); //��0x0000_0000 ��ʼ��119��block 			
				}
		}	
}

extern uint8_t ok;
void IIC_CmdProc(void)
{
	 uint8_t flag = 0;// iic�����Ƿ����������־��0Ϊ���������� 1Ϊ�������� 

    if(IIC_ReDataFinsh && IIC_WriteflashCmd) //����������� & host д����
 		{
          //������д������ر�100ms��ʱ
          Flag_WaitTime = 0;
          Timer_Disable(Timer_0);//��ʱʱ�䵽�رն�ʱ��0
			    //------------------------------------------------------------
          if(IIC_HostRWAddr == 0x0000) //������ַ��0x0000
					{
						  if((IIC_ReCount-2)==4) //����������4
							{
							  if( (Code_IIC_Buf0[0]==0xAA) && (Code_IIC_Buf0[1]==0x55) 
                    && (Code_IIC_Buf0[2]==0xA5) && (Code_IIC_Buf0[3]==0x5A)) //����flashָ��
										{
											    //��0x0000_0000 ��ʼ��119��block
												if(FMC_EraseMorePage(0x00000000, 119) == 0)//success
												SetDRDY(1);
												flag = 1; Flag_Erase=1;ok=1;
										}                
                if( (Code_IIC_Buf0[0]==0x7E) && (Code_IIC_Buf0[1]==0xE7) 
                    && (Code_IIC_Buf0[2]==0xEE) && (Code_IIC_Buf0[3]==0x77) && Flag_APROMCheckOK) //��תaprom ָ��
										{
											  SetDRDY(0);flag = 1;ok=0;
												FMC_SwitchROM(FMC_APROM); // �л�APROM													
										}
							}
					}
					if(flag==0 && Flag_Erase==1)
					{
					    APROM_UpdateProc();//iic���ݲ�д��Ӧflash
					}
					IIC_ReDataFinsh = 0;
          IIC_WriteflashCmd = 0;			
		}	
}





