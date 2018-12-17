/**
  ******************************************************************************
  * @file    csa37fx60_it.h 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2017 chipsea</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CSA37FX60_IT_H
#define __CSA37FX60_IT_H

/* Includes ------------------------------------------------------------------*/
#include "csa37fx60.h"
#include "delay.h" 
#include "addr_map.h" 
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void BOD_IRQHandler(void);
void WDT_IRQHandler(void);
void TMR0_IRQHandler(void);
void TMR1_IRQHandler(void);
void UART0_IRQHandler(void);
void I2C0_IRQHandler(void);
void AFE0_IRQHandler(void);
void AFE1_IRQHandler(void);
void PD_WU_IRQHandler(void);

#endif /* __CSA37FX60_IT_H */

/******************* (C) COPYRIGHT 2017 chipsea *****END OF FILE****/
