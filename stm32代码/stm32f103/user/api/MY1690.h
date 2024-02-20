#ifndef _MY1690_H_
#define _MY1690_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "USART2.h"

#define VoicePlay_Busy (GPIOA->IDR & (1 << 11))
//֡
typedef struct
{
	u8 Frame_Header;		//֡ͷ
	u8 Data_Lenth;     	//���ݳ���
	u8 MY1690_Cmd;      //����
	u8 Data_Buf[3];    	//Data_Buf[0] -- ��һ������
											//Data_Buf[1] -- �ڶ������� 
											//Data_Buf[2] -- �����ĸ���
	u8 Data_Check;  		//����У����
	u8 Frame_End; 			//֡β
}MY1690_STRUCT;

#define CMD_PLAY 		  	0x11            //����
#define CMD_STOP 		  	0x12            //��ͣ
#define CMD_NEXT 	 	  	0x13            //��һ��
#define CMD_PREV 				0x14            //��һ��
#define CMD_VOICEADD  	0x15            //������
#define CMD_VOICESUB  	0x16            //������
#define CMD_RESET     	0x19            //��λ
#define CMD_SPEED     	0x1A            //���
#define CMD_SLOW      	0x1B            //����
#define CMD_STARTorSTOP 0x1C            //����/��ͣ
#define CMD_END         0x1E            //ֹͣ
#define CMD_ROOTCHO_MUSIC 0x41          //ROOTѡ�����
#define CMD_CHOOSE_MUSIC 0x42           //ѡ�����

void MY1690_Config(void);//My1690��ʼ������
u8 Voice_GetCheckVal(u8 *pdata,u8 lenth);
void Voice_SendCmd(u8 cmd,u8 arg1,u8 arg2,u8 arg_lenth);//My1690���������	
void DrunkPPM_ValCount(float MQ3_PPM);
void Play_DrunkPPM(float MQ3_PPM);
#endif

