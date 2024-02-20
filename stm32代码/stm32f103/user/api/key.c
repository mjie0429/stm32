#include "key.h"
#include "delay.h"

void Key_Config(void)
{
	GPIO_InitTypeDef Kio_struct;
	RCC_APB2PeriphClockCmd(UP_CLK|DOWN_CLK,ENABLE);
	
	Kio_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	Kio_struct.GPIO_Pin = UP_Pin;
	GPIO_Init(UP_Port,&Kio_struct);
	
	Kio_struct.GPIO_Pin = DOWN_Pin|RIGHT_Pin|LEFT_Pin;
	GPIO_Init(RIGHT_Port,&Kio_struct);
}

int Key_GetValue(void)
{
	if(GPIO_ReadInputDataBit(UP_Port,UP_Pin) == 0)
	{
		Delay_nms(5);
		if(GPIO_ReadInputDataBit(UP_Port,UP_Pin) == 0)
		{
			while(GPIO_ReadInputDataBit(UP_Port,UP_Pin) == 0);
			return UP;
		}
	}
	
	if(GPIO_ReadInputDataBit(DOWN_Port,DOWN_Pin) == 0)
	{
		Delay_nms(5);
		if(GPIO_ReadInputDataBit(DOWN_Port,DOWN_Pin) == 0)
		{
			while(GPIO_ReadInputDataBit(DOWN_Port,DOWN_Pin) == 0);
			return DOWN;
		}
	}
	
	if(GPIO_ReadInputDataBit(RIGHT_Port,RIGHT_Pin) == 0)
	{
		Delay_nms(5);
		if(GPIO_ReadInputDataBit(RIGHT_Port,RIGHT_Pin) == 0)
		{
			while(GPIO_ReadInputDataBit(RIGHT_Port,RIGHT_Pin) == 0);
			return RIGHT;
		}
	}
	
	if(GPIO_ReadInputDataBit(LEFT_Port,LEFT_Pin) == 1)
	{
		Delay_nms(5);
		if(GPIO_ReadInputDataBit(LEFT_Port,LEFT_Pin) == 1)
		{
			while(GPIO_ReadInputDataBit(LEFT_Port,LEFT_Pin) == 1);
			return LEFT;
		}
	}
	
	return NONE;
}
