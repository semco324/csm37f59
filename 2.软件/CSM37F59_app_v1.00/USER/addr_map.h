#ifndef __ADDR_MAP_H
#define __ADDR_MAP_H

#include <stdint.h>                   /* Include standard types */
#include "CS1258.h"
//�豸������rw    23(64)  0x1000
typedef struct
{
	uint32_t STATUS;       //
	uint32_t FREQ;
	uint32_t M_PART;
	
	uint32_t FREQ1_CalRes_H;
	uint32_t FREQ1_CalRes_L;	 
	
	uint32_t FREQ2_CalRes_H;
	uint32_t FREQ2_CalRes_L;	
	
	uint32_t FREQ3_CalRes_H;
	uint32_t FREQ3_CalRes_L;	
	
	uint32_t CONFIG_K;
	uint32_t F1CV_FLAG;	
	uint32_t F2CV_FLAG;
	uint32_t F3CV_FLAG;	
	
	uint32_t FREQ1K_VAL_H;//r
	uint32_t FREQ1K_VAL_L;
	uint32_t FREQ2K_VAL_H;//r	
	uint32_t FREQ2K_VAL_L;
	uint32_t FREQ3K_VAL_H;//r
	uint32_t FREQ3K_VAL_L;
	
	uint32_t Z_STATUS;  //r		
	uint32_t ERR_STATUS;//r		
	uint32_t C_STATUS;  //r		
	uint32_t F_STATUS;  //r		
	
	uint32_t RESERVED1[40];  //RESERVED1
	uint32_t RESERVED[1];
}EquipmentConfig_TypeDef;



//�豸��Ϣ�� r  20(24)  0x1040
typedef struct
{
	/*  14(24)
	uint32_t MID_HH;
	uint32_t MID_H;
	uint32_t MID_L;
	uint32_t MID_LL;
	uint32_t SID_HH;
	uint32_t SID_H;
	uint32_t SID_L;
	uint32_t SID_LL;
	
	uint32_t HMV;
	uint32_t FSV;
	
	uint32_t APROM_H;
	uint32_t APROM_L;
	uint32_t BOOT_VER;
	uint32_t CHECK_SUM;

	uint32_t RESERVED1[9];  //RESERVED1
	uint32_t RESERVED[1];
	*/
	uint32_t MID_HH;
	uint32_t MID_H;
	uint32_t MID_L;
	uint32_t MID_LL;
	uint32_t SID_HH;
	uint32_t SID_H;
	uint32_t SID_L;
	uint32_t SID_LL;
	
	uint32_t S_HAND;      // ��Ƶ�ֲ��㷨 1048
	uint32_t SA_HAND;     // ��Ƶ�ֲ��˶�Ա�㷨
	uint32_t S_LEG;       // ��Ƶ�Ų��㷨
	uint32_t SA_LEG;      // ��Ƶ�Ų��˶�Ա�㷨
	uint32_t S_BODY;      // ��Ƶȫ���㷨
	uint32_t SA_BODY;     // ��Ƶȫ���˶�Ա�㷨
	uint32_t M_HEART;     // �����㷨
	uint32_t HW_VER;      // Ӳ���汾��
	
	uint32_t APROM_H;     
	uint32_t APROM_L;
	uint32_t BOOT_VER;
	uint32_t CHECK_SUM;    

	uint32_t RESERVED1[3];  //RESERVED1
	uint32_t RESERVED[1];
	
}EquipmentInfo_TypeDef;

