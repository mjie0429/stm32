#ifndef LED_H
#define LED_H

#include "stm32f10x.h"

/*		LED引脚配置					*/
#define LED1_CLK	RCC_APB2Periph_GPIOB
#define LED1_Port	GPIOB
#define LED1_Pin	GPIO_Pin_5
#define LED2_CLK	RCC_APB2Periph_GPIOE
#define LED2_Port	GPIOE
#define LED2_Pin	GPIO_Pin_5
#define LED3_CLK	RCC_APB2Periph_GPIOA
#define LED3_Port	GPIOA
#define LED3_Pin	GPIO_Pin_5
#define LED4_CLK	RCC_APB2Periph_GPIOA
#define LED4_Port	GPIOA
#define LED4_Pin	GPIO_Pin_6

/*		LED相关函数					*/
#define LED1(x) (x?(GPIO_ResetBits(LED1_Port,LED1_Pin)):(GPIO_SetBits(LED1_Port,LED1_Pin)))
#define LED2(x) (x?(GPIO_ResetBits(LED2_Port,LED2_Pin)):(GPIO_SetBits(LED2_Port,LED2_Pin)))
#define LED3(x) (x?(GPIO_ResetBits(LED3_Port,LED3_Pin)):(GPIO_SetBits(LED3_Port,LED3_Pin)))
#define LED4(x) (x?(GPIO_ResetBits(LED4_Port,LED4_Pin)):(GPIO_SetBits(LED4_Port,LED4_Pin)))

void LED_Config(void);
void LED_LSD(u8 flag);

#endif
