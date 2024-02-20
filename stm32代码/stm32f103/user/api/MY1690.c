#include "MY1690.h"
#include "usart.h"


/*********************ȫ�ֱ���**************************/
float MQ3PPM_GetVal;				//�洢�ƾ�Ũ��float����
uint8_t MQ3_Num[5];					//�洢�ƾ�Ũ�ȵİ١�ʮ������С������λ

/**********************************
�������ƣ�MY1690_Config
�������ܣ�MY1690��ʼ��
�������Σ���
��������ֵ����
�������ߣ�XYD_WYC
		BUSY 			 	-- PA11 		-- ��������
		USART2_TX 	-- PA2    -- �����������
		USART2_RX   -- PA3    -- ��������
**********************************/
void MY1690_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//����ģʽ
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//������Ҳ������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	USART2_Config(); //����2��ʼ��������                         ����ָ�������оƬ
}

MY1690_STRUCT MY1690_SendBuf={.Frame_Header = 0x7E,.Frame_End = 0xEF};
/**********************************
�������ƣ�Voice_GetCheckVal
�������ܣ��õ�У���� 
�������Σ�
				*pdata -- У׼����
				lenth  -- �����ĸ���
��������ֵ��^��������
**********************************/
u8 Voice_GetCheckVal(u8 *pdata,u8 lenth)
{
	u8 r_value = pdata[0];			/*��ȡ0��Ԫ��*/
	u8 i = 0;
	
	for(i=1;i<lenth;i++)
	{
		r_value ^= pdata[i];
	}
	return r_value;
}

/**********************************
�������ƣ�Voice_SendCmd
�������ܣ��������� 
�������Σ�
				cmd -- ����
				arg1 -- ��һ������
				arg2 -- �ڶ�������
				arg_lenth -- ��������
��������ֵ����
**********************************/
void Voice_SendCmd(u8 cmd,u8 arg1,u8 arg2,u8 arg_lenth)
{
	//��MY1690_SendBuf���ݲ���
	//�������
	MY1690_SendBuf.MY1690_Cmd = cmd;
	//�������
	MY1690_SendBuf.Data_Buf[0] = arg1;				/*����1*/
	MY1690_SendBuf.Data_Buf[1] = arg2;				/*����2*/
	MY1690_SendBuf.Data_Buf[2] = arg_lenth;		/*��������*/
	//�������
	MY1690_SendBuf.Data_Lenth = 3 + arg_lenth;	/*���� =����(1) + cmd(1) + ��������(arg_lenth) + ������(1)*/
	MY1690_SendBuf.Data_Check = Voice_GetCheckVal(&MY1690_SendBuf.Data_Lenth,2+arg_lenth);//lenth+cmd + ����
	//����
	USART2_SendStr(&MY1690_SendBuf.Frame_Header,3);//֡��ʼ+����+����
	USART2_SendStr(MY1690_SendBuf.Data_Buf,arg_lenth);//���Ͳ���
	USART2_SendStr(&MY1690_SendBuf.Data_Check,2);//���ֵ+֡β
	

}



/***************************************
�������ƣ�DrunkPPM_ValCount
�������ܣ�����ƾ�PPM�İ١�ʮ������С��λ
�������Σ�MQ3_PPM MQ3���Ե���PPM
��������ֵ����
�������ߣ�XYD_WYC
***************************************/
void DrunkPPM_ValCount(float MQ3_PPM)
{
	uint16_t PPM_MAX100 = 0;
	PPM_MAX100 = (uint16_t)(MQ3_PPM * 100);
	MQ3_Num[0] = PPM_MAX100/10000;					//��λ
	MQ3_Num[1] = PPM_MAX100%10000/1000;			//ʮλ
	MQ3_Num[2] = PPM_MAX100%1000/100;				//��λ
	//С����һλ
	MQ3_Num[3] = PPM_MAX100%100/10;	
	//С����һλ
	MQ3_Num[4] = PPM_MAX100%10;	
	printf("%d%d%d.%d%d",MQ3_Num[0],MQ3_Num[1],MQ3_Num[2],MQ3_Num[3],MQ3_Num[4]);
}


/***************************************
�������ƣ�Play_DrunkPPM
�������ܣ������ƾ�PPM
�������Σ�MQ3_PPM MQ3���Ե���PPM
��������ֵ����
�������ߣ�XYD_WYC
***************************************/
void Play_DrunkPPM(float MQ3_PPM)
{
	uint32_t i = 0;
	DrunkPPM_ValCount(MQ3_PPM);
	while(VoicePlay_Busy);
	Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x12,2);
	while(VoicePlay_Busy);
	for(i=0;i<5;i++)
	{
			switch(MQ3_Num[i])
			{
				case 0:
					//ֻҪ������0���Ͳ���
					if(MQ3_Num[i] != 0)
						Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x04,2);
					//����0��ֻ����ʮλ�����Ұ�λ��Ϊ0�Ų���
					else if((i == 1)&&(MQ3_Num[0] != 0))
						Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x04,2);
					
				break;
				case 1:Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x05,2);break;
				case 2:Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x06,2);break;
				case 3:Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x07,2);break;
				case 4:Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x08,2);break;
				case 5:Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x09,2);break;
				case 6:Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x0A,2);break;
				case 7:Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x0B,2);break;
				case 8:Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x0C,2);break;
				case 9:Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x0D,2);break;
			}

		if((i == 0)&&(MQ3_Num[0] != 0))
			Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0xF,2);
		else if((i == 1)&&(MQ3_Num[1] != 0))//����ʮ
			Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x10,2);
		else if(i == 2)
			Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x11,2);
	}
	Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x0E,2);
}
