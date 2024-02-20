#include "main.h"


/*
 1Œ¢√Î—” ±
*/
void Delay_1us(void)
{
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}

/*
	nŒ¢√Î—” ±
*/
void Delay_nus(int n)
{
	while(n--)
	{
		Delay_1us();
	}
}

/*
	n∫¡√Î—” ±
*/
void Delay_nms(int n)
{
	while(n--)
	{
		Delay_nus(1000);
	}
}
