#include "main.h"

void All_Config(void)
{
	USART1_Init(9600);
	printf("串口初始化成功\r\n");
	USART2_Config();
	Systick_Init();
	LED_Config();
	LCD_Init();
	Key_Config();
	MQ3_Init();
	MY1690_Config();
}

int main(void)
{
	float mq3_val=0,max_val=300;//mq3_val：测量值，max_val：最大值
	char lcd_buf[30];
	u8 play_flag = 0,lsd_flag = 0;
	All_Config();
	
	/*************开机动画***************************/
	LCD_Clear(WHITE);
	LCD_Show_Photo(0,40,240,239,gImage_logo);
	Delay_nms(2000);
	LCD_Clear(WHITE);
	Voice_SendCmd(0x31,0x02,0x19,1);//设置音量为25
	Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x01,2);
	LCD_Show_Photo(0,121,240,78,gImage_Drunk);
	Draw_Text_8_16_Str(88,10,WHITE,BLUE,"欢迎使用");
	Draw_Text_8_16_Str(96,280,WHITE,BLUE,"信盈达");
	Draw_Text_8_16_Str(48,300,WHITE,BLUE,"语音播报酒驾测试仪");
	while(VoicePlay_Busy);
	Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x02,2);
	while(VoicePlay_Busy);
RST:	LCD_Show_Photo(0,0,240,320,gImage_back);
	Draw_Text_8_16_Str(5,2,LGRAY,BLUE,"播报");
	Draw_Text_8_16_Str(203,2,WHITE,BLUE,"关机");
	
	while(1)
	{
		LED_LSD(lsd_flag);
		
		if(MQ3_time[0] > MQ3_time[1])
		{
			MQ3_time[0] = 0;
			mq3_val = MQ3_Get();
			printf("酒精浓度：%.2f\r\n",mq3_val);
			sprintf(lcd_buf,"实时酒精浓度:%.2f   ",mq3_val);
			Draw_Text_8_16_Str(60,230,LGRAY,RED,lcd_buf);
			sprintf(lcd_buf,"最大浓度:%.2f   ",max_val);
			Draw_Text_8_16_Str(60,260,LGRAY,RED,lcd_buf);
			
			if(mq3_val>max_val && play_flag==0)//酒精浓度超标，且没有警报过
			{
				play_flag = 1;
				lsd_flag = 1;
				Draw_Text_8_16_Str(88,155,WHITE,RED,"酒精超标");
				Voice_SendCmd(CMD_ROOTCHO_MUSIC,0x00,0x16,2);
				while(VoicePlay_Busy);
			}
			else if(mq3_val<max_val && play_flag==1)//酒精恢复正常
			{
				play_flag = 0;
				lsd_flag = 0;
				goto RST;
			}
		}
		
		
		switch(Key_GetValue())
		{
			case UP:
				max_val++;
				break;
			case DOWN:
				max_val--;
				break;
			case LEFT:
				Play_DrunkPPM(MQ3_Get());//酒精浓度检测并且播报
				while(VoicePlay_Busy);
				break;
			case RIGHT:
				Draw_Text_8_16_Str(88,152,LGRAY,BLACK,"关机中..");
				Delay_nms(1500);
				LCD_DisplayOff();
				return 0;
				break;
		}
	}
	
	
}

