#include "beep.h"

void Beep_Config(void)
{
	GPIO_InitTypeDef Bio_stuct;
	RCC_APB2PeriphClockCmd(BEEP_CLK,ENABLE);
	
	Bio_stuct.GPIO_Mode = GPIO_Mode_Out_PP;
	Bio_stuct.GPIO_Speed = GPIO_Speed_50MHz;
	Bio_stuct.GPIO_Pin = BEEP_Pin;
	GPIO_Init(BEEP_Port,&Bio_stuct);
	
	BEEP(0);
}
