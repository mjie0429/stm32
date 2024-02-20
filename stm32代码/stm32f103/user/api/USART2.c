#include "usart2.h"

/***************************************
函数名称：USART2_Config
函数功能：串口2初始化
函数传参：无
函数返回值：无
函数作者：XYD_WYC
***************************************/
void USART2_Config(void)
{

	
	 //1,配置GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//高速
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//2,配置串口
	//2.1开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//2.2配置
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600-1;//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不使用硬件流控制
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//发送和接收模式
	USART_InitStruct.USART_Parity = USART_Parity_No;//不使用校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//一位停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//8位字长
	USART_Init(USART2,&USART_InitStruct);
	
//	USART2_NVICConfig();//中断配置
	USART_Cmd(USART2,ENABLE);//打开串口
	
}

///***************************************
//函数名称：USART2_NVICConfig
//函数功能：串口2接收中断
//函数传参：无
//函数返回值：无
//函数作者：XYD_WYC
//***************************************/
//void USART2_NVICConfig(void)
//{
//	//接收中断使能
//	USART2->CR1 |= (1<<5);
//	//NVIC
//	NVIC_SetPriority(USART2_IRQn,0);//占先 0 次级 1
//	NVIC_EnableIRQ(USART2_IRQn);
//}

//void USART2_IRQHandler(void)
//{
//	USART2->SR &= ~(1<<5);
//	USART1->DR = USART2->DR;
//	
//}

/***************************************
函数名称：USART2_SendStr
函数功能：串口2发送字符串
函数传参：
					*pdata 	-- 字符串指针
					lenth		-- 字符串长度
函数返回值：无
***************************************/
void USART2_SendStr(u8 *pdata,u8 lenth)
{
	u8 i = 0;
	for(i=0;i<lenth;i++)
	{
		//再判断USART2上次是否发送完成
		while((USART2->SR & (1<<6)) == 0);
		//发送新数据
		USART2->DR = pdata[i];
	}
}

