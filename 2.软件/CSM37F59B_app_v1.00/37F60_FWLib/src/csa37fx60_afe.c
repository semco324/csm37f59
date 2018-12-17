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



//DAC У׼��ʱʹ�ñ���
uint16_t AFE0_DAC_AdjData[16];
uint16_t AFE1_DAC_AdjData[16];

//DAC У׼ ADC ����ֵ
uint16_t ADC_DataTemp1[16];
uint16_t ADC_DataFirst1[16];

/**
  * @brief  AFE��ʼ��
  * @param  AFE_x : ѡ��AFE0 or AFE1
  * @param  AFE_InitStruct : AFE_x ��ʼ���������ο�afe.h
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
    
    //����VS��ѹ
    PWRMU->VS_CR = BIT(7) | AFE_InitStruct->VS_Sel; //
    
    //-----------------------------------------------------------
    
    AFEx->PGACR = pGACR;
   
    AFEx->ADCR = aDCR;
    
    AFEx->DACR |= BIT(28) ; // VS /2
    //����Ҫ������ͨ��

    AFEx->ADCHER = AFE_InitStruct->AFEx_SampleChannel;
    
    
}


/**
  * @brief  AFEx����ADת��
  * @param  AFE_x : ѡ��AFE0 or AFE1
  * @retval None
  */
void AFEx_StartADScan(AFE_TypeDef *AFEx)
{
    uint16_t afex_Channel = AFEx->ADCHER & 0xffff;
    
    if(afex_Channel == 0) //û��ͨ��ʹ��ֱ�ӷ���
    {
        return;
    }
    
    AFEx->ADCR |= BIT(11); 
}

/**
  * @brief  AFEx���ADת���Ƿ����
  * @param  AFE_x : ѡ��AFE0 or AFE1
  * @retval 1:���  0:δ���
  */
uint8_t AFEx_CheckADFinish(AFE_TypeDef *AFEx)
{
    uint8_t temp = 0;
    
    uint16_t afex_Channel = AFEx->ADCHER & 0xffff;
    
    if(afex_Channel == 0) //û��ͨ��ʹ��ֱ�ӷ���
    {
        temp = 2;
    }
    
    if(AFEx->ADSR & BIT(0) )
    {
        temp = 1;
        
        AFEx->ADSR |= BIT(0);//����
    }
    
    return temp;
}
/**
  * @brief  AFEx�� AD ��Դ
  * @param  AFE_x : ѡ��AFE0 or AFE1
  * @retval None
  */
void AFEx_ADPowerOpen(AFE_TypeDef *AFEx)
{
    AFEx->ADCR |= BIT(0); 
}
/**
  * @brief  AFEx�ر� AD ��Դ
  * @param  AFE_x : ѡ��AFE0 or AFE1
  * @retval None
  */
void AFEx_ADPowerClose(AFE_TypeDef *AFEx)
{
    AFEx->ADCR &= ~BIT(0); 
}

/**
  * @brief  AFE0 ��ȡָ��ͨ����ADC��������
  * @param  AFE0_Channelx : ѡ��ͨ�����
  * @param  dat : ADC���� (ָ��)
  * @retval 0: ������Ч   1:������Ч
  */
uint8_t AFEx_ReadSampleData(AFE_TypeDef *AFEx, uint8_t AFEx_Channelx, uint16_t *dat)
{
    uint32_t temp = 0;
    
    uint32_t *base = (uint32_t *)&(AFEx->ADDR0) ;
    
    temp = base[AFEx_Channelx];
    
    *dat = temp & 0x0fff;
    
    if(temp & BIT(17)) 
    {
        return 1; //������Ч
    }
    
    return 0; //������Ч
}


/**
  * @brief  ��ȡADC����ֵ��DACУ׼ʱ��
  * @param  AFE_x:ѡ��Ҫ��ȡ���ݵ�AFEx
  * @retval None
  */
