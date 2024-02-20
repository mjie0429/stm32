#ifndef BEEP_H
#define BEEP_H

#include "stm32f10x.h"

/*		��������������					*/
#define BEEP_CLK	RCC_APB2Periph_GPIOB
#define BEEP_Port	GPIOB
#define BEEP_Pin	GPIO_Pin_8


/*		��������غ���					*/
void Beep_Config(void);
#define BEEP(x) (x?(GPIO_SetBits(BEEP_Port,BEEP_Pin)):(GPIO_ResetBits(BEEP_Port,BEEP_Pin)))

#endif
