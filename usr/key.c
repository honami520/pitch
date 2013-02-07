#include "key.h"


extern uint8_t key_val[3][3];
extern uint16_t key_num[9];
extern uint8_t key_flag[9];


void key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}


//10ms进入一次
void key_scan(void)
{
    uint8_t i, j;

    KEY_H1_H();
    KEY_H2_H();
    KEY_H3_H();

    for(i = 0; i < 3; i ++)
    {
        //将某个IO置低
        GPIOB->BRR = 1 << (8 + i);

        for(j = 0; j < 3; j ++)
        {
            if(GPIOB->IDR & (1 << (11 + j)))
            {
                key_val[i][j] = 0;
            }
            else
            {
                key_val[i][j] = 1;
            }
        }

        GPIOB->BSRR = 1 << (8 + i);
    }

    for(i = 0; i < 3; i ++)
    {
        for(j = 0; j < 3; j ++)
        {
            if(key_val[i][j] == 1)
            {
                //有键按下，则计数增加
                key_num[3 * i + j] ++;

                if(key_num[3 * i + j] == 3)
                {
                    key_flag[3 * i + j] = 1;
                }
            }
            else
            {
                key_num[3 * i + j] = 0;
            }
        }
    }
}



void key_done(void)
{
    if(key_flag[0] == 1)
    {
        key_flag[0] = 0;

    }

    if(key_flag[1] == 1)
    {
        key_flag[1] = 0;

    }

    if(key_flag[2] == 1)
    {
        key_flag[2] = 0;

    }

    if(key_flag[3] == 1)
    {
        key_flag[3] = 0;

    }

    if(key_flag[4] == 1)
    {
        key_flag[4] = 0;

    }

    if(key_flag[5] == 1)
    {
        key_flag[5] = 0;

    }

    if(key_flag[6] == 1)
    {
        key_flag[6] = 0;

    }

    if(key_flag[7] == 1)
    {
        key_flag[7] = 0;

    }

    if(key_flag[8] == 1)
    {
        key_flag[8] = 0;

    }
}

