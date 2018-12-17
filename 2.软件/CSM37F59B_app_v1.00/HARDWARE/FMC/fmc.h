#ifndef __FMC_H
#define __FMC_H

#include "csa37fx60.h"
#include "CS1258.h"

//校验区数据
#define APROM_ADDR 0xEC00 //前2字节
#define CHECK_ADDR 0xEDFC //最后字节
//校验区数据

#define FMC_ADDR   0xEE00

#define ID_ADDR    0xEE20 //ID开始
#define BOOT_ADDR  0xEE60//0xEE3C //第1字节  ????????????????????????

/*----------------------------------------------
0xEE00  FREQ      XX XX XX  0      
0xEE04  PART      XX XX XX  1
0xEE08  K1        XX XX XX  2
0xEE0C  K2        XX XX XX  3
0xEE10  K3        XX XX XX  4
0xEE14  MID_HH    XX XX XX  5
0xEE18  MID_H     XX XX XX  6
0xEE1C  MID_L     XX XX XX  7
0xEE20  MID_LL    XX XX XX  8
0xEE24  SID_HH    XX XX XX  9
0xEE28  SID_H     XX XX XX  10
0xEE2C  SID_L     XX XX XX  11
0xEE30  SID_LL    XX XX XX  12
0xEE34  HMV       XX XX XX  13 不用
0xEE38  FSV       XX XX XX  14 不用
0xEE3C  BOOT_VER  XX XX XX  15

        多频段/单频段
0xEE00  FREQ      					XX XX XX  0      
0xEE04  PART      					XX XX XX  1
0xEE08  K1        					XX XX XX  2
0xEE0C  K2        					XX XX XX  3
0xEE10  K3        					XX XX XX  4
0xEE14  MID_HH    					XX XX XX  5
0xEE18  MID_H     					XX XX XX  6
0xEE1C  MID_L     					XX XX XX  7
0xEE20  MID_LL    					XX XX XX  8
0xEE24  SID_HH    					XX XX XX  9
0xEE28  SID_H     					XX XX XX  10
0xEE2C  SID_L     					XX XX XX  11
0xEE30  SID_LL    					XX XX XX  12
0xEE34  M_HAND/S_HAND       XX XX XX  13
0xEE38  ---   /SA_HAND      XX XX XX  14
0xEE3C  M_LEG /S_LEG        XX XX XX  15
0xEE40  ---   /SA_LEG       XX XX XX  16
0xEE44  M_BODY/S_BODY       XX XX XX  17
0xEE48  ---   /SA_BODY      XX XX XX  18
0xEE4C  M_HEART             XX XX XX  19
0xEE50  ---                 XX XX XX  20
0xEE54  BOOT_VER            XX XX XX  21

0xEE00  FREQ      					XX XX XX  0      
0xEE04  PART      					XX XX XX  1
0xEE08  K1_H        				XX XX XX  2
0xEE0C  K1_L        				XX XX XX  3
0xEE10  K2_H       					XX XX XX  4
0xEE14  K2_L        				XX XX XX  5
0xEE18  K3_H       					XX XX XX  6
0xEE1C  K3_L        				XX XX XX  7
0xEE20  MID_HH    					XX XX XX  8
0xEE24  MID_H     					XX XX XX  9
0xEE28  MID_L     					XX XX XX  10
0xEE2C  MID_LL    					XX XX XX  11
0xEE30  SID_HH    					XX XX XX  12
0xEE34  SID_H     					XX XX XX  13
0xEE38  SID_L     					XX XX XX  14
0xEE3C  SID_LL    					XX XX XX  15
0xEE40  M_HAND/S_HAND       XX XX XX  16
0xEE44  ---   /SA_HAND      XX XX XX  17
0xEE48  M_LEG /S_LEG        XX XX XX  18
0xEE4C  ---   /SA_LEG       XX XX XX  19
0xEE50  M_BODY/S_BODY       XX XX XX  20
0xEE54  ---   /SA_BODY      XX XX XX  21
0xEE58  M_HEART             XX XX XX  22
0xEE5C  ---                 XX XX XX  23
0xEE60  BOOT_VER            XX XX XX  24
------------------------------------------------*/
//上表编号
typedef enum
{ N_FREQ=0,
	N_PART=1,	
  N_K1_H=2,
	N_K1_L=3,
  N_K2_H=4,
	N_K2_L=5,
  N_K3_H=6,
  N_K3_L=7,	
  N_M_HH=8, //以上编号用到
  N_M_H=9,
  N_M_L=10,	
  N_M_LL=11,
  N_S_HH=12,
  N_S_H=13,	
  N_S_L=14,
  N_S_LL=15,
  N_HMV=16,	
  N_FSV=17,
  N_BOOT=18,	//boot 用到
}numdefault;

//保存flash的顺序
typedef enum
{
	num_freq=0,
	num_m_part=1,
  num_freq1k_val=2,
  num_freq2k_val=3,
  num_freq3k_val=4,	
}Functionflash;

extern uint8_t flash_data;//要写入flash的数据
extern uint8_t flash_flag;

extern uint8_t FMC_Data[512];
extern uint8_t Default_Data[32];
extern uint8_t Temp_FMC_Data[512];

void User_FMC_Init(void);
void load_fmc_data(void);
BOOL Cmd_WriteTypeByteToFlash(uint16_t data,uint8_t flash_num,uint8_t type);
void Check_Flash_Cmd(uint8_t data);



void load_id_data(void);

#endif