//�û���Ϣ��rw      77-18(128)  0x1058
typedef struct
{
	uint32_t WTH;
	uint32_t WTL;
	uint32_t HT;
	uint32_t SAGE;
	uint32_t MODE;
  //�Ӵ�����
	uint32_t F1_All_Res_H; 
	uint32_t F1_All_Res_L;
	uint32_t F1_Z1_Res_H;
	uint32_t F1_Z1_Res_L;
	uint32_t F1_Z2_Res_H;
	uint32_t F1_Z2_Res_L;	
	uint32_t F1_Z3_Res_H;
	uint32_t F1_Z3_Res_L;
	uint32_t F1_Z4_Res_H;
	uint32_t F1_Z4_Res_L;
	uint32_t F1_Z5_Res_H;
	uint32_t F1_Z5_Res_L;
	
	uint32_t F2_All_Res_H;
	uint32_t F2_All_Res_L;
	uint32_t F2_Z1_Res_H;
	uint32_t F2_Z1_Res_L;
	uint32_t F2_Z2_Res_H;
	uint32_t F2_Z2_Res_L;	
	uint32_t F2_Z3_Res_H;
	uint32_t F2_Z3_Res_L;
	uint32_t F2_Z4_Res_H;
	uint32_t F2_Z4_Res_L;
	uint32_t F2_Z5_Res_H;
	uint32_t F2_Z5_Res_L;
	
	uint32_t F3_All_Res_H;
	uint32_t F3_All_Res_L;
	uint32_t F3_Z1_Res_H;
	uint32_t F3_Z1_Res_L;
	uint32_t F3_Z2_Res_H;
	uint32_t F3_Z2_Res_L;	
	uint32_t F3_Z3_Res_H;
	uint32_t F3_Z3_Res_L;
	uint32_t F3_Z4_Res_H;
	uint32_t F3_Z4_Res_L;
	uint32_t F3_Z5_Res_H;
	uint32_t F3_Z5_Res_L;


  //�ⲿ���û����ɼ� ע����������32λ�洢
	uint32_t F1_Z34_Res;
//	uint32_t ;
	uint32_t F1_Z12_Res;
//	uint32_t ;	
	uint32_t F1_Z13_Res;
//	uint32_t ;
	uint32_t F1_Z14_Res;
//	uint32_t ;
	uint32_t F1_Z23_Res;
//	uint32_t ;
	uint32_t F1_Z24_Res;
//	uint32_t ;
	
	uint32_t F2_Z34_Res;
//	uint32_t ;
	uint32_t F2_Z12_Res;
//	uint32_t ;	
	uint32_t F2_Z13_Res;
//	uint32_t ;
	uint32_t F2_Z14_Res;
//	uint32_t ;
	uint32_t F2_Z23_Res;
//	uint32_t ;
	uint32_t F2_Z24_Res;
//	uint32_t ;

	uint32_t F3_Z34_Res;
//	uint32_t ;
	uint32_t F3_Z12_Res;
//	uint32_t ;	
	uint32_t F3_Z13_Res;
//	uint32_t ;
	uint32_t F3_Z14_Res;
//	uint32_t ;
	uint32_t F3_Z23_Res;
//	uint32_t ;
	uint32_t F3_Z24_Res;
//	uint32_t ;
	//�ⲿ���û����ɼ�
	//�Ӵ�����
	uint32_t RESERVED1[50+18];  //RESERVED1
	uint32_t RESERVED[1];
}UserInfo_TypeDef;


//�û�����BIA�� r   72+2(���2��)(128) 0x10D8
typedef struct
{
	//����ɷּ���ĵ���
	uint32_t Freq1_All_Res_H;  //0
	uint32_t Freq1_All_Res_L;  //1
	uint32_t Freq1_Z1_Res_H;   //2
	uint32_t Freq1_Z1_Res_L;	 //3
	uint32_t Freq1_Z2_Res_H;   //4
	uint32_t Freq1_Z2_Res_L;	 //5
	uint32_t Freq1_Z3_Res_H;   //6
	uint32_t Freq1_Z3_Res_L;	 //7
	uint32_t Freq1_Z4_Res_H;   //8
	uint32_t Freq1_Z4_Res_L;	 //9
	uint32_t Freq1_Z5_Res_H;   //a
	uint32_t Freq1_Z5_Res_L;   //b

	uint32_t Freq2_All_Res_H;  //c
	uint32_t Freq2_All_Res_L;  //d
	uint32_t Freq2_Z1_Res_H;   //e
	uint32_t Freq2_Z1_Res_L;	 //f
	uint32_t Freq2_Z2_Res_H;   //10
	uint32_t Freq2_Z2_Res_L;	 //11
	uint32_t Freq2_Z3_Res_H;   //12
	uint32_t Freq2_Z3_Res_L;	 //13
	uint32_t Freq2_Z4_Res_H;   //14
	uint32_t Freq2_Z4_Res_L;	 //15
	uint32_t Freq2_Z5_Res_H;   //16
	uint32_t Freq2_Z5_Res_L;   //17

	uint32_t Freq3_All_Res_H;  //18
	uint32_t Freq3_All_Res_L;  //19
	uint32_t Freq3_Z1_Res_H;   //1a
	uint32_t Freq3_Z1_Res_L;	 //1b
	uint32_t Freq3_Z2_Res_H;   //1c
	uint32_t Freq3_Z2_Res_L;	 //1d
	uint32_t Freq3_Z3_Res_H;   //1e
	uint32_t Freq3_Z3_Res_L;	 //1f
	uint32_t Freq3_Z4_Res_H;   //20
	uint32_t Freq3_Z4_Res_L;	 //21
	uint32_t Freq3_Z5_Res_H;   //22
	uint32_t Freq3_Z5_Res_L;   //23
	
	//�ⲿ���û����ɼ�
	uint32_t Freq1_Z34_Res_H;  //24
	uint32_t Freq1_Z34_Res_L;	 //25
	uint32_t Freq1_Z12_Res_H;  //26
	uint32_t Freq1_Z12_Res_L;	 //27
	uint32_t Freq1_Z13_Res_H;  //28
	uint32_t Freq1_Z13_Res_L;	 //29
	uint32_t Freq1_Z14_Res_H;  //3a
	uint32_t Freq1_Z14_Res_L;	 //3b
	uint32_t Freq1_Z23_Res_H;  //3c
	uint32_t Freq1_Z23_Res_L;	 //3d
	uint32_t Freq1_Z24_Res_H;  //3e
	uint32_t Freq1_Z24_Res_L;	 //3f
	
	uint32_t Freq2_Z34_Res_H;  //40
	uint32_t Freq2_Z34_Res_L;	
	uint32_t Freq2_Z12_Res_H;
	uint32_t Freq2_Z12_Res_L;	
	uint32_t Freq2_Z13_Res_H;
	uint32_t Freq2_Z13_Res_L;	
	uint32_t Freq2_Z14_Res_H;
	uint32_t Freq2_Z14_Res_L;	
	uint32_t Freq2_Z23_Res_H;
	uint32_t Freq2_Z23_Res_L;	
	uint32_t Freq2_Z24_Res_H;
	uint32_t Freq2_Z24_Res_L;	
	
	uint32_t Freq3_Z34_Res_H;
	uint32_t Freq3_Z34_Res_L;	
	uint32_t Freq3_Z12_Res_H;
	uint32_t Freq3_Z12_Res_L;	
	uint32_t Freq3_Z13_Res_H;
	uint32_t Freq3_Z13_Res_L;	
	uint32_t Freq3_Z14_Res_H;
	uint32_t Freq3_Z14_Res_L;	
	uint32_t Freq3_Z23_Res_H;
	uint32_t Freq3_Z23_Res_L;	
	uint32_t Freq3_Z24_Res_H;
	uint32_t Freq3_Z24_Res_L;	
	//�ⲿ���û����ɼ�	
	uint32_t RESERVED1[53];  //RESERVED1
	uint32_t diff_h;
	uint32_t diff_l;
	uint32_t RESERVED[1];
}UserBIAPart_TypeDef;


