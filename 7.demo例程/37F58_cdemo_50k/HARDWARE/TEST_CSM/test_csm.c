#include "test_csm.h"

uint8_t ver_info[12]={0};   //�汾
uint8_t mesure_info[2]={0}; //Ƶ�ʲ�λ
uint8_t res_val[12]={0};    //RES
uint8_t aly_dat[32];        //�ɷֽ��
uint8_t hum_dat[5]={0x02,0xC1,0xAA,0x9E,0x00}; //����70.5kg ���170cm ����30 �Ա��� 1 Ĭ��ģʽ 0x00
/*
temp=0x35
IIC_WriteDate(0xA0,0x3F5A,&temp,1);//����˯������

temp=0x53
IIC_WriteDate(0xA0,0x3F5A,&temp,1);//���ͻ�������
*/

/* ģ�����������ֵʾ��ͼ
   (1)    (2)
   300    300
       28
   240    240 
   (3)    (4)
Z12 = 600 
Z14 = 568
Z13 = 568
Z23 = 568
Z24 = 568
Z34 = 480 
*/
//Z12 Z14 Z13 Z23 Z24 Z34



uint8_t redy_flg=0;
uint8_t tim_flg=0;
uint8_t flash_redy=0;
uint8_t sta_flg=0;   

void DRDY_Init(void)
{
	//DRDY1
	GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(DRDY1_CLOCK,ENABLE);	//��ʹ������IO PORTCʱ��   
//	GPIO_InitStructure.GPIO_Pin = DRDY1_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;   //��������
//	GPIO_Init(IIC_GPIOX,&GPIO_InitStructure);
	
	//RESET1 ���������
	RCC_APB2PeriphClockCmd(RESET1_CLOCK,ENABLE);	//��ʹ������IO PORTCʱ��   
	GPIO_InitStructure.GPIO_Pin = RESET1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_Init(RESET1_GPIOX,&GPIO_InitStructure);	
	
	GPIO_SetBits(RESET1_GPIOX,RESET1_PIN);		
	
	//CE1  ��������ʹ��CSM37F58��Դ����,һֱʹ�ܵ�Դ
	RCC_APB2PeriphClockCmd(CE1_CLOCK,ENABLE);	//��ʹ������IO PORTCʱ��   
	GPIO_InitStructure.GPIO_Pin = CE1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_Init(CE1_GPIOX,&GPIO_InitStructure);	
	
	GPIO_SetBits(CE1_GPIOX,CE1_PIN);
}

/*
ִ������ 1.tim_flg==1  ��ʱ��ѯʱ�䵽
         2.sta_flg==0  CSM37F58���ڿ���״̬
�����־ 1.redy_flg  1 ���� 0 δ����
*/

void check_pre(void)
{			
	    uint8_t temp_read=0; 
		/***���ģ���Ƿ����***/
		if(tim_flg &&(sta_flg==0)) //��ʱ���
		{
			tim_flg=0;redy_flg=0;
			
		   /*��ȡ�汾��Ϣ*/  
			if(IIC_ReadDate(0xA0,0x1048,&ver_info[0],12)==TRUE && IIC_ReadDate(0xA0,0x1001,&mesure_info[0],2)==TRUE)
				{ //8 9 10 11
					//sprintf(s,"%02x-%02x-%02x---%02x-%02x",ver_info[4],ver_info[11],ver_info[7],mesure_info[0],mesure_info[1]);  //Ӳ���汾  511�ֽ�  �㷨�汾 Ƶ�� ��λ
					//LCD_write_string(0,2,s); //��,��,����	  
				}
			else
				{  
					//��ӡ��Ƶ����Ϣ����λ��Ϣʧ��
					LCD_write_string(0,1," -------------- ");
          LCD_write_string(0,2,"----------------");	
					LCD_write_string(0,3,"ͨѶʧ��--------");
					flash_redy=0;sta_flg=0;					
          M1_ERR();//���									
					return;
				}
		
			  IIC_ReadDate(0xA0,0x1013,&temp_read,1); //Z_STATUS
				if((temp_read>>7)&&(temp_read!=0xFF))
				{
						//ģ�����						
						redy_flg=1;	
            if(flash_redy==0) 
						{
							LCD_write_string(0,3,"ģ�����--------");
						}							
				}
				else
				{ 
						//ģ�����ڳ�ʼ��					
						redy_flg=0;flash_redy=0;sta_flg=0;
					  LCD_write_string(0,3,"��ʼ����---------");					
				}				
		}	
}


