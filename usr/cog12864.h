#ifndef _COG12864_H__
#define _COG12864_H__

#include "stm32f0xx.h"


#define LCD_SDI_H()     (GPIOA->BSRR = GPIO_Pin_7)
#define LCD_SDI_L()     (GPIOA->BRR = GPIO_Pin_7)

#define LCD_SCK_H()     (GPIOA->BSRR = GPIO_Pin_6)
#define LCD_SCK_L()     (GPIOA->BRR = GPIO_Pin_6)

#define LCD_A0_H()      (GPIOA->BSRR = GPIO_Pin_5)
#define LCD_A0_L()      (GPIOA->BRR = GPIO_Pin_5)

#define LCD_RES_H()     (GPIOA->BSRR = GPIO_Pin_4)
#define LCD_RES_L()     (GPIOA->BRR = GPIO_Pin_4)

#define LCD_CS_H()      (GPIOA->BSRR = GPIO_Pin_3)
#define LCD_CS_L()      (GPIOA->BRR = GPIO_Pin_3)






void lcd_io_init(void);
void udelay(uint16_t i);
void mdelay(uint16_t i);
void lcd_write_dat(uint8_t dat);
void lcd_write_cmd(uint8_t cmd);
void lcd_init(void);
void lcd_fill(uint8_t fill);
void lcd_goto_xy(uint8_t x, uint8_t y);
void lcd_write_ch(uint8_t row, uint8_t page, uint8_t c);
void lcd_write_en(uint8_t row, uint8_t page, uint8_t c);

#endif