//�ɷַ�������� r      (84)128     0x1158
typedef struct
{	
    uint32_t FM_H;          //֬���� 1 				0x00
		uint32_t FM_L;          //         				0x01
		uint32_t SLM_H;         //������ 2 				0x02   2
		uint32_t SLM_L;	        //         				0x03
		uint32_t TF_H;          //��ˮ�� 3 				0x04
		uint32_t TF_L;          //				 				0x05
		uint32_t EXF_H;         //ϸ����Һ 4			0x06
		uint32_t EXF_L;		      //								0x07
		uint32_t INF_H;         //ϸ����Һ 5      0x08
		uint32_t INF_L;		      //                0x09
		uint32_t LBM_H;         //ȥ֬���� 6      0x0a
		uint32_t LBM_L;			    //                0x0b
		uint32_t BM_H;          //��׼���� 7      0x0c
		uint32_t BM_L;          //                0x0d
		uint32_t BMC_H;         //������ 8        0x0e MSW_H 3
		uint32_t BMC_L;	        //                0x0f  
		uint32_t SMM_H;         //�������� 9      0x10      6
		uint32_t SMM_L;	     		//                0x11
		uint32_t PP_H;          //�������� 10     0x12 PM_H 5
		uint32_t PP_L;					//                0x13 PM_L
		uint32_t BMI_H;         //����ָ�� 11     0x14       10
		uint32_t BMI_L;					//                0x15
		uint32_t BMR_H;         //������л 12     0x16     7
		uint32_t BMR_L;					//                0x17
    uint32_t BFP_H;         //��֬�ٷֱ� 13   0x18  BFR_H  1
    uint32_t BFP_L;					//                0x19  BFR_L
		uint32_t BWP_H;         //��ˮ���� 14     0x1a  TFR_H  4
		uint32_t BWP_L; 				//                0x1b  TFR_L
		uint32_t BW_H;          //��׼���� 15     0x1c         12
		uint32_t BW_L;					//                0x1d
		uint32_t VFR_H;         //����֬���ȼ� 16 0x1e       8
		uint32_t VFR_L;					//                0x1f
		uint32_t MA;            //�������� 17     0x20  Body_Age  9
		uint32_t SBC;           //�������� 18     0x21  Score   11
		uint32_t EE_H;          //ˮ�׶� 19       0x22
		uint32_t EE_L;					//                0x23
		uint32_t OD_H;          //���ֶ� 20       0x24
		uint32_t OD_L;					//                0x25
		uint32_t MC_H;          //������� 21     0x26       14
		uint32_t MC_L; 					//                0x27
		uint32_t WC_H;          //���ؿ��� 22     0x28       13
		uint32_t WC_L;					//                0x29
		uint32_t FC_H;          //֬������ 23     0x2a       15
		uint32_t FC_L;					//                0x2b
    uint32_t TW_H;          //Ŀ������ 24     0x2c
    uint32_t TW_L;          //                0x2d
    //--------------------------------------------��������4��8�缫���в���
    //��������8�缫���в���
		uint32_t TFP_H;         //Z5 ��֬�� 25    0x2e  BFR_TR_H   20
		uint32_t TFP_L;  		    //                0x2f
		uint32_t RAFP_H;        //Z2 ��֬�� 26    0x30  BFR_RA_H   16
		uint32_t RAFP_L;		    //                0x31
		uint32_t LAFP_H;        //Z1 ��֬�� 27    0x32  BFR_LA_H   17
		uint32_t LAFP_L;		    //                0x33
		uint32_t RLFP_H;        //Z4 ��֬�� 28    0x34  BFR_RL_H   18
		uint32_t RLFP_L;        //                0x35
		uint32_t LLFP_H;        //Z3 ��֬�� 29    0x36  BFR_LL_H   19
		uint32_t LLFP_L;		    //                0x37
		uint32_t TMM_H;         //Z5 ������ 30    0x38  SLM_TR_H    21
		uint32_t TMM_L;         //                0x39
		uint32_t RAMM_H;        //Z2 ������ 31    0x3a  SLM_RA_H    22
		uint32_t RAMM_L;		    //                0x3b
		uint32_t LAMM_H;        //Z1 ������ 32    0x3c  SLM_LA_H    23
		uint32_t LAMM_L;        //                0x3d
		uint32_t RLMM_H;        //Z4 ������ 33    0x3e  SLM_RL_H    24
		uint32_t RLMM_L;        //                0x3f
		uint32_t LLMM_H;        //Z3 ������ 24    0x40  SLM_LL_L    25
		uint32_t LLMM_L;        //                0x41
		uint32_t JW_H;          //��Χ 35         0x42
		uint32_t JW_L;          //                0x43
		uint32_t WL_H;          //��Χ 36         0x44
		uint32_t WL_L;          //                0x45
		uint32_t HL_H;          //��Χ 37         0x46
		uint32_t HL_L;          //                0x47
		uint32_t XW_H;          //��Χ 38         0x48
		uint32_t XW_L;          //                0x49
		uint32_t WHR_H;         // ���α�  39     0x4a      26
		uint32_t WHR_L;         //                0x4b
		uint32_t RAW_H;         //Z2 ���ϱ�Χ 40  0x4c
		uint32_t RAW_L;         //                0x4d
		uint32_t LAW_H;         //Z1 ���ϱ�Χ 41  0x4e
		uint32_t LAW_L;         //                0x4f
		uint32_t RLW_H;         //Z4 �Ҵ���Χ 42  0x50
		uint32_t RLW_L;         //                0x51
		uint32_t LLW_H;         //Z3 �����Χ 43  0x52
		uint32_t LLW_L;         //                0x53
				
		uint32_t BH;            //����            0x54
	uint32_t RESERVED1[42];  //RESERVED1
	uint32_t RESERVED[1];
}Analysis_TypeDef;


