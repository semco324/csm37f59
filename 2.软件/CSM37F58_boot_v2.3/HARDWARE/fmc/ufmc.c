#include "ufmc.h"

//flash ��������ʼ��
void User_FMCInit(void)
{
    RCC_AHBPerophClOCKCmd(RCC_AHBPeriph_ISP , ENABLE);
    Reg_WRProtDisable(); //����д����
    
	  FMC->ISPCON |= (FMC_ISPEN);                         // Enable ISP function
	  FMC->ISPCON |= (FMC_CLK_HIRC);                      // ISP clock selet 24MHz
	  FMC->ISPCON |= (FMC_EXIT_STANDBY);					// Exit Flash standby mode
// 	FMC->ISPCON |= (FMC_LDUEN);							// LDROM enable
// 	FMC->ISPCON |= (FMC_CFGUEN);						// CFGROM enable
	  FMC->ISPCON |= (FMC_APUEN);							// APROM update enable
  //FMC->ICPCON |= (FMC_ICPEN);                         // Enable ICP functions ?
    
//  Reg_WRProtEnable();
}
