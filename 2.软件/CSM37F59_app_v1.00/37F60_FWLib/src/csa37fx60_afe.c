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
 
#include "csa37fx60_afe.h"
#include "csa37fx60_uart.h"
#include "csa37fx60_rcc.h"



//DAC 校准临时使用变量
uint16_t AFE0_DAC_AdjData[16];
uint16_t AFE1_DAC_AdjData[16];

//DAC 校准 ADC 采样值
uint16_t ADC_DataTemp1[16];
uint16_t ADC_DataFirst1[16];

/**
  * @brief  AFE初始化
  * @param  AFE_x : 选择AFE0 or AFE1
  * @param  AFE_InitStruct : AFE_x 初始化参数，参考afe.h
  * @retval None
  */
void AFE_Init(AFE_TypeDef *AFEx , AFE_InitTypeDef* AFE_InitStruct)
{
    uint32_t temp;
    uint32_t temp2;
    
    uint32_t pGACR;
    uint32_t aDCR;
    
    //PGACR
    temp = 0;
    
    temp = AFE_InitStruct->PGA1_Gain;
    temp <<= 4;
    temp |= AFE_InitStruct->PGA2_Gain;
    
    if(AFE_InitStruct->AFE_PGAEn == ENABLE)
    {
        temp |= BIT(22);
    }
    
    pGACR = temp;
    
    //ADCR
    temp = 0;
    
    temp2 = AFE_InitStruct->AFE_SampleTime;
    temp |= (temp2<<3);
    temp <<= 8;
    
    temp2 = AFE_InitStruct->CycleMode1_unVaildNum;
    if(temp2 > 15)
    {
        temp2 = 15;
    }
    temp |= (temp2<<4);
    
    if(AFE_InitStruct->Avg_Mode == Mid_Avg)
    {
        temp |= BIT(3);
    }
    
    temp2 = AFE_InitStruct->CycleMode_VaildNum;
    temp |= temp2;

    temp <<= 8;

    temp <<= 8;    
    
    temp2 = AFE_InitStruct->AFE_ScanMode;
    temp2 <<= 2 ;
    
    temp |= temp2;
    
    if( AFE_InitStruct->AFE_IntEn == ENABLE)
    {
        temp |= BIT(1);
    }
    
    aDCR = temp;
    
    //设置VS电压
    PWRMU->VS_CR = BIT(7) | AFE_InitStruct->VS_Sel; //
    
    //-----------------------------------------------------------
    
    AFEx->PGACR = pGACR;
   
    AFEx->ADCR = aDCR;
    
    AFEx->DACR |= BIT(28) ; // VS /2
    //设置要采样的通道

    AFEx->ADCHER = AFE_InitStruct->AFEx_SampleChannel;
    
    
}


/**
  * @brief  AFEx启动AD转换
  * @param  AFE_x : 选择AFE0 or AFE1
  * @retval None
  */
void AFEx_StartADScan(AFE_TypeDef *AFEx)
{
    uint16_t afex_Channel = AFEx->ADCHER & 0xffff;
    
    if(afex_Channel == 0) //没有通道使能直接返回
    {
        return;
    }
    
    AFEx->ADCR |= BIT(11); 
}

/**
  * @brief  AFEx检查AD转换是否完成
  * @param  AFE_x : 选择AFE0 or AFE1
  * @retval 1:完成  0:未完成
  */
uint8_t AFEx_CheckADFinish(AFE_TypeDef *AFEx)
{
    uint8_t temp = 0;
    
    uint16_t afex_Channel = AFEx->ADCHER & 0xffff;
    
    if(afex_Channel == 0) //没有通道使能直接返回
    {
        temp = 2;
    }
    
    if(AFEx->ADSR & BIT(0) )
    {
        temp = 1;
        
        AFEx->ADSR |= BIT(0);//清标记
    }
    
    return temp;
}
/**
  * @brief  AFEx打开 AD 电源
  * @param  AFE_x : 选择AFE0 or AFE1
  * @retval None
  */
void AFEx_ADPowerOpen(AFE_TypeDef *AFEx)
{
    AFEx->ADCR |= BIT(0); 
}
/**
  * @brief  AFEx关闭 AD 电源
  * @param  AFE_x : 选择AFE0 or AFE1
  * @retval None
  */