//���Թ������� r     54(128)   0x11D8
typedef struct
{
	uint32_t Freq1_Short_AD_H;  //00
	uint32_t Freq1_Short_AD_L;  //04
	uint32_t Freq1_Ref0_AD_H;   //08
	uint32_t Freq1_Ref0_AD_L;	  //0c
	uint32_t Freq1_Ref1_AD_H;   //10
	uint32_t Freq1_Ref1_AD_L;	  //14	
  uint32_t Freq1_Z12_AD_H;
  uint32_t Freq1_Z12_AD_L;		
  uint32_t Freq1_Z34_AD_H;
  uint32_t Freq1_Z34_AD_L;		
  uint32_t Freq1_Z13_AD_H;
  uint32_t Freq1_Z13_AD_L;			
  uint32_t Freq1_Z23_AD_H;
  uint32_t Freq1_Z23_AD_L;		
  uint32_t Freq1_Z24_AD_H;
  uint32_t Freq1_Z24_AD_L;	
  uint32_t Freq1_Z14_AD_H;
  uint32_t Freq1_Z14_AD_L;	
		
	uint32_t Freq2_Short_AD_H;
	uint32_t Freq2_Short_AD_L;
	uint32_t Freq2_Ref0_AD_H;
	uint32_t Freq2_Ref0_AD_L;	
	uint32_t Freq2_Ref1_AD_H;
	uint32_t Freq2_Ref1_AD_L;	
  uint32_t Freq2_Z12_AD_H;
  uint32_t Freq2_Z12_AD_L;	
  uint32_t Freq2_Z34_AD_H;
  uint32_t Freq2_Z34_AD_L;	
  uint32_t Freq2_Z13_AD_H;
  uint32_t Freq2_Z13_AD_L;		
  uint32_t Freq2_Z23_AD_H;
  uint32_t Freq2_Z23_AD_L;	
  uint32_t Freq2_Z24_AD_H;
  uint32_t Freq2_Z24_AD_L;		
  uint32_t Freq2_Z14_AD_H;
  uint32_t Freq2_Z14_AD_L;	

	uint32_t Freq3_Short_AD_H;
	uint32_t Freq3_Short_AD_L;
	uint32_t Freq3_Ref0_AD_H;
	uint32_t Freq3_Ref0_AD_L;	
	uint32_t Freq3_Ref1_AD_H;
	uint32_t Freq3_Ref1_AD_L;		
  uint32_t Freq3_Z12_AD_H;
  uint32_t Freq3_Z12_AD_L;	
  uint32_t Freq3_Z34_AD_H;
  uint32_t Freq3_Z34_AD_L;		
  uint32_t Freq3_Z13_AD_H;
  uint32_t Freq3_Z13_AD_L;	
  uint32_t Freq3_Z23_AD_H;
  uint32_t Freq3_Z23_AD_L;		
  uint32_t Freq3_Z24_AD_H;
  uint32_t Freq3_Z24_AD_L;		
  uint32_t Freq3_Z14_AD_H;
  uint32_t Freq3_Z14_AD_L;		
	
	uint32_t RESERVED1[73];  //RESERVED1
	uint32_t RESERVED[1];
}ADCVal_TypeDef;

