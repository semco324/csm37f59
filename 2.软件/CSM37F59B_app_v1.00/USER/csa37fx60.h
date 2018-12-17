/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2015 SHENZHEN CHIPSEA TECHNOLOGIES CO.,LTD. All rights reserved.                           */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#ifndef __CSA37FX60_H__
#define __CSA37FX60_H__


#include <stdint.h>                   /* Include standard types */
#include "system_csa37fx60.h"


#define     __I     volatile const    /*!< defines 'read only' permissions     */
#define     __O     volatile          /*!< defines 'write only' permissions    */
#define     __IO    volatile          /*!< defines 'read / write' permissions  */

/*******************************************************************************/
/*                 Register Abstraction                                        */
/*******************************************************************************/
typedef struct
{
	__IO uint32_t RMCON;					//00
	
} SRAM_TypeDef;


typedef struct
{
  __IO uint32_t ISPCON;					//00
	__IO uint32_t ISPADR;					//04
	__IO uint32_t ISPDAT;					//08
	__IO uint32_t ISPCMD;					//0C
	__IO uint32_t ISPTRG;					//10
	__I  uint32_t DFBADR;					//14
	__IO uint32_t ISPSTA;					//18
	
} FMC_TypeDef;

typedef struct
{
  __IO uint32_t NVIC_ISER;			//100
         uint32_t RESERVED0[31];        //100 ~ 17C Reserved
	__IO uint32_t NVIC_ICER;			//180
         uint32_t RESERVED1[31];        //184 ~ 1FC Reserved
	__IO uint32_t NVIC_ISPR;			//200
         uint32_t RESERVED2[31];        //200 ~ 27C Reserved
	__IO uint32_t NVIC_ICPR;			//280
         uint32_t RESERVED3[95];        //284 ~ 3FC Reserved
	__IO uint32_t NVIC_IPR0;			//400
	__IO uint32_t NVIC_IPR1;			//404
	__IO uint32_t NVIC_IPR2;			//408
	
} NVIC_TypeDef;

typedef struct
{
  __I  uint32_t PDID;					  //00
	__IO uint32_t PA_MFP;			   	//04
			 uint32_t RESERVED0[15];        	//08 ~ 40 Reserved
			 uint32_t RESERVED1[3];         	//44 ~ 4C Reserved
	__IO uint32_t TEMP_CR;		   	//50
	__I  uint32_t TEMP_DR;		   	//54
	     uint32_t RESERVED2[2];         	//58 ~ 5C Reserved
	__IO uint32_t AFE_TCR;		   	//60
	     uint32_t RESERVED4[3];         	//64 68 6c Reserved
	__IO uint32_t RPL_DET_CR;     //70
	__IO uint32_t RPL_DET_TM;     //74
	__IO uint32_t RPL_DET_CNT;    //78
	     uint32_t RESERVED3[33];        	//7c ~ fC Reserved
	__IO uint32_t REGWRPROT;			//100
} GCR_TypeDef;

typedef struct
{
	__IO uint32_t IRQ0_SRC;				//00
	__IO uint32_t IRQ1_SRC;				//04
	__IO uint32_t IRQ2_SRC;				//08
	__IO uint32_t IRQ3_SRC;				//0C
	__IO uint32_t IRQ4_SRC;				//10
  __IO uint32_t IRQ5_SRC;				//14
	__IO uint32_t IRQ6_SRC;				//18
	__IO uint32_t IRQ7_SRC;				//1C
	__IO uint32_t IRQ8_SRC;				//20
       uint32_t RESERVED0[27];        	//24 ~ 7C Reserved
	__IO uint32_t NMI_SEL;				//80
  __IO uint32_t MCU_IRQ;				//84

} INT_TypeDef;

typedef struct
{
  __IO uint32_t SYST_CSR;				//00
	__IO uint32_t SYST_RVR;				//04
	__IO uint32_t SYST_CVR;				//08
	
} SYS_TICK_TypeDef;


typedef struct
{
  __I  uint32_t CPUID;					//00
	__IO uint32_t ICSR;						//04
			 uint32_t RESERVED0[1];	  	 			//08 Reserved
	__IO uint32_t AIRCR;					//0C
	__IO uint32_t SCR;						//10
			 uint32_t RESERVED1[1];	  	 			//14 Reserved
			 uint32_t RESERVED2[1];	  	 			//18 Reserved
	__IO uint32_t SHPR2;					//1C
	__IO uint32_t SHPR3;					//20

} SYS_CONTROL_TypeDef;


