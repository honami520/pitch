#ifndef _IO_H__
#define _IO_H__
#include "stm32f0xx.h"


#define BELL_ON()       (GPIOB->BSRR = GPIO_Pin_1)
#define BELL_OFF()      (GPIOB->BRR = GPIO_Pin_1)

#define PWR_CON_ON()    (GPIOB->BSRR = GPIO_Pin_2)
#define PWR_CON_OFF()   (GPIOB->BRR = GPIO_Pin_2)

#define OUT_ON()       (GPIOB->BSRR = GPIO_Pin_3)
#define OUT_OFF()      (GPIOB->BRR = GPIO_Pin_3)




void io_init(void);


#endif


