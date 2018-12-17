#ifndef __BOOT_H
#define __BOOT_H
#include "csa37fx60.h"
#include "utimer.h"
#include "uiic.h"
/*
----0x0000_EFFF
存储数据区
----0x0000_EE00
校验区 CHECK_ADDR
----0x0000_EC01
程序区
...
...
...
----0x0000_0000
*/

#define  CHECK_ADDR 0x0000EC00

#define  FMC_ADDR   0x0000EE00
#define  BOOT_ADDR  0x0000EE60//0x0000EE3C

#define  LDROM_MAJOR 0x01 //LDROM 主版本 


#define N_BOOT  24//15
extern uint8_t APROM_Major;
extern uint8_t APROM_Minor; //APROM 主版本 副版本
extern uint8_t Code_IIC_Buf0[512];//APROM程序区缓存
extern uint8_t Code_IIC_Buf1[512];//APROM检查区缓存

extern uint16_t IIC_ReCount; //iic接受计数
extern uint16_t IIC_HostRWAddr;//boot 读写地址

extern uint8_t  IIC_ReDataFinsh;   //IIC 数据接收完成标记
extern uint8_t  IIC_WriteflashCmd; //IIC写flash命令
extern uint8_t  IIC_Buf[16];       //iic地址缓存
extern uint8_t  Flag_APROMCheckOK;

extern uint8_t first_buf[512]; //第1块512内容  
extern uint8_t temp[4];


void GetAPROM_ID(void);
void IIC_CmdProc(void);
//void re_bin(uint8_t *buf,uint8_t *rebuf,uint16_t n);
void load_boot_ver(void);
#endif