typedef struct
{
  __IO uint32_t PWR_CON;				//00
			 uint32_t RESERVED0[7];	  	   		//04 ~ 1c Reserved
	__IO uint32_t BACKUP0;				//20
			 uint32_t RESERVED1[3];	  	   		//24 ~ 2C Reserved
	__IO uint32_t VS_CR;				  //30
	
} PWR_TypeDef;


typedef struct
{
	__IO uint32_t RST_SRC;				//00
	__IO uint32_t IPRSTC1;				//04
	__IO uint32_t IPRSTC2;				//08
	__IO uint32_t BODCR;				  //0C
	__IO uint32_t PORCR;				  //10

} RST_TypeDef;


typedef struct
{
	__IO uint32_t	CLKCON;					//00
	__IO uint32_t	AHBCLK;					//04			
	__IO uint32_t	APBCLK;					//08
	__IO uint32_t	CLKSTATUS;			//0C
	__IO uint32_t	CLKSEL0;				//10
	__IO uint32_t	CLKSEL1;				//14
	__IO uint32_t	CLKSEL2;      	//18
	__IO uint32_t	CLKDIV;					//1C
	__IO uint32_t	PLLCON;					//20
	__IO uint32_t	FRQDIV;					//24
	
} CLKMU_TypeDef;


typedef struct
{
	__I  uint32_t	ADDR0;					//00
	__I  uint32_t	ADDR1;					//04
	__I  uint32_t	ADDR2;					//08
	__I  uint32_t	ADDR3;					//0c
	__I  uint32_t	ADDR4;					//10
	__I  uint32_t	ADDR5;					//14
	__I  uint32_t	ADDR6;					//18
	__I  uint32_t	ADDR7;					//1c
	__I  uint32_t	ADDR8;					//20
	__I  uint32_t	ADDR9;					//24
	__I  uint32_t	ADDR10;					//28
	__I  uint32_t	ADDR11;					//2c
	__I  uint32_t	ADDR12;					//30
	__I  uint32_t	ADDR13;					//34
	__I  uint32_t	ADDR14;					//38
	__I  uint32_t	ADDR15;					//3c
	__I  uint32_t	ADDR16;					//40
	__I  uint32_t	ADDR17;					//44
			 uint32_t RESERVED0[14]; 	    		//48 ~ 7C Reserved
	__IO uint32_t	ADCR;				  	//80
	__IO uint32_t	ADCHER;					//84
	     uint32_t RESERVED1; 		      		//88 Reserved
	__IO uint32_t	ADCMPR0;		  	//8C
	__IO uint32_t	ADCMPR1;		  	//90
	__IO uint32_t	ADSR;		  			//94
	__IO uint32_t	ADTDCR;		  		//98
	     uint32_t RESERVED2[25]; 		  		//9C ~ FC Reserved
	__IO uint32_t	PGACR;		  		//100
			 uint32_t RESERVED3[7]; 	    		//104 ~ 11C Reserved
	__IO uint32_t	ADCHSR0;	  		//120		
	__IO uint32_t	ADCHSR1;	  		//124	
	__IO uint32_t	ADCHSR2;	  		//128		
	__IO uint32_t	ADCHSR3;	  		//12C	
	__IO uint32_t	ADCHSR4;	  		//130		
	__IO uint32_t	ADCHSR5;	  		//134	
	__IO uint32_t	ADCHSR6;	  		//138		
	__IO uint32_t	ADCHSR7;	  		//13C	
	__IO uint32_t	ADCHSR8;	  		//140		
	__IO uint32_t	ADCHSR9;	  		//144	
	__IO uint32_t	ADCHSR10;	  		//148		
	__IO uint32_t	ADCHSR11;	  		//14C	
	__IO uint32_t	ADCHSR12;	  		//150		
	__IO uint32_t	ADCHSR13;	  		//154	
	__IO uint32_t	ADCHSR14;	  		//158		
	__IO uint32_t	ADCHSR15;	  		//15C	
	__IO uint32_t	DACR;	  	  		//160
	__IO uint32_t DADAT0;					//164
	__IO uint32_t DADAT1;			  	//168
	__IO uint32_t DADAT2;			  	//16C
	__IO uint32_t DADAT3;       	//170
	__IO uint32_t DADAT4;       	//174
	__IO uint32_t DADAT5;       	//178
	__IO uint32_t DADAT6;       	//17C
	__IO uint32_t DADAT7;       	//180
	__IO uint32_t DADAT8;       	//184
	__IO uint32_t DADAT9;       	//188
	__IO uint32_t DADAT10;      	//18C
	__IO uint32_t DADAT11;      	//190
	__IO uint32_t DADAT12;      	//194
	__IO uint32_t DADAT13;      	//198
	__IO uint32_t DADAT14;      	//19C
	__IO uint32_t DADAT15;      	//1A0
	
} AFE_TypeDef;


