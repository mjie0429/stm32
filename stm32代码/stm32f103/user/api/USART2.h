#ifndef _USART2_H_
#define _USART2_H_

#include "stm32f10x.h"
#include "stdio.h"

void USART2_Config(void);
//void USART2_NVICConfig(void);
void USART2_SendStr(u8 *pdata,u8 lenth);

#endif