//                   24   0x1258
typedef struct          
{	
	uint32_t RESERVED1[23];  //RESERVED1
  uint32_t RESERVED[1];
}Log_TypeDef;

//��ʵ����            66(128)   0x1270
typedef struct          
{                           //F1���
  uint32_t F1_Z12_RES_H;
  uint32_t F1_Z12_RES_L;	
  uint32_t F1_Z34_RES_H;
  uint32_t F1_Z34_RES_L;	
  uint32_t F1_Z13_RES_H;
  uint32_t F1_Z13_RES_L;
  uint32_t F1_Z23_RES_H;
  uint32_t F1_Z23_RES_L;
  uint32_t F1_Z24_RES_H;
  uint32_t F1_Z24_RES_L;
  uint32_t F1_Z14_RES_H;
  uint32_t F1_Z14_RES_L;	
	uint32_t F1_Z1_RES_H;    //F1�ֿ�
	uint32_t F1_Z1_RES_L;	
	uint32_t F1_Z2_RES_H;
	uint32_t F1_Z2_RES_L;
	uint32_t F1_Z3_RES_H;
	uint32_t F1_Z3_RES_L;
	uint32_t F1_Z4_RES_H;
	uint32_t F1_Z4_RES_L;	
	uint32_t F1_Z5_RES_H;
	uint32_t F1_Z5_RES_L;		
	
  uint32_t F2_Z12_RES_H;
  uint32_t F2_Z12_RES_L;
  uint32_t F2_Z34_RES_H;
  uint32_t F2_Z34_RES_L;
  uint32_t F2_Z13_RES_H;
  uint32_t F2_Z13_RES_L;	
  uint32_t F2_Z23_RES_H;
  uint32_t F2_Z23_RES_L;	
  uint32_t F2_Z24_RES_H;
  uint32_t F2_Z24_RES_L;
  uint32_t F2_Z14_RES_H;
  uint32_t F2_Z14_RES_L;
	uint32_t F2_Z1_RES_H;
	uint32_t F2_Z1_RES_L;	
	uint32_t F2_Z2_RES_H;
	uint32_t F2_Z2_RES_L;
	uint32_t F2_Z3_RES_H;
	uint32_t F2_Z3_RES_L;
	uint32_t F2_Z4_RES_H;
	uint32_t F2_Z4_RES_L;	
	uint32_t F2_Z5_RES_H;
	uint32_t F2_Z5_RES_L;		
	
	
  uint32_t F3_Z12_RES_H;
  uint32_t F3_Z12_RES_L;
  uint32_t F3_Z34_RES_H;
  uint32_t F3_Z34_RES_L;
  uint32_t F3_Z13_RES_H;
  uint32_t F3_Z13_RES_L;
  uint32_t F3_Z23_RES_H;
  uint32_t F3_Z23_RES_L;	
	uint32_t F3_Z24_RES_H;
  uint32_t F3_Z24_RES_L;
  uint32_t F3_Z14_RES_H;
  uint32_t F3_Z14_RES_L;
	uint32_t F3_Z1_RES_H;
	uint32_t F3_Z1_RES_L;	
	uint32_t F3_Z2_RES_H;
	uint32_t F3_Z2_RES_L;
	uint32_t F3_Z3_RES_H;
	uint32_t F3_Z3_RES_L;
	uint32_t F3_Z4_RES_H;
	uint32_t F3_Z4_RES_L;	
	uint32_t F3_Z5_RES_H;
	uint32_t F3_Z5_RES_L;		   
	
	
	uint32_t RESERVED1[61]; //RESERVED1
	uint32_t RESERVED[1];
		
}RESVal_TypeDef;



typedef struct 
{				
    uint32_t paddr;
}AddrMap_TypeDef;

typedef enum 
{		
	ISCMD  = 0,   // 0 �ǵ�ַ 1������ 
  b_sleep=1,
	b_flash=2,
	b_analysis=3,
	b_unlock=4,
	ISMODE=5,   //��ģʽ
	b_wakeup=6,
}Functionaddrflag;