void AFEx_ADPowerClose(AFE_TypeDef *AFEx)
{
    AFEx->ADCR &= ~BIT(0); 
}

/**
  * @brief  AFE0 读取指定通道的ADC采样数据
  * @param  AFE0_Channelx : 选择通道序号
  * @param  dat : ADC数据 (指针)
  * @retval 0: 数据无效   1:数据有效
  */
uint8_t AFEx_ReadSampleData(AFE_TypeDef *AFEx, uint8_t AFEx_Channelx, uint16_t *dat)
{
    uint32_t temp = 0;
    
    uint32_t *base = (uint32_t *)&(AFEx->ADDR0) ;
    
    temp = base[AFEx_Channelx];
    
    *dat = temp & 0x0fff;
    
    if(temp & BIT(17)) 
    {
        return 1; //数据有效
    }
    
    return 0; //数据无效
}


/**
  * @brief  获取ADC采样值，DAC校准时用
  * @param  AFE_x:选择要获取数据的AFEx
  * @retval None
  */
void Get_ADCData(AFE_TypeDef *AFEx, uint16_t *ADC_Data)
{
    uint8_t i;
//    uint8_t flag;
    
    AFEx_StartADScan(AFEx); //启动转换
    
    while(AFEx_CheckADFinish(AFEx)==0) //等待转换完成
    {

    }

    for(i=0;i<16;i++)
    {
        AFEx_ReadSampleData(AFEx, i, &ADC_Data[i]);    
    }  
}
/**
  * @brief  设置DAC校准值，DAC校准时用
  * @param  AFE_x:选择要设置的AFE
  * @retval None
  */
void AFEx_SetDACData(AFE_TypeDef *AFEx, uint16_t *dac_AdjData)
{
    uint8_t i;
    uint32_t *base = (uint32_t *)&(AFEx->DADAT0) ;
    
    for(i=0;i<16;i++)
    {
        *(base + i) = dac_AdjData[i];
    }
}
/**
  * @brief  求两个16位变量的差值绝对值
  * @param  None
  * @retval None
  */
uint16_t AbsData(uint16_t data1,uint16_t data2)
{
    uint16_t temp;
    
    temp = data2 - data1;
    
    if(data1 > data2)
    {
        temp = data1- data2;
    }     
    
    return temp;
}

/**
  * @brief  DAC校准
  * @param  AFE_x:选择要校准的AFE
  * @retval 
  */
void AFEx_DAC_Adjust(AFE_TypeDef *AFEx)
{
    uint8_t i,j;
    
//    uint16_t *DAC_AdjData;
    
    uint16_t DiffDataMin[16]; //保存校准过程中，各个通道采样到距2048最小的采样值
    uint16_t DAC_AdjTemp[16]; //保存校准过程中，各个通道采样到距2048最小的校准参数值
    uint16_t DAC_AdjData[16];
    
    uint16_t afex_Channel; //保存需要采样及处理的通道
    
    uint8_t flag;

    afex_Channel = AFEx->ADCHER & 0xffff;
    
    if(afex_Channel == 0) //没有通道使能直接返回
    {
        return;
    }
    
    AFEx->DACR |= BIT(31);//DAC 使能      
    
    AFEx_ADPowerOpen(AFEx);    
    
    for(i=0;i<16;i++)
    {
        DiffDataMin[i] = 0xffff;
        DAC_AdjData[i] = 0;
    }
    
    //获取第一次数据
    AFEx_SetDACData(AFEx,DAC_AdjData); //设置DAC
    Get_ADCData(AFEx,ADC_DataTemp1);
    
    //通过二分法查找距2048最小值，
    
    //第一次采样，确定查找方向
    for(i=0;i<16;i++)
    {
        if(afex_Channel & BIT(i)) //使能的通道才处理
        {
            ADC_DataFirst1[i] = ADC_DataTemp1[i];
            
            if((ADC_DataTemp1[i] & BIT(11)))
            {
                DAC_AdjData[i] = BIT(10);
            }
            else
            {
                DAC_AdjData[i] = BIT(11) | BIT(10);
            }
        }
    }

    for(i=1;i<12;i++)
    {   
        AFEx_SetDACData(AFEx,DAC_AdjData); //设置DAC
        
        Get_ADCData(AFEx,ADC_DataTemp1); //获取AD值
        
        for(j=0;j<16;j++)
        {
            if(afex_Channel & BIT(j)) //使能的通道才处理
            {
                if(AbsData(ADC_DataTemp1[j],2048) < DiffDataMin[j]) //记录查找的到距2048最小值
                {
                    DiffDataMin[j] = AbsData(ADC_DataTemp1[j],2048);    
                    
                    DAC_AdjTemp[j] = DAC_AdjData[j];
                }
                
                if(i==11) //最后一次时，确定DAC校准值
                {
                    DAC_AdjData[j] = DAC_AdjTemp[j];

                    AFEx_SetDACData(AFEx,DAC_AdjData); //设置DAC
                }
                else
                {
                    flag = 0;
                    
                    //确定下一轮采样时的DAC校准值
                    if((ADC_DataTemp1[j] & BIT(11)) != (ADC_DataFirst1[j] & BIT(11)))
                    {
                        DAC_AdjData[j] &= ~BIT(11-i);
                        
                        flag = 1;
                    }
                    
                    DAC_AdjData[j] |= BIT(10-i);
                    
                    //跳过有问题的DAC 0xD00~0XD80 值
                    if((DAC_AdjData[j]>(0xCFF)) && (DAC_AdjData[j]<(0xD81)))
                    {
                        if(flag)
                        {
                            DAC_AdjData[j] = 0xD80 + 1;
                        }
                        else
                        {
                            DAC_AdjData[j] = 0XD00 -1;
                        }
                    }
                    
                    //跳过有问题的DAC 0x500~0x580 值
                    if((DAC_AdjData[j]>(0x4FF)) && (DAC_AdjData[j]<(0x581)))
                    {
                        if(flag)
                        {
                            DAC_AdjData[j] = 0x580 + 1;
                        }
                        else
                        {
                            DAC_AdjData[j] = 0X500 -1;
                        }
                    }
                }
            }
        }        
    }
}


