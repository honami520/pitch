#ifndef _HOT_H__
#define _HOT_H__

#include "stm32f0xx.h"

#define HOT_DISABLE()	(GPIOB->BSRR = GPIO_Pin_7)
#define HOT_ENABLE()	(GPIOB->BRR = GPIO_Pin_7)

#define BELL_ENABLE()	(GPIOB->BSRR = GPIO_Pin_2)
#define BELL_DISABLE()	(GPIOB->BRR = GPIO_Pin_2)


void hot_init(void);
void hot_adjust(void);
void bell_control(void);

#endif



