#ifndef _KEY_H__
#define _KEY_H__

#include "stm32f0xx.h"

#define KEY_H1_H()      (GPIOB->BSRR = GPIO_Pin_8)
#define KEY_H1_L()      (GPIOB->BRR = GPIO_Pin_8)

#define KEY_H2_H()      (GPIOB->BSRR = GPIO_Pin_9)
#define KEY_H2_L()      (GPIOB->BRR = GPIO_Pin_9)

#define KEY_H3_H()      (GPIOB->BSRR = GPIO_Pin_10)
#define KEY_H3_L()      (GPIOB->BRR = GPIO_Pin_10)




void key_init(void);
void key_scan(void);
void key_done(void);










#endif