#if FAST_DAC_ADJUST

//-------------------------------------------------------------
//                                    1                 32           64               64                              
const uint8_t PGA1_Data[5] = {AFE_PGA1_Gain_1,AFE_PGA1_Gain_32,AFE_PGA1_Gain_64,AFE_PGA1_Gain_64};
//                                    1                  1            8                8
const uint8_t PGA2_Data[5] = {AFE_PGA2_Gain_1,AFE_PGA2_Gain_1,AFE_PGA2_Gain_8,AFE_PGA2_Gain_8};

const uint16_t PGA_Factor[4] = {1,32,512,512};

uint16_t ADC_DataTempTest[16];
uint16_t DAC_DataTempTest[16];

extern uint16_t AFE0_SampleData[16];
extern uint16_t AFE1_SampleData[16];

void Sample_InitFast(AFE_TypeDef *AFEx, uint8_t pga_num)
{
    
    AFE_InitTypeDef AFE_InitStruct;
    
    //AFE配置初始化，失调校准采样参数
    AFE_InitStruct.AFE_IntEn = DISABLE; //关中断
    AFE_InitStruct.AFE_PGAEn = ENABLE;  //打开PGA
    AFE_InitStruct.PGA1_Gain = PGA1_Data[pga_num]; //PGA 1 增益
    AFE_InitStruct.PGA2_Gain = PGA2_Data[pga_num];  // PGA 2 增益
    AFE_InitStruct.AFE_SampleTime = Time_ADCClock_8; // 

    AFE_InitStruct.Avg_Mode = Mid_Avg; // 采样结果计算方式，去掉最大最小值后平均
    AFE_InitStruct.CycleMode1_unVaildNum = 4; //无效数据采样次数
    AFE_InitStruct.CycleMode_VaildNum = Vaild_Num_8; //有效数据采样次数
    AFE_InitStruct.AFE_ScanMode = AFE_FiniteCycleMode1   ;//采样方式 有限周期模式1
    
    AFE_InitStruct.AFEx_SampleChannel = AFEx->ADCHER; //afe1 通道配置
    
    AFE_InitStruct.VS_Sel = VS_30; //vs 电压 3.0v
    
    AFE_Init(AFEx , &AFE_InitStruct); //初始化AFEx
    
    //初始化后需重新打开电源
    AFEx_ADPowerOpen(AFEx); //打开AFE0电源
    
}

uint16_t ADC_DataTest1[16];
uint16_t ADC_DataTest2[16];

