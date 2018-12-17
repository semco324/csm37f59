/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from  CHIPSEA.
 *
 *            (C) COPYRIGHT 2015 SHENZHEN CHIPSEA TECHNOLOGIES CO.,LTD.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from CHIPSEA.
 *
 *      Release Information : CSA37FX60 
 *-----------------------------------------------------------------------------
 */
 
#ifndef __CSA37FX60_NVIC_H
#define __CSA37FX60_NVIC_H

#include "csa37fx60.h"
#include "absacc.h"
#include "csa37fx60_lib.h"

//中断源列表
#define IRQ_BOD_HVD_RPL     BIT(0)  //IRQ 0
#define IRQ_WDT_WWDT        BIT(1)  //IRQ 1
#define IRQ_TMR0            BIT(2)  //IRQ 2
#define IRQ_TMR1            BIT(3)  //IRQ 3
#define IRQ_UART            BIT(4)  //IRQ 4
#define IRQ_I2C             BIT(5)  //IRQ 5
#define IRQ_AFE0            BIT(6)  //IRQ 6
#define IRQ_AFE1            BIT(7)  //IRQ 7
#define IRQ_PD_WU           BIT(8)  //IRQ 8

void NVIC_IRQxEnable(uint32_t IRQ_x);
void NVIC_IRQxDisable(uint32_t IRQ_x);
void NVIC_IRQxSetPending(uint32_t IRQ_x);
void NVIC_IRQxClearPending(uint32_t IRQ_x);
void NVIC_IRQPriorityConfig(uint32_t IRQ_x , uint8_t priority);
void NVIC_NMI_IRQSource(uint32_t IRQ_x , FunctionalState NewState);


#endif /* __CSA37FX60_NVIC_H */


