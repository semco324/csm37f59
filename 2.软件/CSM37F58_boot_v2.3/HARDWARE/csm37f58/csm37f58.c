#include "csm37f58.h"

uint32_t BIA_FLAG=0;   //关于BIA的标志位见FunctionBIAFlag

//判断bit0~bit5有多少个1
uint8_t howmany(uint8_t data)
{
	uint8_t i,j=0;
	for(i=0;i<6;i++)
	{
	  if(((data>>i)&0x01))
			j++;
	}
   return j;

}
