#ifndef USART_H
#define USART_H

#include "stm32f10x.h"

void USART1_Init(int brr);
void USART1_Send(u8 data);
u8 USART1_Rcv(void);

#endif
