#ifndef __CSM37F58_H
#define __CSM37F58_H
#include "csa37fx60.h"

extern uint32_t BIA_FLAG;
//flag 
typedef enum 
{		
	
	Redy   		  =0,    //模组是否准备好	  1 是   0 没有
	Err_Short   =1,    //内短出错标志     1 错    0 对
	Err_Hight   =2,    //上限出错标志     1 错    0 对
	Err_Low     =3,   //下限出错标志     1 错    0 对
	Err_post    =4,   //站姿异常判断     1 错    0 对
	time        =5,	
	START       =6,   //按下开始测量
}FunctionBIAFlag;

//base
#define U_EquipmentConfig_BASE         0x1000 //设备配置区开始
#define U_EquipmentInfo_BASE           0x1040 //设备信息区开始
#define U_UserInfo_BASE                0x1058 //用户信息区开始
#define U_UserBIAPart_BASE             0x10D8 //用户BIA测试区开始
#define U_Analysis_BASE                0x1158 //分析结果区开始
#define U_ADCVal_BASE                  0x11D8 //ADC值区开始
#define U_Log_BASE										 0x1258 //通化日志区开始
#define U_RESVal_BASE                  0x1270 //真实电阻区开始

//offset
typedef enum
{
	 STATUS_os=0,       //
	 FREQ_os,
	 M_PART_os,	
	 FREQ1_CalRes_H_os,
	 FREQ1_CalRes_L_os,		
	 FREQ2_CalRes_H_os,
	 FREQ2_CalRes_L_os,		
	 FREQ3_CalRes_H_os,
	 FREQ3_CalRes_L_os,		
	 CONFIG_K_os,
	 F1CV_FLAG_os,	
	 F2CV_FLAG_os,
	 F3CV_FLAG_os,		
	 FREQ1K_VAL_os,//r
	 FREQ2K_VAL_os,//r	
	 FREQ3K_VAL_os,//r	
	 Z_STATUS_os,  //r		
	 ERR_STATUS_os,//r		
	 C_STATUS_os,  //r		
	 F_STATUS_os,  //r		
}FunctionEquipmentConfig;

typedef enum
{
	 MID_HH_os=0,
	 MID_H_os,
	 MID_L_os,
	 MID_LL_os,
	 SID_HH_os,
	 SID_H_os,
	 SID_L_os,
	 SID_LL_os,
	 HMV_os,
	 FMV_os,
	 FSV_os,
}FunctionEquipmentInfo;

//addr=base+offest
//设备配置区rw    26(64)
#define STATUS  										(U_EquipmentConfig_BASE+STATUS_os)
#define FREQ    										(U_EquipmentConfig_BASE+FREQ_os)
#define FREQ1_CalRes_H							(U_EquipmentConfig_BASE+FREQ1_CalRes_H_os)
#define FREQ1_CalRes_L	            (U_EquipmentConfig_BASE+FREQ1_CalRes_L_os)
#define FREQ2_CalRes_H              (U_EquipmentConfig_BASE+FREQ2_CalRes_H_os)
#define FREQ2_CalRes_L							(U_EquipmentConfig_BASE+FREQ2_CalRes_L_os)
#define FREQ3_CalRes_H							(U_EquipmentConfig_BASE+FREQ3_CalRes_H_os)
#define FREQ3_CalRes_L							(U_EquipmentConfig_BASE+FREQ3_CalRes_L_os)
#define CONFIG_K  									(U_EquipmentConfig_BASE+CONFIG_K_os)
#define F1CV_FLAG	 									(U_EquipmentConfig_BASE+F1CV_FLAG_os)
#define F2CV_FLAG 									(U_EquipmentConfig_BASE+F2CV_FLAG_os)
#define F3CV_FLAG	 									(U_EquipmentConfig_BASE+F3CV_FLAG_os)
#define FREQ1K_VAL 									(U_EquipmentConfig_BASE+FREQ1K_VAL_os)//r 
#define FREQ2K_VAL 									(U_EquipmentConfig_BASE+FREQ2K_VAL_os)//r	
#define FREQ3K_VAL 									(U_EquipmentConfig_BASE+FREQ3K_VAL_os)//r
#define Z_STATUS   									(U_EquipmentConfig_BASE+Z_STATUS_os)//r		
#define ERR_STATUS 									(U_EquipmentConfig_BASE+ERR_STATUS_os)//r		
#define C_STATUS   									(U_EquipmentConfig_BASE+C_STATUS_os)//r		
#define F_STATUS   									(U_EquipmentConfig_BASE+F_STATUS_os)//r		
//设备信息区 r  11(24)
#define MID_HH                      (U_EquipmentInfo_BASE+MID_HH_os)
#define MID_H 											(U_EquipmentInfo_BASE+MID_H_os)
#define MID_L 											(U_EquipmentInfo_BASE+MID_L_os)
#define MID_LL 											(U_EquipmentInfo_BASE+MID_LL_os)
#define SID_HH 											(U_EquipmentInfo_BASE+SID_HH_os)
#define SID_H 											(U_EquipmentInfo_BASE+SID_H_os)
#define SID_L 											(U_EquipmentInfo_BASE+SID_L_os)
#define SID_LL 											(U_EquipmentInfo_BASE+SID_LL_os)
#define HMV 												(U_EquipmentInfo_BASE+HMV_os)
#define FMV 												(U_EquipmentInfo_BASE+FMV_os)
#define FSV 												(U_EquipmentInfo_BASE+FSV_os)
//用户信息区rw      74(128)
//用户测试BIA区 r   69(128)
//成分分析结果区 r      128
//测试过程数据 r     54(128)
//log                 24
//真实电阻            63(128)

uint8_t howmany(uint8_t data);
#endif
