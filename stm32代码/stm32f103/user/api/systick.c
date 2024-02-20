#include "main.h"

u32 Runtime = 0;
u32 MQ3_time[2] = {0,500};
u32 LSD_run[2] = {0,200};

void Systick_Init(void)
{
	SysTick_Config(72000-1);//重装载值=72000-1，计数周期为1ms
}


void SysTick_Handler(void)//中断函数，1ms进入1次
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
