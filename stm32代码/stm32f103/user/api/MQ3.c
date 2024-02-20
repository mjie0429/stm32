#include "MQ3.h"

/*
��������MQ3_Init
�������ܣ���MQ3����ADC���г�ʼ��
������������
��������ֵ����
�޸�ʱ�䣺2021��3��9��09:14:02
���ߣ�XYD_ZZH
*/
void MQ3_Init(void)
{
	//ADC1-IN13  PC3
	//1.�����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//2.����GPIO
	GPIO_InitTypeDef PC3;
	PC3.GPIO_Pin = GPIO_Pin_3;
	PC3.GPIO_Mode = GPIO_Mode_AIN;//ģ������
	GPIO_Init(GPIOC,&PC3);
	//3.����ADCģʽ
	ADC_InitTypeDef mq3_adc;
	mq3_adc.ADC_Mode = ADC_Mode_Independent;//��ͨ������ģʽ
	mq3_adc.ADC_ScanConvMode = DISABLE;//�رռ��
	mq3_adc.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
	mq3_adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�ֶ�����ת��
	mq3_adc.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
	mq3_adc.ADC_NbrOfChannel = 1;//ͨ������
	ADC_Init(ADC1,&mq3_adc);
	//3.1����ͨ��
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,1,ADC_SampleTime_239Cycles5);
	//4.ʹ��ADC
	ADC_Cmd(ADC1,ENABLE);
	
	//У׼ADC
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == 1);
}

float MQ3_Get(void)
{
	int Dgt;
	float ppm;
	//1.��ʼת��
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//2.�ȴ�ת�����
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == 0);
	//3.����ת����ֵ
	Dgt = ADC_GetConversionValue(ADC1);//0~4095
	//4.ͨ������������ppm
	ppm = (475.0/4096*Dgt)+25;//0~4095��Ӧ25~500ppm
	return ppm;
}