extern AddrMap_TypeDef AddrMap;
extern uint8_t addr_flag;
/******************************************************************************/
/*                         csa37f60 memory map                                */
/******************************************************************************/
#define SRAM_BASE	               ((uint32_t)0x20000000)



#define Sizeof_EquipmentConfig        ((uint32_t)(0x00000040))  //�豸��������С
#define Sizeof_EquipmentInfo          ((uint32_t)(0x00000018))  //�û���Ϣ����С
#define Sizeof_UserInfo               ((uint32_t)(0x00000080))  //�û���Ϣ����С
#define Sizeof_UserBIAPart            ((uint32_t)(0x00000080))  //�û�BIA��������С
#define Sizeof_Analysis               ((uint32_t)(0x00000080))  //�����������С
#define Sizeof_ADCVal                 ((uint32_t)(0x00000080))  //ADCֵ����С
#define Sizeof_Log                    ((uint32_t)(0x00000018))  //log����С
#define Sizeof_RESVal                 ((uint32_t)(0x00000080))  //��ʵ��������С


#define EquipmentConfig_BASE         ((uint32_t)(SRAM_BASE+0x00001000))                           //�豸��������ʼ
#define EquipmentInfo_BASE           ((uint32_t)(EquipmentConfig_BASE+(Sizeof_EquipmentConfig<<2))) //�豸��Ϣ����ʼ
#define UserInfo_BASE                ((uint32_t)(EquipmentInfo_BASE+  (Sizeof_EquipmentInfo<<2)))   //�û���Ϣ����ʼ
#define UserBIAPart_BASE             ((uint32_t)(UserInfo_BASE+       (Sizeof_UserInfo<<2)))        //�û�BIA��������ʼ
#define Analysis_BASE                ((uint32_t)(UserBIAPart_BASE+    (Sizeof_UserBIAPart<<2)))     //�����������ʼ
#define ADCVal_BASE                  ((uint32_t)(Analysis_BASE+       (Sizeof_Analysis<<2)))        //ADCֵ����ʼ
#define Log_BASE										 ((uint32_t)(ADCVal_BASE+         (Sizeof_ADCVal<<2)))          //ͨ����־����ʼ
#define RESVal_BASE                  ((uint32_t)(Log_BASE+            (Sizeof_Log<<2)))             //��ʵ��������ʼ


#define EquipmentConfig_END           (EquipmentInfo_BASE-4) //�豸����������
#define EquipmentInfo_END             (UserInfo_BASE-4)      //�豸��Ϣ������
#define UserInfo_END                  (UserBIAPart_BASE-4)   //�û���Ϣ������
#define UserBIAPart_END               (Analysis_BASE-4)      //�û�����BIA������
#define Analysis_END                  (ADCVal_BASE-4)        //�������������
#define ADCVal_END                    (Log_BASE-4)           //ADCֵ������
#define Log_END                       (RESVal_BASE-4)        //ͨ����־������
#define RESVal_END                    ((uint32_t)RESVal_BASE+(Sizeof_RESVal<<2)-4)//��ʵ������


#define Sizeof_LastBlock               Sizeof_RESVal //���һ��ȡ��С 
#define LastBlock_BASE                 RESVal_BASE   //���һ������ʼ


/******************************************************************************/
/*                         User memory map     �û�����                       */
/******************************************************************************/
#define U_EquipmentConfig_BASE         ((uint32_t)(SRAM_BASE+0x00001000))//�豸��������ʼ
#define U_EquipmentInfo_BASE           ((uint32_t)(SRAM_BASE+0x00001040))//�豸��Ϣ����ʼ
#define U_UserInfo_BASE                ((uint32_t)(SRAM_BASE+0x00001058))//�û���Ϣ����ʼ
#define U_UserBIAPart_BASE             ((uint32_t)(SRAM_BASE+0x000010D8))//�û�BIA��������ʼ
#define U_Analysis_BASE                ((uint32_t)(SRAM_BASE+0x00001158))//�����������ʼ
#define U_ADCVal_BASE                  ((uint32_t)(SRAM_BASE+0x000011D8))//ADCֵ����ʼ
#define U_Log_BASE										 ((uint32_t)(SRAM_BASE+0x00001258)) //ͨ����־����ʼ
#define U_RESVal_BASE                  ((uint32_t)(SRAM_BASE+0x00001270)) //��ʵ��������ʼ


#define U_EquipmentConfig_END           (U_EquipmentInfo_BASE-1) //�豸����������
#define U_EquipmentInfo_END             (U_UserInfo_BASE-1)      //�豸��Ϣ������
#define U_UserInfo_END                  (U_UserBIAPart_BASE-1)   //�û���Ϣ������
#define U_UserBIAPart_END               (U_Analysis_BASE-1)      //�û�����BIA������
#define U_Analysis_END                  (U_ADCVal_BASE-1)        //�������������
#define U_ADCVal_END                    (U_Log_BASE-1)           //ADCֵ������
#define U_Log_END                       (U_RESVal_BASE-1)        //ͨ����־������
#define U_RESVal_END                    ((uint32_t)U_RESVal_BASE+Sizeof_RESVal-1)//��ʵ������


