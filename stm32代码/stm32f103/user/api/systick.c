#include "main.h"

u32 Runtime = 0;
u32 MQ3_time[2] = {0,500};
u32 LSD_run[2] = {0,200};

void Systick_Init(void)
{
	SysTick_Config(72000-1);//��װ��ֵ=72000-1����������Ϊ1ms
}


void SysTick_Handler(void)//�жϺ�����1ms����1��
{
	Runtime++;
	MQ3_time[0]++;
	LSD_run[0]++;
}

void Sys_nms(u32 n)
{
	u32 NowTime = Runtime;
	while(Runtime < NowTime+n);
}
