#include "boot.h"

/* APROM
数据区[0xEE00~0xEFFF]    
校验区[0xEC00~0xEE00)    1*512=0.5KB
程序区[0x0000~0xEC00)   118*512=59KB
*/
//获得APROM版本号

 uint8_t APROM_Major,APROM_Minor; //APROM 主版本 副版本

 __align(4) uint8_t Code_IIC_Buf0[512];//APROM程序缓存
 __align(4) uint8_t Code_IIC_Buf1[512];//APROM检查缓存
 
 
// uint8_t ReCode_IIC_Buf0[512];//APROM程序缓存_Re


 uint16_t IIC_ReCount=0; //iic接受计数
 uint16_t IIC_HostRWAddr=0;//boot 读写地址

 uint8_t  IIC_ReDataFinsh;   //IIC 数据接收完成标记
 uint8_t  IIC_WriteflashCmd; //IIC写flash命令
 uint8_t  IIC_Buf[16];       //iic地址缓存

 uint8_t  Flag_APROMCheckOK;
 uint8_t  Flag_Erase=0;


void load_boot_ver(void)
{	 
		FMC_ReadPage(FMC_ADDR,512,first_buf); //先读出来保存其他数据		
		first_buf[(N_BOOT<<2)]=LDROM_MAJOR;   //更新boot
	
		FMC_ErasePage(FMC_ADDR);             //擦除	512	   
		FMC_WritePage(FMC_ADDR,512,first_buf); //写数据  
}

			
			
void GetAPROM_ID(void)
{
	 uint16_t i;

	 
	 FMC_ReadPage(CHECK_ADDR, 4, temp); //读APROM 主版本 副版本 主板本xor 副版本xor
	 
	 APROM_Major = 0xff;
   APROM_Minor = 0xff; //默认是0xff
	
	 Flag_APROMCheckOK = 0;
	
	 temp[2] ^=0xff;
   temp[3] ^=0xff;   //这是有校验区下	
	
	if((temp[0]==(temp[2])) && (temp[1]==(temp[3]))) //校验通过，aprom版本号校验正确
	{
			APROM_Major = temp[0];
			APROM_Minor = temp[1];  

			Flag_APROMCheckOK = 1;		
			Timer_Enable(Timer_0); //使能100ms 计时
		  return;
	}  
	//
	FMC_ReadPage(0x0000, 512, first_buf); //读512
	
	if(temp[0]==0xff && temp[1]==0xff) //校验是ff
	{
		 for(i=0;i<512;i++)
		  {
			   if(first_buf[i]==0xff) 
				  {
					 if(i==511)
					 {
						 Flag_APROMCheckOK = 0;		
						 Timer_Disable(Timer_0); //失能100ms 计时
						 return;
					 }
					}
					else
					{
						Flag_APROMCheckOK = 1;		
						Timer_Enable(Timer_0); //使能100ms 计时
						return;  
					}
			}  			
	}	
}

//iic 根据主控发送的地址和数据对flash进行擦写
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
    if(IIC_HostRWAddr<CHECK_ADDR) //升级应用程序区
    {
//			 if(IIC_HostRWAddr==0xEC00)
//			 {
//  			IIC_HostWriteData(Code_IIC_Buf0, 512,IIC_HostRWAddr);   
//			 }	
//      else	
//			 {
//				re_bin(Code_IIC_Buf0,ReCode_IIC_Buf0,512);//调整		 
//       	IIC_HostWriteData(ReCode_IIC_Buf0, (IIC_ReCount-2),IIC_HostRWAddr); 
					IIC_HostWriteData(Code_IIC_Buf0, (IIC_ReCount-2),IIC_HostRWAddr);			
//			 }				 
    }
		else if(IIC_HostRWAddr == CHECK_ADDR)
		{   
			   
        
			  //校验接受到的校验区数据
			  sum=0;
			  for(j=0;j<511;j++) {sum+=Code_IIC_Buf0[j];} //校验区累加和(除开最后1个)
			
			  if(sum==Code_IIC_Buf0[511]) //先比较校验区自己的校验值
				{
					   //比较计算每一段校验和
				    for(i=0;i<Code_IIC_Buf0[4];i++)  //Code_IIC_Buf0[4] APROM代码段个数
					     {  
							       FMC_ReadPage((0x0000 + 0x0200*i), 512, Code_IIC_Buf1);
								     sum=0;
								     for(j=0;j<512;j++) {sum += Code_IIC_Buf1[j];}
										 if(sum!=Code_IIC_Buf0[5+i])
										 {
										     code_Error = 1;
											 //写ff 
//											 	 SetDRDY(0);
											   FMC_EraseMorePage(0x00000000, 119); //从0x0000_0000 开始，119个block 
											   break;
										 }						 
							 }
						if(code_Error==0) 
						   {    //code_Error==0,保存校验区
						        IIC_HostWriteData(Code_IIC_Buf0, (IIC_ReCount-2),CHECK_ADDR); 
							      GetAPROM_ID();
						   }
				}	
				else
				{
					code_Error = 1;
					//写ff 
//				SetDRDY(0);
  				FMC_EraseMorePage(0x00000000, 119); //从0x0000_0000 开始，119个block 			
				}
		}	
}

extern uint8_t ok;
void IIC_CmdProc(void)
{
	 uint8_t flag = 0;// iic数据是否特殊命令标志，0为非特殊命令 1为特殊命令 

    if(IIC_ReDataFinsh && IIC_WriteflashCmd) //接收数据完成 & host 写命令
 		{
          //主控有写数据则关闭100ms定时
          Flag_WaitTime = 0;
          Timer_Disable(Timer_0);//定时时间到关闭定时器0
			    //------------------------------------------------------------
          if(IIC_HostRWAddr == 0x0000) //操作地址是0x0000
					{
						  if((IIC_ReCount-2)==4) //检测命令长度是4
							{
							  if( (Code_IIC_Buf0[0]==0xAA) && (Code_IIC_Buf0[1]==0x55) 
                    && (Code_IIC_Buf0[2]==0xA5) && (Code_IIC_Buf0[3]==0x5A)) //擦除flash指令
										{
											    //从0x0000_0000 开始，119个block
												if(FMC_EraseMorePage(0x00000000, 119) == 0)//success
												SetDRDY(1);
												flag = 1; Flag_Erase=1;ok=1;
										}                
                if( (Code_IIC_Buf0[0]==0x7E) && (Code_IIC_Buf0[1]==0xE7) 
                    && (Code_IIC_Buf0[2]==0xEE) && (Code_IIC_Buf0[3]==0x77) && Flag_APROMCheckOK) //跳转aprom 指令
										{
											  SetDRDY(0);flag = 1;ok=0;
												FMC_SwitchROM(FMC_APROM); // 切换APROM													
										}
							}
					}
					if(flag==0 && Flag_Erase==1)
					{
					    APROM_UpdateProc();//iic数据擦写相应flash
					}
					IIC_ReDataFinsh = 0;
          IIC_WriteflashCmd = 0;			
		}	
}





