#include "led.h"
#include "systick.h"

void LED_Config(void)
{
	GPIO_InitTypeDef LIO_Struct;
	RCC_APB2PeriphClockCmd(LED1_CLK|LED2_CLK|LED3_CLK|LED4_CLK,ENABLE);
	
	LIO_Struct.GPIO_Mode = GPIO_Mode_Out_PP;
	LIO_Struct.GPIO_Speed = GPIO_Speed_50MHz;
	LIO_Struct.GPIO_Pin = LED1_Pin;
	GPIO_Init(LED1_Port,&LIO_Struct);
	
	LIO_Struct.GPIO_Pin = LED2_Pin;
	GPIO_Init(LED2_Port,&LIO_Struct);
	
	LIO_Struct.GPIO_Pin = LED3_Pin;
	GPIO_Init(LED3_Port,&LIO_Struct);
	
	LIO_Struct.GPIO_Pin = LED4_Pin;
	GPIO_Init(LED4_Port,&LIO_Struct);
	
	LED1(0);
	LED2(0);
	LED3(0);
	LED4(0);
}



void LED_LSD(u8 flag)
{
	static int count = 1;
	if(flag == 1)
	{
		if(LSD_run[0] > LSD_run[1])
		{
			LSD_run[0] = 0;
			switch(count)
			{
				case 1:LED1(1);LED2(0);LED3(0);LED4(0);break;
				case 2:LED1(0);LED2(1);LED3(0);LED4(0);break;
				case 3:LED1(0);LED2(0);LED3(1);LED4(0);break;
				case 4:LED1(0);LED2(0);LED3(0);LED4(1);break;
			}
			count++;
			if(count > 4)count = 1;
		}
	}
	else if(flag == 0)
	{
		LED1(0);LED2(0);LED3(0);LED4(0);
	}
}