void Get_ADCData(AFE_TypeDef *AFEx, uint16_t *ADC_Data)
{
    uint8_t i;
//    uint8_t flag;
    
    AFEx_StartADScan(AFEx); //����ת��
    
    while(AFEx_CheckADFinish(AFEx)==0) //�ȴ�ת�����
    {

    }

    for(i=0;i<16;i++)
    {
        AFEx_ReadSampleData(AFEx, i, &ADC_Data[i]);    
    }  
}
/**
  * @brief  ����DACУ׼ֵ��DACУ׼ʱ��
  * @param  AFE_x:ѡ��Ҫ���õ�AFE
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
  * @brief  ������16λ�����Ĳ�ֵ����ֵ
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
  * @brief  DACУ׼
  * @param  AFE_x:ѡ��ҪУ׼��AFE
  * @retval 
  */
void AFEx_DAC_Adjust(AFE_TypeDef *AFEx)
{
    uint8_t i,j;
    
//    uint16_t *DAC_AdjData;
    
    uint16_t DiffDataMin[16]; //����У׼�����У�����ͨ����������2048��С�Ĳ���ֵ
    uint16_t DAC_AdjTemp[16]; //����У׼�����У�����ͨ����������2048��С��У׼����ֵ
    uint16_t DAC_AdjData[16];
    
    uint16_t afex_Channel; //������Ҫ�����������ͨ��
    
    uint8_t flag;

    afex_Channel = AFEx->ADCHER & 0xffff;
    
    if(afex_Channel == 0) //û��ͨ��ʹ��ֱ�ӷ���
    {
        return;
    }
    
    AFEx->DACR |= BIT(31);//DAC ʹ��      
    
    AFEx_ADPowerOpen(AFEx);    
    
    for(i=0;i<16;i++)
    {
        DiffDataMin[i] = 0xffff;
        DAC_AdjData[i] = 0;
    }
    
    //��ȡ��һ������
    AFEx_SetDACData(AFEx,DAC_AdjData); //����DAC
    Get_ADCData(AFEx,ADC_DataTemp1);
    
    //ͨ�����ַ����Ҿ�2048��Сֵ��
    
    //��һ�β�����ȷ�����ҷ���
    for(i=0;i<16;i++)
    {
        if(afex_Channel & BIT(i)) //ʹ�ܵ�ͨ���Ŵ���
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
        AFEx_SetDACData(AFEx,DAC_AdjData); //����DAC
        
        Get_ADCData(AFEx,ADC_DataTemp1); //��ȡADֵ
        
        for(j=0;j<16;j++)
        {
            if(afex_Channel & BIT(j)) //ʹ�ܵ�ͨ���Ŵ���
            {
                if(AbsData(ADC_DataTemp1[j],2048) < DiffDataMin[j]) //��¼���ҵĵ���2048��Сֵ
                {
                    DiffDataMin[j] = AbsData(ADC_DataTemp1[j],2048);    
                    
                    DAC_AdjTemp[j] = DAC_AdjData[j];
                }
                
                if(i==11) //���һ��ʱ��ȷ��DACУ׼ֵ
                {
                    DAC_AdjData[j] = DAC_AdjTemp[j];

                    AFEx_SetDACData(AFEx,DAC_AdjData); //����DAC
                }
                else
                {
                    flag = 0;
                    
                    //ȷ����һ�ֲ���ʱ��DACУ׼ֵ
                    if((ADC_DataTemp1[j] & BIT(11)) != (ADC_DataFirst1[j] & BIT(11)))
                    {
                        DAC_AdjData[j] &= ~BIT(11-i);
                        
                        flag = 1;
                    }
                    
                    DAC_AdjData[j] |= BIT(10-i);
                    
                    //�����������DAC 0xD00~0XD80 ֵ
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
                    
                    //�����������DAC 0x500~0x580 ֵ
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
    
    //AFE���ó�ʼ����ʧ��У׼��������
    AFE_InitStruct.AFE_IntEn = DISABLE; //���ж�
    AFE_InitStruct.AFE_PGAEn = ENABLE;  //��PGA
    AFE_InitStruct.PGA1_Gain = PGA1_Data[pga_num]; //PGA 1 ����
    AFE_InitStruct.PGA2_Gain = PGA2_Data[pga_num];  // PGA 2 ����
    AFE_InitStruct.AFE_SampleTime = Time_ADCClock_8; // 

    AFE_InitStruct.Avg_Mode = Mid_Avg; // ����������㷽ʽ��ȥ�������Сֵ��ƽ��
    AFE_InitStruct.CycleMode1_unVaildNum = 4; //��Ч���ݲ�������
    AFE_InitStruct.CycleMode_VaildNum = Vaild_Num_8; //��Ч���ݲ�������
    AFE_InitStruct.AFE_ScanMode = AFE_FiniteCycleMode1   ;//������ʽ ��������ģʽ1
    
    AFE_InitStruct.AFEx_SampleChannel = AFEx->ADCHER; //afe1 ͨ������
    
    AFE_InitStruct.VS_Sel = VS_30; //vs ��ѹ 3.0v
    
    AFE_Init(AFEx , &AFE_InitStruct); //��ʼ��AFEx
    
    //��ʼ���������´򿪵�Դ
    AFEx_ADPowerOpen(AFEx); //��AFE0��Դ
    
}

uint16_t ADC_DataTest1[16];
uint16_t ADC_DataTest2[16];

void AFEx_DAC_AdjustFast(AFE_TypeDef *AFEx)
{
    uint8_t i,j;
    uint16_t temp;
    uint8_t flag; //0 ����2048 1С��2048
    
//    uint8_t flag_Dir[16];//DAC �Ӽ������¼ 0 �� 1��
    
    uint16_t dac_diff; //����dac��Ҫ�Ӽ��ı仯��
    
    uint8_t count = 0;
    
    uint16_t DAC_AdjData[16];
    uint16_t DAC_AdjDataBak[16];
    
    uint16_t ADC_SampleData[16];
    uint16_t ADC_SampleDataBak[16];
    
    uint16_t afex_Channel = AFEx->ADCHER & 0xffff; //��ȡ����ͨ��

    AFEx->DACR |= BIT(31);//DAC ʹ��     

    for(i=0;i<6;i++)
    {

        if(i<3)
        {
            Sample_InitFast(AFEx,i);   //���ò�������            
        }

        Get_ADCData(AFEx, ADC_SampleData); //��ȡadֵ
        
        for(j=0;j<16;j++)
        {
            if(i == 0) //��һ�γ�ʼ��dacֵ
            {
                DAC_AdjData[j] = 0;
            }
            
            if(afex_Channel & BIT(j)) //ʹ�ܵ�ͨ���Ŵ���
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
                
                ADC_SampleDataBak[j] = ADC_SampleData[j]; //����ֵ����
                DAC_AdjDataBak[j] = DAC_AdjData[j]; //DACֵ����
                
                flag = 0;
                if(ADC_SampleData[j] < 2048)
                {
                    flag = 1;
                }

                temp = AbsData(2048,ADC_SampleData[j]);
                
//                    dac_diff = (temp*6.912)/PGA_Factor[i] + 0.5;
                dac_diff = (((uint32_t)temp*6912)/PGA_Factor[i]+500)/1000; //����dac������

                if(i==4) //��5�β����̶�ƫ��1������һ�αȽ��ҳ���ӽ�2048��DACֵ
                {
                    dac_diff = 1;
                }
                

                if(flag==0)
                {
                    if(DAC_AdjData[j] & 0x800) //����
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
                    if(DAC_AdjData[j] & 0x800) //����
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
                
                //�쳣DAC������
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
        
        AFEx_SetDACData(AFEx, DAC_AdjData);//����DAC
    } 
    
}

#endif

