#include "usart2.h"

/***************************************
�������ƣ�USART2_Config
�������ܣ�����2��ʼ��
�������Σ���
��������ֵ����
�������ߣ�XYD_WYC
***************************************/
void USART2_Config(void)
{

	
	 //1,����GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//����ģʽ
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//����
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//2,���ô���
	//2.1����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//2.2����
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600-1;//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��ʹ��Ӳ��������
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//���ͺͽ���ģʽ
	USART_InitStruct.USART_Parity = USART_Parity_No;//��ʹ��У��
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//һλֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//8λ�ֳ�
	USART_Init(USART2,&USART_InitStruct);
	
//	USART2_NVICConfig();//�ж�����
	USART_Cmd(USART2,ENABLE);//�򿪴���
	
}

///***************************************
//�������ƣ�USART2_NVICConfig
//�������ܣ�����2�����ж�
//�������Σ���
//��������ֵ����
//�������ߣ�XYD_WYC
//***************************************/
//void USART2_NVICConfig(void)
//{
//	//�����ж�ʹ��
//	USART2->CR1 |= (1<<5);
//	//NVIC
//	NVIC_SetPriority(USART2_IRQn,0);//ռ�� 0 �μ� 1
//	NVIC_EnableIRQ(USART2_IRQn);
//}

//void USART2_IRQHandler(void)
//{
//	USART2->SR &= ~(1<<5);
//	USART1->DR = USART2->DR;
//	
//}

/***************************************
�������ƣ�USART2_SendStr
�������ܣ�����2�����ַ���
�������Σ�
					*pdata 	-- �ַ���ָ��
					lenth		-- �ַ�������
��������ֵ����
***************************************/
void USART2_SendStr(u8 *pdata,u8 lenth)
{
	u8 i = 0;
	for(i=0;i<lenth;i++)
	{
		//���ж�USART2�ϴ��Ƿ������
		while((USART2->SR & (1<<6)) == 0);
		//����������
		USART2->DR = pdata[i];
	}
}