/*
ִ������ 1.redy_flg==1 ���� 
         2.sta_flg==0  CSM37F58���ڿ���״̬
         3.��������(���滻�����ȳɹ�)
�����־ 
*/
void measure(void)
{
	   uint8_t cmd=0x80;
	   uint8_t key_flag=0;
		if(redy_flg &&(sta_flg==0))
		{
				key_flag=Key_Scan(0);//��鰴��		
				if(key_flag==KEY0_PRES)	
				{  
					//д���������
					IIC_WriteDate(0xA0,0x1058,hum_dat,5);
					
					flash_redy=0;sta_flg=0;M1_NONE();					
					LCD_write_string(0,1," -------------- ");
					LCD_write_string(0,2,"----------------");
					LCD_write_string(0,3,"----------------");
					
          if(IIC_WriteDate(0xA0,0x1000,&cmd,1)==TRUE) //���Ͳ������� STATUS
					{
						sta_flg=1;   
					}	
					else
					{
						  flash_redy=1;sta_flg=0;
					    LCD_write_string(0,3,"���Ͳ�������----");	
						  M1_ERR();
      		}
				}
    }
}

//��ʾ�Ѿ�������λ
void dis_part(void)
{
	 uint8_t temp;
     if(sta_flg==2) //���ڲ�����
		{
			 IIC_ReadDate(0xA0,0x1013,&temp,1);//Z_STATUS
			 if((temp>>5)&0x01) LCD_write_string(0,1," LH-");//����1
			 else LCD_write_string(0,1," ---");
			
			 if((temp>>4)&0x01) LCD_write_string(13,1,"LL "); //���
			 else LCD_write_string(13,1,"-- ");
			
			 if((temp>>3)&0x01) LCD_write_string(10,1,"RL-");//�ҽ�
			 else LCD_write_string(10,1,"---");
				
			 if((temp>>2)&0x01) LCD_write_string(4,1,"RH-");//����1
			 else LCD_write_string(4,1,"---");
				
			 if((temp>>1)&0x01) LCD_write_string(7,1,"TR-");//����
			 else LCD_write_string(7,1,"---");
				
			 if((temp>>0)&0x01) 
			 {
				 LCD_write_string(0+1,1," ------------- ");
				 LcdUpdate();
				 delay_ms(1000);
				 LCD_write_string(0+1,1," LH-RH-TR-RH-LL ");//ȫ��
				 LcdUpdate();
			 } 			 		
		}
}
/* (1)    (2)
   300    300
       28
   240    240 
   (3)    (4)
*/
//��ò������
void get_result(void)
{			
	uint8_t err_flag=0;		
	uint8_t aly_cmd=0x04;		
	uint8_t s[30];
		if(sta_flg==3)  //�������
		{
			//��ʾ�������
			IIC_ReadDate(0xA0,0x1014,&err_flag,1);
			if(err_flag==0)
			{			
				IIC_WriteDate(0xA0,0x3F5A,&aly_cmd,1);//���ͼ���ɷ�����
				delay_ms(10);				
				if(IIC_ReadDate(0xA0,0x1158,&aly_dat[0],32)==FALSE)//���ɷֽ��
				{
					LCD_write_string(0,3,"ͨѶʧ��--------");
			  	flash_redy=1;sta_flg=0;	
          M1_ERR();//���					
					return ;
				}
				IIC_ReadDate(0xA0,(0x10D8),&res_val[0],12);
				
//				//��ʾ�ɷ�  ��֬�ٷֱ�  ������
				sprintf(s,"BFP:%.1f PP:%.1f",(((aly_dat[0x18]<<8)+aly_dat[0x19])*0.1),
																					(((aly_dat[0x12]<<8)+aly_dat[0x13])*0.1));


				LCD_write_string(0,2,s); //��,��,����	  
				
				sprintf(s,"OK!%d-%d-%d",((res_val[2]<<8)|res_val[3]),
																((res_val[6]<<8)|res_val[7]),
																((res_val[10]<<8)|res_val[11]));	 //���� ��� ����
				
				LCD_write_string(0,3,s);//��,��,����	
				flash_redy=1;	sta_flg=0;		
				M1_OK();
			}
			else
			{
				//������	
        //���������ʾ	
				flash_redy=1;	sta_flg=0;
				M1_ERR();
				if((err_flag>>7)&0x01) {LCD_write_string(0,3,"�ڶ̴���--------");return;}
				if((err_flag>>6)&0x01) {LCD_write_string(0,3,"���޴���--------");return;}
				if((err_flag>>5)&0x01) {LCD_write_string(0,3,"���޴���--------");return;}
				if((err_flag>>4)&0x01) {LCD_write_string(0,3,"վ�˴���--------");return;}
			}				
		}		
}

