#include "MQ3.h"

/*
函数名：MQ3_Init
函数功能：对MQ3连接ADC进行初始化
函数参数：无
函数返回值：无
修改时间：2021年3月9日09:14:02
作者：XYD_ZZH
*/
void MQ3_Init(void)
{
	//ADC1-IN13  PC3
	//1.打开相关时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//2.配置GPIO
	GPIO_InitTypeDef PC3;
	PC3.GPIO_Pin = GPIO_Pin_3;
	PC3.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
	GPIO_Init(GPIOC,&PC3);
	//3.配置ADC模式
	ADC_InitTypeDef mq3_adc;
	mq3_adc.ADC_Mode = ADC_Mode_Independent;//单通道独立模式
	mq3_adc.ADC_ScanConvMode = DISABLE;//关闭间断
	mq3_adc.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	mq3_adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//手动开启转换
	mq3_adc.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
	mq3_adc.ADC_NbrOfChannel = 1;//通道数量
	ADC_Init(ADC1,&mq3_adc);
	//3.1配置通道
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,1,ADC_SampleTime_239Cycles5);
	//4.使能ADC
	ADC_Cmd(ADC1,ENABLE);
	
	//校准ADC
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == 1);
}

float MQ3_Get(void)
{
	int Dgt;
	float ppm;
	//1.开始转换
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//2.等待转换完成
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == 0);
	//3.返回转换的值
	Dgt = ADC_GetConversionValue(ADC1);//0~4095
	//4.通过数字量计算ppm
	ppm = (475.0/4096*Dgt)+25;//0~4095对应25~500ppm
	return ppm;
}
