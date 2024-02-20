#ifndef _MY1690_H_
#define _MY1690_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "USART2.h"

#define VoicePlay_Busy (GPIOA->IDR & (1 << 11))
//帧
typedef struct
{
	u8 Frame_Header;		//帧头
	u8 Data_Lenth;     	//数据长度
	u8 MY1690_Cmd;      //命令
	u8 Data_Buf[3];    	//Data_Buf[0] -- 第一个参数
											//Data_Buf[1] -- 第二个参数 
											//Data_Buf[2] -- 参数的个数
	u8 Data_Check;  		//数据校验码
	u8 Frame_End; 			//帧尾
}MY1690_STRUCT;

#define CMD_PLAY 		  	0x11            //播放
#define CMD_STOP 		  	0x12            //暂停
#define CMD_NEXT 	 	  	0x13            //下一曲
#define CMD_PREV 				0x14            //上一曲
#define CMD_VOICEADD  	0x15            //音量加
#define CMD_VOICESUB  	0x16            //音量减
#define CMD_RESET     	0x19            //复位
#define CMD_SPEED     	0x1A            //快进
#define CMD_SLOW      	0x1B            //快退
#define CMD_STARTorSTOP 0x1C            //播放/暂停
#define CMD_END         0x1E            //停止
#define CMD_ROOTCHO_MUSIC 0x41          //ROOT选择歌曲
#define CMD_CHOOSE_MUSIC 0x42           //选择歌曲

void MY1690_Config(void);//My1690初始化函数
u8 Voice_GetCheckVal(u8 *pdata,u8 lenth);
void Voice_SendCmd(u8 cmd,u8 arg1,u8 arg2,u8 arg_lenth);//My1690发送命令函数	
void DrunkPPM_ValCount(float MQ3_PPM);
void Play_DrunkPPM(float MQ3_PPM);
#endif