typedef struct
{
	__IO uint32_t	CRC_DR;			  	//00
	__IO uint32_t	CRC_IDR;		  	//04
	__IO uint32_t	CRC_CR;			  	//08
	__IO uint32_t	CRC_INIT;		  	//0c
} CRC32_TypeDef;


typedef struct
{
	__IO uint32_t	DIVIDEND;		  	//00
	__IO uint32_t	DIVISOR;		  	//04
	__IO uint32_t	DIVQUO;			  	//08
	__IO uint32_t	DIVREM;			  	//0C
	__IO uint32_t	DIVSTS;			  	//10
	
} HDIV_TypeDef;


typedef struct
{
  __IO uint32_t PA_PMD;					//00
	__IO uint32_t PA_OFFD;				//04
	__IO uint32_t PA_DOUT;    		//08
	__IO uint32_t PA_DMASK;   		//0c
	__I  uint32_t PA_PIN;     		//10	
	     uint32_t RESERVED1[4];  	     		//14 ~ 20 Reserved
	__IO uint32_t PA_PUEN;    		//24
	     uint32_t RESERVED4;    	     		//28 Reserved
	__IO uint32_t PA_TYPEn;   		//2c
			 uint32_t RESERVED2[55];  	   		//30 ~ 108 Reserved
	__IO uint32_t PA3_DOUT;     	//10c
	     uint32_t RESERVED3[5];  	     		//110 ~ 120 Reserved
	__IO uint32_t PA9_DOUT;     	//124
	__IO uint32_t PA10_DOUT;    	//128
	__IO uint32_t PA11_DOUT;    	//12c
	__IO uint32_t PA12_DOUT;    	//130

} GPIOA_TypeDef;


typedef struct
{	
	__IO uint32_t I2C_CON;  					//00
	__IO uint32_t I2C_TAR;  					//04
	__IO uint32_t I2C_SAR;  					//08
	     uint32_t RESERVED1[1];                //0c Reserved
	__IO uint32_t I2C_DATA_CMD;  			//10
	__IO uint32_t I2C_SS_SCL_HCNT;  	//14
	__IO uint32_t I2C_SS_SCL_LCNT;  	//18
	__IO uint32_t I2C_FS_SCL_HCNT;  	//1C
	__IO uint32_t I2C_FS_SCL_LCNT;  	//20
	     uint32_t RESERVED2[2];                //24 28 Reserved
	__I  uint32_t I2C_INT_STAT;  			//2C
	__IO uint32_t I2C_INT_MASK;  			//30
	__I  uint32_t I2C_RAW_INT_ST;  		//34
	__IO uint32_t I2C_RX_TL;  				//38
	__IO uint32_t I2C_TX_TL;  				//3C
	__I  uint32_t I2C_CLR_INT;  			//40
	__I  uint32_t I2C_CLR_RX_UD;  		//44
	__I  uint32_t I2C_CLR_RX_OV;  		//48
	__I  uint32_t I2C_CLR_TX_OV;  		//4C
	__I  uint32_t I2C_CLR_RD_REQ;  		//50
	__I  uint32_t I2C_CLR_TX_ABRT;  	//54
	__I  uint32_t I2C_CLR_RX_DONE;  	//58
	__I  uint32_t I2C_CLR_ACTIVITY;  	//5C
	__I  uint32_t I2C_CLR_STOP_DET;  	//60
	__I  uint32_t I2C_CLR_START_DET;  //64
	__I  uint32_t I2C_CLR_GEN_CALL;  	//68
	__IO uint32_t I2C_ENABLE;  				//6C
	__I  uint32_t I2C_STATUS;  				//70
	__I  uint32_t I2C_TXFLR;  				//74
	__I  uint32_t I2C_RXFLR;  				//78
	__IO uint32_t I2C_SDA_HOLD;  			//7C
	__I  uint32_t I2C_TX_ABRT_SOURCE; //80
	__IO uint32_t I2C_SLV_DATA_NACK;  //84
			 uint32_t RESERVED3[3];                //88 ~ 90 Reserved
	__IO uint32_t I2C_SDA_SETUP;  		//94
	__IO uint32_t I2C_ACK_GEN_CALL;  	//98
	__I  uint32_t I2C_ENABLE_STATUS;  //9C
	__IO uint32_t I2C_FS_SPKLEN;  		//A0
	     uint32_t RESERVED4[1];                //A4 Reserved
	__I  uint32_t I2C_CLR_RST_DET;  	//A8
	      uint32_t RESERVED5[1];      
	__I  uint32_t I2C_CLR_MAT_SAR;     //B0
	
}	I2C_TypeDef;