/******************************************************************************/
/*                         Block declaration                             */
/******************************************************************************/
#define EquMent							((EquipmentConfig_TypeDef*) EquipmentConfig_BASE) //�豸������
#define EquInfo							((EquipmentInfo_TypeDef*  )   EquipmentInfo_BASE) //�豸��Ϣ��
#define UsrInfo							((UserInfo_TypeDef*       )        UserInfo_BASE) //�û���Ϣ��
#define UsrBIAP             ((UserBIAPart_TypeDef*    )     UserBIAPart_BASE) //�û�BIA������
#define Analys              ((Analysis_TypeDef*       )        Analysis_BASE) //���������
#define ADCVal              ((ADCVal_TypeDef*         )          ADCVal_BASE) //ADCֵ��
#define LOG                 ((Log_TypeDef*            )             Log_BASE) //ͨ����־�� 
#define RESVal              ((RESVal_TypeDef*         )          RESVal_BASE) //��ʵ������


#define  ON_OFF 7    //STATUS
#define  CK     7    //CONFIG_K

#define  F1C_FLAG   7  //F1CV_FLAG
#define  F1V_FLAG_6 6
#define  F1V_FLAG_5 5
#define  F1_FLASH   4

#define  F2C_FLAG   7  //F2CV_FLAG
#define  F2V_FLAG_6 6
#define  F2V_FLAG_5 5
#define  F2_FLASH   4

#define  F3C_FLAG   7  //F3CV_FLAG
#define  F3V_FLAG_6 6
#define  F3V_FLAG_5 5
#define  F3_FLASH   4

#define  Z_REDY       7  //Z_STATUS
#define  Z_selfcheck  6
#define  Z_S12        5
#define  Z_S34        4
#define  Z_S14        3
#define  Z_S13        2
#define  Z_S23        1
#define  Z_S24        0

#define  Err_Short       7 //ERR_STATUS
#define  Err_lowlimit    6
#define  Err_hightlimit  5
#define  Err_exchange    4
#define  Err_Parm        3
#define  Err_Stb         2

#define  C_Recv         7 //C_STATUS
#define  C_Parm         6
#define  C_Exe          5
#define  C_Ok           4

//F_STATUS

//��������
#define	 USER_CMD     0x3F5A
#define	 MODE_CMD     0xF000
#define	 SLEEP_PARM     0x35
#define	 WAKEUP_PARM    0x53
#define	 ANALYSIS_PARM  0x04
#define	 FLASH_PARM     0x05
#define	 UNLOCK_PARM    0x06


//RW���仮�� [L---R]��RW ����֮�ⶼ��R
#define  RW_Bank0_L   (uint32_t)&EquMent->STATUS
#define  RW_Bank0_R   (uint32_t)&EquMent->CONFIG_K

#define  RW_Bank1_L   ((uint32_t)&UsrInfo->WTH)
#define  RW_Bank1_R   ((uint32_t)&UsrInfo->F3_Z5_Res_L)


#define  WRITE_LAST    RW_Bank1_R  //
#define  READ_LAST     RESVal_END//Log_END  //

void addr_map(uint16_t user_addr);
void Clr_All_Block_Ram(void);
void Clr_RESVal_Ram(void);
void Clr_UserBIAPart_Ram(void);
void Clr_Analysis_Ram(void);
void Clr_ADCVal_Ram(void);
void Clr_UsrInfo_ResF1(void);
void Clr_UsrInfo_ResF2(void);
void Clr_UsrInfo_ResF3(void);
#endif


