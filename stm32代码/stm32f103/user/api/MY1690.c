#include "MY1690.h"
#include "usart.h"


/*********************全局变量**************************/
float MQ3PPM_GetVal;				//存储酒精浓度float变量
uint8_t MQ3_Num[5];					//存储酒精浓度的百、十、个和小数后两位

/**********************************
函数名称：MY1690_Config
函数功能：MY1690初始化
函数传参：无
函数返回值：无
函数作者：XYD_WYC
		BUSY 			 	-- PA11 		-- 浮空输入
		USART2_TX 	-- PA2    -- 复用推挽输出
		USART2_RX   -- PA3    -- 浮空输入
**********************************/
void MY1690_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//输入模式
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;//不上拉也不下拉
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	USART2_Config(); //串口2初始化，用于                         发送指令给语音芯片
}

MY1690_STRUCT MY1690_SendBuf={.Frame_Header = 0x7E,.Frame_End = 0xEF};
/**********************************
函数名称：Voice_GetCheckVal
函数功能：得到校验码 
函数传参：
				*pdata -- 校准参数
				lenth  -- 参数的个数
函数返回值：^计算后的数
**********************************/
u8 Voice_GetCheckVal(u8 *pdata,u8 lenth)
{
	u8 r_value = pdata[0];			/*获取0号元素*/
	u8 i = 0;
	
	for(i=1;i<lenth;i++)
	{
		r_value ^= pdata[i];
	}
	return r_value;
}

/**********************************
函数名称：Voice_SendCmd
函数功能：发送命令 
函数传参：
				cmd -- 命令
				arg1 -- 第一个参数
				arg2 -- 第二个参数
				arg_lenth -- 参数长度
函数返回值：无
**********************************/
void Voice_SendCmd(u8 cmd,u8 arg1,u8 arg2,u8 arg_lenth)
{
	//给MY1690_SendBuf传递参数
	//命令填充
	MY1690_SendBuf.MY1690_Cmd = cmd;
	//参数填充
	MY1690_SendBuf.Data_Buf[0] = arg1;				/*参数1*/
	MY1690_SendBuf.Data_Buf[1] = arg2;				/*参数2*/
	MY1690_SendBuf.Data_Buf[2] = arg_lenth;		/*参数长度*/
	//长度填充
	MY1690_SendBuf.Data_Lenth = 3 + arg_lenth;	/*长度 =长度(1) + cmd(1) + 参数长度(arg_lenth) + 检验码(1)*/
	MY1690_SendBuf.Data_Check = Voice_GetCheckVal(&MY1690_SendBuf.Data_Lenth,2+arg_lenth);//lenth+cmd + 参数
	//发送
	USART2_SendStr(&MY1690_SendBuf.Frame_Header,3);//帧起始+长度+命令
	USART2_SendStr(MY1690_SendBuf.Data_Buf,arg_lenth);//发送参数
	USART2_SendStr(&MY1690_SendBuf.Data_Check,2);//异或值+帧尾
	

}



/***************************************
函数名称：DrunkPPM_ValCount
函数功能：计算酒精PPM的百、十、个、小数位
函数传参：MQ3_PPM MQ3测试到的PPM
函数返回值：无
函数作者：XYD_WYC
***************************************/
void DrunkPPM_ValCount(float MQ3_PPM)
{
	uint16_t PPM_MAX100 = 0;
	PPM_MAX100 = (uint16_t)(MQ3_PPM * 100);
	MQ3_Num[0] = PPM_MAX100/10000;					//百位
	MQ3_Num[1] = PPM_MAX100%10000/1000;			//十位
	MQ3_Num[2] = PPM_MAX100%1000/100;				//个位
	//小数第一位
	MQ3_Num[3] = PPM_MAX100%100/10;	
	//小数第一位
	MQ3_Num[4] = PPM_MAX100%10;	
	printf("%d%d%d.%d%d",MQ3_Num[0],MQ3_Num[1],MQ3_Num[2],MQ3_Num[3],MQ3_Num[4]);
}


/***************************************
函数名称：Play_DrunkPPM
函数功能：播报酒精PPM
函数传参：MQ3_PPM MQ3测试到的PPM
函数返回值：无
函数作者：XYD_WYC
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
					//只要不等于0，就播报
					if(MQ3_Num[i] != 0)
						Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x04,2);
					//等于0，只有在十位，而且百位不为0才播报
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
		else if((i == 1)&&(MQ3_Num[1] != 0))//播报十
			Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x10,2);
		else if(i == 2)
			Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x11,2);
	}
	Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x0E,2);
}