typedef struct
{
	__IO uint32_t UARTx_RBR_THR_DLL;  //00
	__IO uint32_t UARTx_DLH_IER;  		//04
	__IO uint32_t UARTx_IIR_FCR;  		//08
	__IO uint32_t UARTx_LCR;  				//0C
	     uint32_t RESERVED1;  				          //10 Reserved
	__I  uint32_t UARTx_LSR;  				//14
	     uint32_t RESERVED0[22];          		  //18 ~ 6C Reserved
	__IO uint32_t UARTx_FAR;  				//70
	__I  uint32_t UARTx_TFR;  				//74
	__O  uint32_t UARTx_RFW;  				//78
	__I  uint32_t UARTx_USR;  				//7C
	__I  uint32_t UARTx_TFL;  				//80
	__I  uint32_t UARTx_RFL;  				//84
	
} UART_TypeDef;


typedef struct
{	
	__IO uint32_t TCSR0;  						//00
	__IO uint32_t TCMPR0;  						//04
	__IO uint32_t TISR0;  						//08
	__I  uint32_t TMR_CNT0;  					//0C
	     
} TMR0_TypeDef;

typedef struct
{
	__IO uint32_t TCSR1;  						//00
	__IO uint32_t TCMPR1;  						//04
	__IO uint32_t TISR1;  						//08
	__I  uint32_t TMR_CNT1;  					//0C	

} TMR1_TypeDef;


typedef struct{
	
	__IO uint32_t WTSCR;  			//00
	
} WDT_SMART_TypeDef;


typedef struct
{
	__IO uint32_t WTCR;  				//00
	__IO uint32_t WTCRALT;  		//04
	
} WDT_TypeDef;


typedef struct
{
	__IO uint32_t WWDTRLD;  		//00
	__IO uint32_t WWDTCR;  			//04
	__IO uint32_t WWDTSR;  			//08
	__IO uint32_t WWDTCVR;  		//0C
	
} WWDT_TypeDef;

typedef struct
{
	__IO uint32_t SYST_CSR;     //00
	__IO uint32_t SYST_RVR;  		//04
	__IO uint32_t SYST_CVR;  		//08
	
} SYST_TypeDef;



/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
//--- AHB
#define FLASH_BASE	             ((uint32_t)0x00000000)
#define SRAM_BASE	               ((uint32_t)0x20000000)
#define GCR_BASE	               ((uint32_t)0x50000000)
#define PWR_BASE	               ((uint32_t)0x50002000)
#define RST_BASE	               ((uint32_t)0x50002400)
#define CLK_BASE	               ((uint32_t)0x50002800)
#define INT_BASE	               ((uint32_t)0x50003000)
#define GPIOA_BASE	             ((uint32_t)0x50004000)
#define FMC_BASE	               ((uint32_t)0x5000C000)
#define RMC_BASE	               ((uint32_t)0x5000E000)
#define HDIV_BASE	               ((uint32_t)0x50014000)
#define CRC_BASE	               ((uint32_t)0x50024000)
//--- APB
#define WDT_SMART_BASE	         ((uint32_t)0x40004800)
#define WDT_BASE	               ((uint32_t)0x40004000)
#define WWDT_BASE	               ((uint32_t)0x40004400)
#define TMR0_BASE	               ((uint32_t)0x40010000)
#define TMR1_BASE	               ((uint32_t)0x40012000)
#define I2C0_BASE	               ((uint32_t)0x40020000)
#define UART0_BASE	             ((uint32_t)0x40050000)
#define AFE0_BASE	               ((uint32_t)0x400E0000)
#define AFE1_BASE	               ((uint32_t)0x400E4000)
//--- SCS
#define SCS1_BASE	               ((uint32_t)0xE000E010) //SYST_BA
#define SCS2_BASE	               ((uint32_t)0xE000E100) //NVIC_BA
#define SCS3_BASE	               ((uint32_t)0xE000ED00) //SCS_BA