/*
//�������

    uint32_t BFR_H;        //��֬�ٷֱ�
    uint32_t BFR_L;
    uint32_t FM_H;         //֬����
		uint32_t FM_L;
		uint32_t SLM_H;        //������
		uint32_t SLM_L;	
		
		uint32_t TFR_H;        //��ˮ��
		uint32_t TFR_L; 
		uint32_t TF_H;         //��ˮ��
		uint32_t TF_L; 		
		uint32_t BMR_H;      //������л
		uint32_t BMR_L;		
		uint32_t MSW_H;        //������
		uint32_t MSW_L;		
		
		uint32_t VFR_H;        //����֬���ȼ�
		uint32_t VFR_L;		
		uint32_t Body_Age;  //��������
		uint32_t B_Score;     //��������
		uint32_t BW_H;         //��׼����
		uint32_t BW_L;		
		uint32_t EXF_H;         //ϸ����Һ
		uint32_t EXF_L;		
		uint32_t INF_H;         //ϸ����Һ
		uint32_t INF_L;		
		uint32_t LBM_H;         //ȥ֬����
		uint32_t LBM_L;		
		uint32_t PM_H;          //������
		uint32_t PM_L;	
		uint32_t EE_H;          //ˮ�׶�
		uint32_t EE_L;		
		uint32_t OD_H;          //���ֶ�
		uint32_t OD_L;		
		uint32_t BIM_H;         //����ָ��
		uint32_t BIM_L;		
		uint32_t BM_H;          //��׼����
		uint32_t BM_L;		
		uint32_t MC_H;          //�������
		uint32_t MC_L; 		
		uint32_t WC_H;          //���ؿ���
		uint32_t WC_L;		
		uint32_t FC_H;          //֬������
		uint32_t FC_L;		
		uint32_t TW_H;          //Ŀ������
		uint32_t TW_L;		
		uint32_t SMM_H;         //��������
		uint32_t SMM_L;		
		uint32_t BFR_RA_H;      //Z2 ��֬��
		uint32_t BFR_RA_L;		
		uint32_t BFR_LA_H;      //Z1 ��֬��
		uint32_t BFR_LA_L;		
		uint32_t BFR_RL_H;      //Z4 ��֬��
		uint32_t BFR_RL_L;
		uint32_t BFR_LL_H;      //Z3 ��֬��
		uint32_t BFR_LL_L;		
		uint32_t BFR_TR_H;      //Z5 ��֬��
		uint32_t BFR_TR_L;
		uint32_t SLM_RA_H;      //Z2 ������
		uint32_t SLM_RA_L;		
		uint32_t SLM_LA_H;      //Z1 ������
		uint32_t SLM_LA_L;
		uint32_t SLM_RL_H;      //Z4 ������
		uint32_t SLM_RL_L;
		uint32_t SLM_LL_H;      //Z3 ������
		uint32_t SLM_LL_L;
		uint32_t SLM_TR_H;      //Z5 ������
		uint32_t SLM_TR_L;
		uint32_t JW_H;          //��Χ
		uint32_t JW_L;
		uint32_t WL_H;          //��Χ
		uint32_t WL_L;          
		uint32_t HL_H;          //��Χ
		uint32_t HL_L;
		uint32_t XW_H;          //��Χ
		uint32_t XW_L;
		uint32_t RAW_H;         //Z2 ���ϱ�Χ
		uint32_t RAW_L;
		uint32_t LAW_H;         //Z1 ���ϱ�Χ
		uint32_t LAW_L;
		uint32_t RLW_H;         //Z4 �Ҵ���Χ
		uint32_t RLW_L;
		uint32_t LLW_H;         //Z3 �Ҵ���Χ
		uint32_t LLW_L;
		
typedef struct
{
               BFR       //��֬�ٷֱ�
		uint16_t	fat_wgt;   //��֬��
	  uint8_t   fat_per;   //��֬��
	  uint16_t  muscle_wgt;//������
	  uint16_t  water_wgt; //ˮ��
	  uint16_t  water_per; //ˮ��
	  uint16_t  BMR;       //������л
	  uint16_t  bone_salt; //������
	  uint8_t   VFG;       //����֬���ȼ�
    uint8_t   body_age;  //��������
	  uint8_t   body_score;//�������
	  uint8_t   std_wgt;   //��׼����
	  uint16_t  cell_out;  //ϸ����Һ
	  uint16_t  cell_in;   //ϸ����Һ
	  
    uint16_t   LBM;      //������
	  uint16_t  protein;   //������
	  uint16_t  edema_degree;//ˮ�׶�
	  uint16_t  obesity_degree;//���ֶ�
	  uint16_t  BMI;
	  uint16_t  std_muscle;    //��׼����
	  uint16_t  muscle_control; //�������
	  uint16_t  weight_control; //���ؿ���
	  uint16_t  fat_control; //֬������
		
		uint16_t  rh_fat_per;  //����֬����
		uint16_t  lh_fat_per;  //����֬����
		uint16_t  rl_fat_per;  //�ҽ�֬����
		uint16_t  ll_fat_per;  //���֬����
		uint16_t  trunk_fat_per;  //����֬����
		
		uint16_t  rh_muscle;//���ּ���
		uint16_t  lh_muscle;//���ּ���
		uint16_t  rl_muscle;//�ҽż���
		uint16_t  ll_muscle;//��ż���
		uint16_t  trunk_muscle;  //���ɼ���
		
		uint16_t  neck_perimeter;  //��Χ
		uint16_t  waist_perimeter; //��Χ
		uint16_t  hip_perimeter;   //��Χ
		uint16_t  chest_perimeter; //��Χ
		uint16_t  r_hip_perimeter; //������Χ
		uint16_t  l_hip_perimeter; //������Χ
		uint16_t  r_leg_perimeter; //�Ҵ���Χ
		uint16_t  l_leg_perimeter; //�����Χ
		uint8_t   waist_hip_ratio; //���α�
    uint8_t   heart_rate;      //����
		uint8_t   breathing_rate;  //������
		uint8_t   breathing_times;  //��������
}Measure_Results_TypeDef;
*/
