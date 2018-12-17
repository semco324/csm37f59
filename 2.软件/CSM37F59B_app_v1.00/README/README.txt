2017.11.20 v1.0
2017.12.9  v2.0 修补时间问题 
2017.12.20 v3.0 修复算法调用问题,区分普通和运动模式 
2018.1.24  v3.1 修复M_PART部分用户体验问题csa37fx60_it.c   case (uint32_t)&EquMent->M_PART:
2018.1.24  v3.2 修复主机发送37 5A XX 05情况 ,把user_addr指向无效地址
2018.1.24  v3.3 修改算法CS_BIA_V4_3_1-->对应算法版本V01 EquInfo->S_BODY = 0x01; 
2018.1.26  v3.31增加硬件版本号0x01 ---> EquInfo->HW_VER = 0x01; //硬件版本号  
2018.1.27  v3.4 增加电阻加窗口处理(待验证)
		        mov_res(BODY_1); //搬电阻 -->
			    //replace-----------------加窗处理
			    DealWithResPre(BODY_1);//获得用户信息区闯入电阻，判断是否要做处理
			    DealWithRes(BODY_1,F1);//获得处理之后电阻  
			    mov_res(BODY_1);       //搬电阻(内部和上面的mov_res(BODY_1);不一样)
			    //replace-----------------
	           注意 UserInfo_TypeDef 后面使用32位来存储这和其他用8位存储不一样
		       修改 #define  READ_LAST  Log_END  // ---> #define  READ_LAST  RESVal_END  可以读到真实电阻
2018.2.27  v3.5 增加k值位数，校准k值从int8_t--->uint16_t  最高为是1表示负数，最高位0表示正数
2018.2.28  v3.6 修复1258bug，部分1258在powerdown唤醒后读的内短值异常，切换到外面通道后再切到内短读正常
				增加代码sleep.c
				Ref_Init_All(SHORT_MODE,F1);  //内短
				SendDataToAddr(ADDR_AFE_SYS,0xCE);
				Res_Init_All(ISIN2,ISIN3,VSEN3,VSEN2,F1);	//Z34
				SendDataToAddr(ADDR_AFE_SYS,0xCE);
				注释代码main.c
				//if(n==1 && m==1)PowerDownCS125x();
2018.2.28  v3.61 修改AD判稳次数 8,12次改成20次
										 #define	FILTER_AD_TIMES		  4		  //丢掉AD次数
										 #define RES_AD_TIMES			   12//8		  //参考电阻采集次数
										 #define	BODY_AD_TIMES			  20//12		  //人体电阻采集次数
				判稳范围由500改成768     if(tempADC<=768)  //if(tempADC<=500)
2018.2.28  v3.62				
				算法部分增加腰臀比参数
				算法身高参数范围数值如下
				#define HT_MAX   220  //cm
                #define HT_MIN   90  //cm
2018.3.1   v3.63 修复4字节对齐隐藏风险 __align(4) 修饰
2018.3.5   v3.64 增加 void _CS1258bug(void) 在校准、测量、唤醒后调用 \
2018.3.9   v3.65 当无法判稳time_out的处理 ReadAvgADC() 已修复
2018.4.12  v3.66 更新人体成分算法CS_BIA_V4_3_2
2018.4.17  v3.67 增加uint32_t a[64+24+128+128+128+128+24+128] __at(0x20001000);
2018.4.18  v3.68 躯干电阻计算方式改成Z5 = (Z14+Z23)/50; 计算成分依然用加窗口之后的电阻
2018.4.25  v3.69 //站姿异常判断  BOOL judge_posture(uint16_t pos,uint16_t neg) 区分测量模式和校准模式,修改如下

			////////////测量模式下///////////////					
			if(((EquMent->STATUS>>ON_OFF)&0x01)) //测量
			{							
				EquMent->STATUS&=~(1<<ON_OFF); //完成clr
				SetDRDY(0);								
			}				
			////////////校准模式下///////////////
		    else if(((EquMent->CONFIG_K>>CK)&0x01)) //校准
			{
				EquMent->CONFIG_K&=~(1<<CK);//完成clr	
				SetDRDY(0);							
			}		
2018.4.25 v3.70 上下限制有RES_MIN 300~1500改成RES_MIN 200~1500
               void DealWithRes(FunctionTestSta FP , FunctionFreq Fx) switch 中加上break;
2018.4.25 v3.71
				对于新改版1258 
					ADDR_AFE_CONFIG(0x10)由原来0xBF改写成0xBD  ------> void	Reset_CS125x(void)
					ADDR_AFE_ADC3(0x04)由原来0x00改写成0x03  ------> void InitCS125x(void)
					
2018.4.25 v3.71B
				在v371的基础上增加心率功能
				心率算法版本CS_HRI_V112 (无-7)

2018.4.25 v3.72B	
				更新算法至CS_BIAS_V4.3.3
				修改算法输入参数范围 
				#define WEIGHT_MAX   1800--->1500 //kg*10
				#define WEIGHT_MIN   300 --->200  //kg*10
				对于Z12 电阻最小值由200改到250
				#define	RES_MIN12    2500		

2018.7.11 v3.73B
				8电极模式下第一频段当只有双脚接触时，也能输出双脚电阻到BIA区
				DealWithResPre(LEG_1);//获得用户信息区闯入电阻，判断是否要做处理
				DealWithRes(LEG_1,F1);//获得处理之后电阻  
				mov_res(LEG_1);       //搬电阻				GetBodyF1();

                腰臀比 * 100
==========================CSM37F59===================================				
2018.7.31  v1.00B

	CSM37F59
	#define  FAT_CS    GPIO_PA2---> GPIO_PA4 CS控制脚由PA2更换成PA4
	
2018.9.04
		判稳范围700改1400
					