#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f10x.h"

extern u32 Runtime;
extern u32 MQ3_time[2];
extern u32 LSD_run[2];

void Systick_Init(void);
void Sys_nms(u32 n);

#endif