/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define CLKMU							((CLKMU_TypeDef 				*) CLK_BASE	 			)
#define RSTMU							((RST_TypeDef 			    *) RST_BASE	 			)
#define GPIOA		          ((GPIOA_TypeDef 				*) GPIOA_BASE			)
#define TIMER0						((TMR0_TypeDef					*) TMR0_BASE			)
#define TIMER1						((TMR1_TypeDef					*) TMR1_BASE			)
#define	AFE0							((AFE_TypeDef						*) AFE0_BASE			)
#define	AFE1							((AFE_TypeDef						*) AFE1_BASE			)
#define CRC32							((CRC32_TypeDef					*) CRC_BASE				)		
#define HDIV 							((HDIV_TypeDef					*) HDIV_BASE			)
#define I2C0              ((I2C_TypeDef						*) I2C0_BASE			)
#define UART0							((UART_TypeDef					*) UART0_BASE			)
#define WDT_SMART         ((WDT_SMART_TypeDef			*) WDT_SMART_BASE )
#define WDT								((WDT_TypeDef						*) WDT_BASE				)
#define WWDT							((WWDT_TypeDef					*) WWDT_BASE			)
#define GCR  							((GCR_TypeDef				   	*) GCR_BASE		    )
#define FMC  				  		((FMC_TypeDef			  	  *) FMC_BASE		    )
#define SYST  						((SYST_TypeDef			  	*) SCS1_BASE		 	)
#define NVIC  						((NVIC_TypeDef			  	*) SCS2_BASE		 	)
#define SCS  						  ((SYS_CONTROL_TypeDef		*) SCS3_BASE		 	)
#define INT  						  ((INT_TypeDef			  	  *) INT_BASE		    )
#define PWRMU             ((PWR_TypeDef           *) PWR_BASE       )
#define RMC               ((SRAM_TypeDef          *) RMC_BASE       )
#define SYSTICK           ((SYS_TICK_TypeDef      *) SCS1_BASE      )
#define SCB               ((SYS_CONTROL_TypeDef   *) SCS3_BASE      )



#include "csa37fx60_conf.h"


/*******************************************************************************
 *                Hardware Abstraction Layer
 ******************************************************************************/
#if defined ( __CC_ARM   )
  #define __ASM            __asm                /*!< asm keyword for ARM Compiler          */
  #define __INLINE         __inline             /*!< inline keyword for ARM Compiler       */

#elif defined ( __ICCARM__ )
  #define __ASM           __asm                 /*!< asm keyword for IAR Compiler           */
  #define __INLINE        inline                /*!< inline keyword for IAR Compiler. Only avaiable in High optimization mode! */
  #define __NOP           __no_operation        /*!< no operation intrinsic in IAR Compiler */

#elif defined   (  __GNUC__  )
  #define __ASM            asm                  /*!< asm keyword for GNU Compiler          */
  #define __INLINE         inline               /*!< inline keyword for GNU Compiler       */

#endif

/* ###################  Compiler specific Intrinsics  ########################### */

#if defined ( __CC_ARM   ) /*------------------RealView Compiler -----------------*/
/* ARM armcc specific functions */

#define __enable_fault_irq                __enable_fiq
#define __disable_fault_irq               __disable_fiq

#define __NOP                             __nop
#define __WFI                             __wfi
#define __WFE                             __wfe
#define __SEV                             __sev
#define __ISB()                           __isb(0)
#define __DSB()                           __dsb(0)
#define __DMB()                           __dmb(0)
#define __REV                             __rev


#elif (defined (__ICCARM__)) /*------------------ ICC Compiler -------------------*/
/* IAR iccarm specific functions */

#define __enable_irq                              __enable_interrupt        /*!< global Interrupt enable */
#define __disable_irq                             __disable_interrupt       /*!< global Interrupt disable */

static __INLINE void __enable_fault_irq()         { __ASM ("cpsie f"); }
static __INLINE void __disable_fault_irq()        { __ASM ("cpsid f"); }

static __INLINE  void __WFI()                     { __ASM ("wfi"); }
static __INLINE  void __WFE()                     { __ASM ("wfe"); }
static __INLINE  void __SEV()                     { __ASM ("sev"); }


#elif (defined (__GNUC__)) /*------------------ GNU Compiler ---------------------*/
/* GNU gcc specific functions */

static __INLINE void __NOP()                      { __ASM volatile ("nop"); }
static __INLINE void __enable_irq()               { __ASM volatile ("cpsie i"); }
static __INLINE void __disable_irq()              { __ASM volatile ("cpsid i"); }

static __INLINE void __enable_fault_irq()         { __ASM volatile ("cpsie f"); }
static __INLINE void __disable_fault_irq()        { __ASM volatile ("cpsid f"); }

static __INLINE void __WFI()                      { __ASM volatile ("wfi"); }
static __INLINE void __WFE()                      { __ASM volatile ("wfe"); }
static __INLINE void __SEV()                      { __ASM volatile ("sev"); }
static __INLINE void __ISB(arg)                   { __ASM volatile ("isb"); }
static __INLINE void __DSB(arg)                   { __ASM volatile ("dsb"); }
static __INLINE void __DMB(arg)                   { __ASM volatile ("dmb"); }


#endif

#endif
