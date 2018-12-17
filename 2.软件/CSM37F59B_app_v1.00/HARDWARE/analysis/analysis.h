#ifndef __ANALYSIS_H
#define __ANALYSIS_H

#include "addr_map.h"
#include "CS1258.h"

//������Ϣ��Χ
#define WEIGHT_MAX   1500 //kg*10
#define WEIGHT_MIN   200  //kg*10

#define HT_MAX   220  //cm
#define HT_MIN   90  //cm

#define AGE_MAX   99  //year
#define AGE_MIN   18  //year

//#define   UART_HR
#define HR_MODE

//	//�������
//extern uint8_t B_SEX; //�Ա� 1 man 0 weman
//extern uint8_t B_Age; //����
//extern double  B_H;   //��� mm
//extern double  B_Wt;  //���� kg
//extern double  B_Z;   //˫���迹 ohm
//extern double  B_Z_RA;//Z2
//extern double  B_Z_LA;//Z1
//extern double  B_Z_RL;//Z4
//extern double  B_Z_LL;//Z3
//extern double  B_Z_TR;//Z5

//������� 24

//�ɷ���� 6
extern double B_BFP;        //��֬��
extern double B_SLM;        //������**
extern double B_BMC;        //������**
extern double B_BWP;        //��ˮ����
extern double B_PP;         //��������
extern double B_SMM;        //��������* 4-8 **

/*
��ˮ�� = ���� * B_BWP
ȥ֬���� = ���� - ���� * B_BFR
֬���� = ���� * B_BFR
������ = ���� * B_PP
extern double B_TF;         //��ˮ��*
extern double B_LBM;        //ȥ֬����*
extern double B_FM;         //֬����*
extern double B_PM;         //������*
*/

//������ܲ��� 9
extern uint16_t B_BMR;      //������л* 
extern double B_VFR;        //����֬���ȼ�*
extern uint8_t B_MA;        //��������*  B_Body_Age--->B_MA
extern double B_BMI;        //����ָ��***************
extern uint8_t B_SBC;        //����÷�   B_Score-->B_SBC
extern double B_BW;         //��׼����
extern double B_WC;         //���ؿ���
extern double B_MC;         //�������
extern double B_FC;         //֬������


//�ڶβ��� 11
extern double B_RAFP;      //Z2 ��֬�� 8
extern double B_LAFP;      //Z1 ��֬��
extern double B_RLFP;      //Z4 ��֬��
extern double B_LLFP;      //Z3 ��֬��
extern double B_TFP;       //Z5 ��֬��

extern double B_RAMM;      //Z2 ������
extern double B_LAMM;      //Z1 ������
extern double B_RLMM;      //Z4 ������
extern double B_LLMM;      //Z3 ������
extern double B_TMM;       //Z5 ������

extern double B_WHR;    //���α�






//extern double B_BW;         //��׼����*
//extern double B_EXF;         //ϸ����Һ*
//extern double B_INF;         //ϸ����Һ*


//extern double B_EE;          //ˮ�׶�*
//extern double B_OD;          //���ֶ�*

//extern double B_BM;          //��׼����*
//extern double B_MC;          //�������*
//extern double B_WC;          //���ؿ���*
//extern double B_FC;          //֬������*
//extern double B_TW;          //Ŀ������



//extern double B_JW;          //��Χ
//extern double B_WL;          //��Χ
//extern double B_HL;          //��Χ
//extern double B_XW;          //��Χ
//extern double B_LAW;         //Z1 ���ϱ�Χ
//extern double B_RLW;         //Z4 �Ҵ���Χ
//extern double B_LLW;         //Z3 �Ҵ���Χ 2.3.4

BOOL analysis_parm(void);
void CS125X_XLCL_Initial(void);
void CS125X_XLCL_Initial_Per(void);
uint8_t HRI(void);


extern uint32_t B_temp_XLCL;
//IO 
#define SIM_TX_L  GPIO_WriteBits(GPIO_PA11,0) //GPIOA->PA_DOUT&=~SIM_TX_PIN// //Tx 0
#define SIM_TX_H  GPIO_WriteBits(GPIO_PA11,1) //GPIOA->PA_DOUT|=SIM_TX_PIN////Tx 1


#endif