void AFEx_DAC_AdjustFast(AFE_TypeDef *AFEx)
{
    uint8_t i,j;
    uint16_t temp;
    uint8_t flag; //0 大于2048 1小于2048
    
//    uint8_t flag_Dir[16];//DAC 加减方向记录 0 加 1减
    
    uint16_t dac_diff; //保存dac需要加减的变化量
    
    uint8_t count = 0;
    
    uint16_t DAC_AdjData[16];
    uint16_t DAC_AdjDataBak[16];
    
    uint16_t ADC_SampleData[16];
    uint16_t ADC_SampleDataBak[16];
    
    uint16_t afex_Channel = AFEx->ADCHER & 0xffff; //获取采样通道

    AFEx->DACR |= BIT(31);//DAC 使能     

    for(i=0;i<6;i++)
    {

        if(i<3)
        {
            Sample_InitFast(AFEx,i);   //设置采样参数            
        }

        Get_ADCData(AFEx, ADC_SampleData); //获取ad值
        
        for(j=0;j<16;j++)
        {
            if(i == 0) //第一次初始化dac值
            {
                DAC_AdjData[j] = 0;
            }
            
            if(afex_Channel & BIT(j)) //使能的通道才处理
            {
                if(i==5)
                {
                    if(AbsData(2048,ADC_SampleData[j]) > AbsData(2048,ADC_SampleDataBak[j]))
                    {
                        DAC_AdjData[j] = DAC_AdjDataBak[j];
                        
                    }

                    //debug
                    ADC_DataTest1[j] = ADC_SampleData[j];
                    ADC_DataTest2[j] = ADC_SampleDataBak[j];
                    
                    continue;
                }
                
                ADC_SampleDataBak[j] = ADC_SampleData[j]; //采样值备份
                DAC_AdjDataBak[j] = DAC_AdjData[j]; //DAC值备份
                
                flag = 0;
                if(ADC_SampleData[j] < 2048)
                {
                    flag = 1;
                }

                temp = AbsData(2048,ADC_SampleData[j]);
                
//                    dac_diff = (temp*6.912)/PGA_Factor[i] + 0.5;
                dac_diff = (((uint32_t)temp*6912)/PGA_Factor[i]+500)/1000; //计算dac调整量

                if(i==4) //第5次采样固定偏移1，与上一次比较找出最接近2048的DAC值
                {
                    dac_diff = 1;
                }
                

                if(flag==0)
                {
                    if(DAC_AdjData[j] & 0x800) //正数
                    {
                        DAC_AdjData[j] -= dac_diff;  
                        
                        if((DAC_AdjData[j]<2048) && ((DAC_AdjData[j] + dac_diff)>2047))
                        {
                            DAC_AdjData[j] = 2048 - DAC_AdjData[j] -1;
                            
                        }
                    }
                    else
                    {
                        DAC_AdjData[j] += dac_diff;
                        
                        if(DAC_AdjData[j] > 2047)
                        {
                            DAC_AdjData[j] = 2047;
                        }
                        
                    }
                }
                else
                {
                    if(DAC_AdjData[j] & 0x800) //正数
                    {
                        DAC_AdjData[j] += dac_diff;
                        
                        if(DAC_AdjData[j]>4095)
                        {
                            DAC_AdjData[j] = 4095;
                        } 
                        
                    }
                    else
                    {

                        if(DAC_AdjData[j] >= dac_diff)
                        {
                            DAC_AdjData[j] -= dac_diff;
                        }
                        else
                        {
                            DAC_AdjData[j] = 2047 + dac_diff - DAC_AdjData[j];
                        }
                        
                    }
                }
                
                //异常DAC段跳过
                if(((DAC_AdjData[j]>(0xCFF)) && (DAC_AdjData[j]<(0xD81))) 
                    || ((DAC_AdjData[j]>(0x4ff)) && (DAC_AdjData[j]<(0x581))) )
                {
                    if(i==0)
                    {
                        DAC_AdjData[j] += 129;
                    }
                    else
                    {
                        if(flag)
                        {
                            DAC_AdjData[j] += 129;
                        }
                        else
                        {
                            DAC_AdjData[j] -= 129;
                        }                    
                    }

                }
                
                
            }

        }
        
        AFEx_SetDACData(AFEx, DAC_AdjData);//设置DAC
    } 
    
}

#endif

