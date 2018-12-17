;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2015 SHENZHEN CHIPSEA TECHNOLOGIES CO.,LTD. All rights reserved.                           */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

                 GBLL    SEMIHOSTED
SEMIHOSTED       SETL    {FALSE}

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack        0
                DCD     Reset_Handler             ; Reset Handler       4
                DCD     NMI_Handler               ; NMI Handler         8
                DCD     HardFault_Handler         ; Hard Fault Handler  C
                DCD     0                         ; Reserved            10
                DCD     0                         ; Reserved            14
                DCD     0                         ; Reserved            18
                DCD     0                         ; Reserved            1C
                DCD     0                         ; Reserved            20
                DCD     0                         ; Reserved            24
                DCD     0                         ; Reserved            28
                DCD     SVC_Handler               ; SVCall Handler      2C
                DCD     0                         ; Reserved            30
                DCD     0                         ; Reserved            34
                DCD     PendSV_Handler            ; PendSV Handler      38
                DCD     SysTick_Handler           ; SysTick Handler     3C

                ; External Interrupts : maximum of 32 External Interrupts are possible
                DCD     BOD_IRQHandler            ; 40
                DCD     WDT_IRQHandler            ; 44
                DCD     TMR0_IRQHandler           ; 48
                DCD     TMR1_IRQHandler           ; 4c
                DCD     UART0_IRQHandler          ; 50
                DCD     I2C0_IRQHandler           ; 54
                DCD     AFE0_IRQHandler           ; 58
                DCD     AFE1_IRQHandler 
                DCD     PD_WU_IRQHandler 
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler  
                DCD     Default_IRQHandler  
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler
                DCD     Default_IRQHandler 
                DCD     Default_IRQHandler
                DCD     Default_IRQHandler
                DCD     Default_IRQHandler  
                DCD     Default_IRQHandler  
                 
    
                AREA    |.text|, CODE, READONLY
          
; Reset Handler 
;ENTRY
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP
                
                
; Dummy Exception Handlers (infinite loops which can be modified)                
                
NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  TMR0_IRQHandler           [WEAK]
                EXPORT  TMR1_IRQHandler           [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  AFE0_IRQHandler           [WEAK]
                EXPORT  AFE1_IRQHandler           [WEAK]
                EXPORT  PD_WU_IRQHandler          [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
				EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
                EXPORT  Default_IRQHandler        [WEAK]
               
BOD_IRQHandler
WDT_IRQHandler
TMR0_IRQHandler
TMR1_IRQHandler
UART0_IRQHandler
I2C0_IRQHandler
AFE0_IRQHandler
AFE1_IRQHandler
PD_WU_IRQHandler
Default_IRQHandler


                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

    
                END
