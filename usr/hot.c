#include "hot.h"
#include "ntc.h"

extern uint8_t power;
extern uint8_t hot_enable;
extern uint8_t bell_flag;
extern uint8_t hot_output;



void hot_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	HOT_DISABLE();
	BELL_DISABLE();
}


void hot_adjust(void)
{
	static uint8_t i = 0;
	
	if(hot_enable == 1)
	{	
		if(hot_output == 1)
		{
			i ++;
			
			if(i == 1)
			{
				HOT_ENABLE();
			}
			else
			{
				if(power == 500)
				{
					HOT_ENABLE();
				}
				else if(power == 250)
				{
					HOT_DISABLE();
				}
				
				i = 0;
			}			
		}
		else
		{
			i = 0;
			HOT_DISABLE();
		}
	}
	else
	{
		i = 0;
		HOT_DISABLE();
	}
}


void bell_control(void)
{
	static uint8_t i = 0, j = 0;
	static uint16_t time_out_num = 0;
	
	if(bell_flag == 1)
	{
		i ++;
		
		if(i == 1)
		{
			BELL_ENABLE();
		}
		else if(i < 10)
		{
			BELL_DISABLE();
		}
		else if(i >= 10)
		{
			BELL_DISABLE();
			i = 0;
		}
		
		time_out_num ++;
		
		if(time_out_num >= 1200)
		{
			//2分钟超时进入休眠模式
			time_out_num = 0;
			i = 0;
			j = 0;
			bell_flag = 0;
			BELL_DISABLE();
			//休眠
			sys_switch();
		}
	}
	else if(bell_flag == 2)
	{
		//平时按键音，故障时候，叫一下停止蜂鸣器响，进入睡眠
		i = 0;
		time_out_num = 0;
		j ++;
		
		if(j == 1)
		{
			BELL_ENABLE();
		}
		else if(j >= 2)
		{
			j = 0;
			bell_flag = 0;
			BELL_DISABLE();
		}
	}
	else
	{
		BELL_DISABLE();
	}
}


