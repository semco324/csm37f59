2017.11.20 v1.0
2017.12.9  v2.0 �޲�ʱ������ 
2017.12.20 v3.0 �޸��㷨��������,������ͨ���˶�ģʽ 
2018.1.24  v3.1 �޸�M_PART�����û���������csa37fx60_it.c   case (uint32_t)&EquMent->M_PART:
2018.1.24  v3.2 �޸���������37 5A XX 05��� ,��user_addrָ����Ч��ַ
2018.1.24  v3.3 �޸��㷨CS_BIA_V4_3_1-->��Ӧ�㷨�汾V01 EquInfo->S_BODY = 0x01; 
2018.1.26  v3.31����Ӳ���汾��0x01 ---> EquInfo->HW_VER = 0x01; //Ӳ���汾��  
2018.1.27  v3.4 ���ӵ���Ӵ��ڴ���(����֤)
		        mov_res(BODY_1); //����� -->
			    //replace-----------------�Ӵ�����
			    DealWithResPre(BODY_1);//����û���Ϣ��������裬�ж��Ƿ�Ҫ������
			    DealWithRes(BODY_1,F1);//��ô���֮�����  
			    mov_res(BODY_1);       //�����(�ڲ��������mov_res(BODY_1);��һ��)
			    //replace-----------------
	           ע�� UserInfo_TypeDef ����ʹ��32λ���洢���������8λ�洢��һ��
		       �޸� #define  READ_LAST  Log_END  // ---> #define  READ_LAST  RESVal_END  ���Զ�����ʵ����
2018.2.27  v3.5 ����kֵλ����У׼kֵ��int8_t--->uint16_t  ���Ϊ��1��ʾ���������λ0��ʾ����
2018.2.28  v3.6 �޸�1258bug������1258��powerdown���Ѻ�����ڶ�ֵ�쳣���л�������ͨ�������е��ڶ̶�����
				���Ӵ���sleep.c
				Ref_Init_All(SHORT_MODE,F1);  //�ڶ�
				SendDataToAddr(ADDR_AFE_SYS,0xCE);
				Res_Init_All(ISIN2,ISIN3,VSEN3,VSEN2,F1);	//Z34
				SendDataToAddr(ADDR_AFE_SYS,0xCE);
				ע�ʹ���main.c
				//if(n==1 && m==1)PowerDownCS125x();
2018.2.28  v3.61 �޸�AD���ȴ��� 8,12�θĳ�20��
										 #define	FILTER_AD_TIMES		  4		  //����AD����
										 #define RES_AD_TIMES			   12//8		  //�ο�����ɼ�����
										 #define	BODY_AD_TIMES			  20//12		  //�������ɼ�����
				���ȷ�Χ��500�ĳ�768     if(tempADC<=768)  //if(tempADC<=500)
2018.2.28  v3.62				
				�㷨�����������αȲ���
				�㷨��߲�����Χ��ֵ����
				#define HT_MAX   220  //cm
                #define HT_MIN   90  //cm
2018.3.1   v3.63 �޸�4�ֽڶ������ط��� __align(4) ����
2018.3.5   v3.64 ���� void _CS1258bug(void) ��У׼�����������Ѻ���� \
2018.3.9   v3.65 ���޷�����time_out�Ĵ��� ReadAvgADC() ���޸�
2018.4.12  v3.66 ��������ɷ��㷨CS_BIA_V4_3_2
2018.4.17  v3.67 ����uint32_t a[64+24+128+128+128+128+24+128] __at(0x20001000);
2018.4.18  v3.68 ���ɵ�����㷽ʽ�ĳ�Z5 = (Z14+Z23)/50; ����ɷ���Ȼ�üӴ���֮��ĵ���
2018.4.25  v3.69 //վ���쳣�ж�  BOOL judge_posture(uint16_t pos,uint16_t neg) ���ֲ���ģʽ��У׼ģʽ,�޸�����

			////////////����ģʽ��///////////////					
			if(((EquMent->STATUS>>ON_OFF)&0x01)) //����
			{							
				EquMent->STATUS&=~(1<<ON_OFF); //���clr
				SetDRDY(0);								
			}				
			////////////У׼ģʽ��///////////////
		    else if(((EquMent->CONFIG_K>>CK)&0x01)) //У׼
			{
				EquMent->CONFIG_K&=~(1<<CK);//���clr	
				SetDRDY(0);							
			}		
2018.4.25 v3.70 ����������RES_MIN 300~1500�ĳ�RES_MIN 200~1500
               void DealWithRes(FunctionTestSta FP , FunctionFreq Fx) switch �м���break;
2018.4.25 v3.71
				�����¸İ�1258 
					ADDR_AFE_CONFIG(0x10)��ԭ��0xBF��д��0xBD  ------> void	Reset_CS125x(void)
					ADDR_AFE_ADC3(0x04)��ԭ��0x00��д��0x03  ------> void InitCS125x(void)
					
2018.4.25 v3.71B
				��v371�Ļ������������ʹ���
				�����㷨�汾CS_HRI_V112 (��-7)

2018.4.25 v3.72B	
				�����㷨��CS_BIAS_V4.3.3
				�޸��㷨���������Χ 
				#define WEIGHT_MAX   1800--->1500 //kg*10
				#define WEIGHT_MIN   300 --->200  //kg*10
				����Z12 ������Сֵ��200�ĵ�250
				#define	RES_MIN12    2500		

2018.7.11 v3.73B
				8�缫ģʽ�µ�һƵ�ε�ֻ��˫�ŽӴ�ʱ��Ҳ�����˫�ŵ��赽BIA��
				DealWithResPre(LEG_1);//����û���Ϣ��������裬�ж��Ƿ�Ҫ������
				DealWithRes(LEG_1,F1);//��ô���֮�����  
				mov_res(LEG_1);       //�����				GetBodyF1();

                ���α� * 100
==========================CSM37F59===================================				
2018.7.31  v1.00B

	CSM37F59
	#define  FAT_CS    GPIO_PA2---> GPIO_PA4 CS���ƽ���PA2������PA4
	
2018.9.04
		���ȷ�Χ700��1400
					