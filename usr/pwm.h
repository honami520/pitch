#ifndef _PWM_H__
#define _PWM_H__

#include "stm32f0xx.h"


#define MT_ON()         (GPIOB->BSRR = GPIO_Pin_0)
#define MT_OFF()        (GPIOB->BRR = GPIO_Pin_0)



void pwm_init(void);
void pwm_set(uint16_t val);


#endif


