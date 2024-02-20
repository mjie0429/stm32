#ifndef KEY_H
#define KEY_H

#include "stm32f10x.h"

#define UP		1
#define DOWN	2
#define LEFT	3
#define RIGHT	4
#define NONE	0

/*		∞¥º¸“˝Ω≈≈‰÷√					*/
#define UP_CLK	RCC_APB2Periph_GPIOA
#define UP_Port	GPIOA
#define UP_Pin	GPIO_Pin_0
#define RIGHT_CLK	RCC_APB2Periph_GPIOE
#define RIGHT_Port	GPIOE
#define RIGHT_Pin	GPIO_Pin_4
#define DOWN_CLK	RCC_APB2Periph_GPIOE
#define DOWN_Port	GPIOE
#define DOWN_Pin	GPIO_Pin_3
#define LEFT_CLK	RCC_APB2Periph_GPIOE
#define LEFT_Port	GPIOE
#define LEFT_Pin	GPIO_Pin_2

void Key_Config(void);
int Key_GetValue(void);


#endif
