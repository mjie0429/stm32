#include "usart.h"
#include "stdio.h"

/*
函数名：USART_Init
函数功能：初始化串口
函数参数：brr--波特率
函数返回值：无
修改时间：2021年3月9日09:14:02
作者：XYD_ZZH
*/
void USART1_Init(int brr)
{
	//1.打开时钟  GPIO  USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//2.GPIO初始化
	//PA9--Tx  PA10--Rx
	GPIO_InitTypeDef Kio;
	Kio.GPIO_Pin = GPIO_Pin_9;
	Kio.GPIO_Mode = GPIO_Mode_AF_PP;
	Kio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&Kio);
	
	Kio.GPIO_Pin = GPIO_Pin_10;
	Kio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&Kio);
	
	//3.USART1初始化
	USART_InitTypeDef abc;
	abc.USART_BaudRate = brr-1;
	abc.USART_WordLength = USART_WordLength_8b;
	abc.USART_StopBits = USART_StopBits_1;
	abc.USART_Parity = USART_Parity_No;
	abc.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	abc.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART1,&abc);
	
	USART_Cmd(USART1,ENABLE);
}

void USART1_Send(u8 data)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == 0);//等待前面数据发送完成
	USART_SendData(USART1,data);
}

u8 USART1_Rcv(void)
{
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == 0);//等待接收到数据
	return	USART_ReceiveData(USART1);
}

int fputc(int c, FILE * f)
{
	USART1_Send(c);
	return c;
}
