#ifndef _NTC_H__
#define _NTC_H__

#include "stm32f0xx.h"

#define ADC1_DR_Address    0x40012440
#define NTC_TEMP_DALTA  -3      //NTC���ս���˹��������������NTC��������ϸߣ�������-x�ȣ���������¶Ƚϵͣ�����X��


void ntc_init(void);
void adc_convert(void);
int8_t ntc_temp_get(uint16_t adc);

#endif




