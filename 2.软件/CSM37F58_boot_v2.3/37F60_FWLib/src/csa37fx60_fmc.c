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
 
#include "csa37fx60_fmc.h"
#include "csa37fx60_system.h"

/**
  * @brief flash控制器初始化 
  * @param None 
  * @retval None
  */
void FMC_Init(FMC_InitTypeDef* FMC_InitStruct)
{   
    Reg_WRProtDisable(); 								//unlock write-protect
    
    FMC->ISPCON = 0;
    
    FMC->ISPCON |= (FMC_ISPEN);                         // Enable ISP function
    
    FMC->ISPCON |= (FMC_InitStruct->ISP_Freq << 8);     //setting ISP clock
    
    if(FMC_InitStruct->Enter_DeepStandby == DISABLE)    //setting DeepStandby status
    {
        FMC->ISPCON |= BIT(7);
    }
    
    if(FMC_InitStruct->LDROM_Update == ENABLE)          //setting Is it allowed r-w LDROM
    {
        FMC->ISPCON |= BIT(5);
    }
    
    if(FMC_InitStruct->CFG_Update == ENABLE)            //setting Is it allowed r-w CFG reg
    {
        FMC->ISPCON |= BIT(4);
    }
    
    if(FMC_InitStruct->APROM_Update == ENABLE)          //setting Is it allowed r-w APROM
    {
        FMC->ISPCON |= BIT(3);
    }

}

/**
  * @brief  Erase one page (512 byte)
  * @param  adr：start addr
  * @retval 0 - OK,  1 - Failed
  */
uint8_t FMC_ErasePage(uint32_t adr)
{
    uint32_t offs;                                   	// Flash Offset

    Reg_WRProtDisable(); 								//unlock write-protect
    //def FLASH_APROM
    offs = 0x00000000;

    while (FMC->ISPTRG & FMC_ISPGO);                      // Wait until command is finished

    FMC->ISPSTA |= FMC_ISPFF;                             // Reset Error Flags

    FMC->ISPCMD = FMC_PAGE_ERASE;                         // Prepare Command
    FMC->ISPADR = ((adr + offs) & ~0x00000003);           // Prepare Address
    FMC->ISPTRG = FMC_ISPGO;                              // Exacute Command
    __nop();
    //__isb(0);

    while (FMC->ISPTRG & FMC_ISPGO) // Wait until command is finished
    {                     
        /* reload Watdchdog */                              // Reload IWDG
    }

    if (FMC->ISPSTA &  FMC_ISPFF)                        // Check for Error
    {
        FMC->ISPSTA |= FMC_ISPFF;                         // Reset Error Flags
        return (1);                                       // Failed
    }

    return (0);                                           // Done
}

/**
  * @brief  Erase more page
  * @param  adr: start addr
  * @param  num: block number
  * @retval 0 - OK,  1 - Failed
  */
uint8_t FMC_EraseMorePage(uint32_t adr, uint8_t num)
{
    uint8_t i;
    uint8_t ret = 0;
    
    for(i=0;i<num;i++)
    {
        ret = FMC_ErasePage((adr + i*0x200));    
    }

    return(ret);
}

/**
  * @brief  Write data
  * @param  adr: start addr
  * @param  sz: data number
  * @param  buf: data source
  * @retval 0 - OK,  1 - Failed
  */
uint8_t FMC_WritePage (uint32_t adr, uint16_t sz, uint8_t *buf) 
{
    uint32_t offs;                                   		// Flash Offset

    Reg_WRProtDisable(); 									//unlock write-protect
    //def FLASH_APROM
    offs = 0x00000000;

    sz = (sz + 3) & ~3;                                   // Adjust size for Words

    while(FMC->ISPTRG & FMC_ISPGO);                      // Wait until command is finished

    FMC->ISPSTA |= FMC_ISPFF;                             // Reset Error Flags

    while(sz) 
    {
        FMC->ISPCMD = FMC_PROGRAM;                          // Prepare Command
        FMC->ISPADR = ((adr + offs) & ~0x00000003);         // Prepare Address
        FMC->ISPDAT = *((uint32_t *)buf);                        // Prepare Data
        FMC->ISPTRG = FMC_ISPGO;                            // Execute Command
        __nop();
        //__isb(0);

        while(FMC->ISPTRG & FMC_ISPGO) // Wait until command is finished
        {                   
            /* reload Watdchdog */                            // Reload IWDG
        }

        if (FMC->ISPSTA &  FMC_ISPFF) // Check for Error
        {                     
            FMC->ISPSTA |= FMC_ISPFF;                       // Reset Error Flags
            return (1);                                     // Failed
        }

        adr += 4;                                           // Go to next Word
        buf += 4;
        sz  -= 4;
    }

    return (0);                                           // Done
}

/**
  * @brief  读数据
  * @param  adr: 起始地址
  * @param  sz: 数据长度
  * @param  buf: 数据指针
  * @retval (adr+sz) - OK, Failed Address
  */
uint32_t FMC_ReadPage (uint32_t adr, uint16_t sz, uint8_t *buf)
{
    uint32_t offs;                                   // Flash Offset

    uint16_t i;

    uint32_t *temp = (uint32_t *)buf;

    
    Reg_WRProtDisable(); //解锁写保护
    //def FLASH_APROM

    offs = 0x00000000;


    sz = (sz + 3) & ~3;                                   // Adjust size for Words

    while (FMC->ISPTRG & FMC_ISPGO);                      // Wait until command is finished

    FMC->ISPSTA |= FMC_ISPFF;                             // Reset Error Flags

    i = 0;
    while (sz) 
    {
        FMC->ISPCMD = FMC_READ;                             // set command
        FMC->ISPADR = ((adr + offs) & ~0x00000003);         // Prepare Address
        FMC->ISPDAT = 0x00000000;                           // Prepare Data
        FMC->ISPTRG = FMC_ISPGO;                            // Exacute Command
        __nop();
        //__isb(0);

        while (FMC->ISPTRG & FMC_ISPGO) 
        {                   // Wait until command is finished
        /* reload Watdchdog */                              // Reload IWDG
        }

        if (FMC->ISPSTA &  FMC_ISPFF) 
        {                                                   // Check for Error
            FMC->ISPSTA |= FMC_ISPFF;                       // Reset Error Flags
            return (adr);                                   // Failed
        }
        
        temp[i++] = FMC->ISPDAT;

        adr += 4;                                           // Go to next Word
        buf += 4;
        sz  -= 4;
    }

    return (adr);
}

/**
  * @brief  Switch the ROM to run the program
  * @param  ROM_Mode: Choose to switch type of ROM :APROM or LDROM
  * @retval None
  */
void FMC_SwitchROM(FMC_ROM_Mode_TypeDef ROM_Mode)
{
    Reg_WRProtDisable(); 			//unlock write-protect
    
    //Reset control bits
    FMC->ISPCON &= ~BIT(2);
    FMC->ISPCON &= ~BIT(1);
    
    //Setting control bits
    FMC->ISPCON |= (ROM_Mode<<1);
    
    //reset MCU
    System_Reset(MCU_Reset);
}
