#include "cog12864.h"


extern uint8_t hanzi[];
extern uint8_t shuzi[];


void udelay(uint16_t i)
{
    uint16_t j;
    
    for (; i > 0; i --)
    {
        j = 8;
        while(j > 0)
        {
            j --;
        }
    }
    
}

void mdelay(uint16_t i)
{
    uint16_t j;
    for(; i > 0; i --)
    {
        j = 8000;
        while(j > 0)
        {
            j --;
        }       
    }
}



void lcd_io_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA , &GPIO_InitStructure);
}



void lcd_write_dat(uint8_t dat)
{
    uint8_t i;
    
    LCD_CS_L();
    udelay(1);
    LCD_A0_H();
    udelay(1);
    
    for (i = 0; i < 8; i ++)
    {
        if (dat & 0x80)
        {
            LCD_SDI_H();
        }
        else
        {
            LCD_SDI_L();
        }
        udelay(1);
        dat <<= 1;
        LCD_SCK_L();
        LCD_SCK_H();
        udelay(1);
    }
    
    LCD_CS_H();
}


void lcd_write_cmd(uint8_t cmd)
{
    uint8_t i;
    
    LCD_CS_L();
    udelay(1);
    LCD_A0_L();
    udelay(1);
    
    for (i = 0; i < 8; i ++)
    {
        if (cmd & 0x80)
        {
            LCD_SDI_H();
        }
        else
        {
            LCD_SDI_L();
        }
        udelay(1);
        cmd <<= 1;
        LCD_SCK_L();
        LCD_SCK_H();
        udelay(1);
    }
    
    LCD_CS_H(); 
}



void lcd_init(void)
{
    lcd_io_init();
    
    LCD_CS_L();
    LCD_RES_L();
    mdelay(50);
    LCD_RES_H();
    mdelay(50);
    
    lcd_write_cmd(0xA2);
    lcd_write_cmd(0xa1); 
    lcd_write_cmd(0x80);
    mdelay(5);
    
    lcd_write_cmd(0x26);
    lcd_write_cmd(0x81);
    lcd_write_cmd(0x08);
    mdelay(10);
    
    lcd_write_cmd(0x2f);
    mdelay(10);
    
    lcd_write_cmd(0xf8);
    lcd_write_cmd(0x00);
    mdelay(5);
    
    lcd_write_cmd(0xaf);
    mdelay(5);
    
    lcd_write_cmd(0xa4);
    lcd_write_cmd(0xc8);
    lcd_write_cmd(0xa0);

    lcd_fill(0x00);
}

void lcd_fill(uint8_t fill)  
{  
    uint8_t page, column;  
    
    for(page = 0xB7; page >= 0xB0; page --)  
    {  
        lcd_write_cmd(page);  //set page address   
        lcd_write_cmd(0x10);  //set Column address MSB   
        lcd_write_cmd(0x00);  //set column address LSB   
        for(column = 0; column < 132; column ++)  
        {  
            lcd_write_dat(fill);  
        }  
    }  
}  


void lcd_goto_xy(uint8_t x, uint8_t y)
{
    uint8_t gao, di; 
    lcd_write_cmd(0xb0 | y); //页

    x = x;       //液晶是0-131的，我们只用到0-127，所以当倒序的方法时（131-0），实际上是127-0，
    gao = x & 0xf0;
    gao = gao >> 4;
    di = x & 0x0f;
    lcd_write_cmd(0x10 | gao);  //set Column address MSB   
    lcd_write_cmd(0x00 | di);  //set column address LSB

}   


void lcd_write_ch(uint8_t row, uint8_t page, uint8_t c) //row:列 page:页 dd:字符
{
    uint8_t i;      
    
    lcd_goto_xy(row * 6, page);// 列，页
    
    for(i = 0; i < 12; i++) 
    {
        lcd_write_dat(hanzi[c*24+i]);
    }
    
    lcd_goto_xy(row * 6, page + 1);// 列，页 
    
    for(i = 12; i < 24; i++) 
    {
        lcd_write_dat(hanzi[c * 24 + i]);
    }   
}


/*---------------------------------------------
LCD_write_shu: 显示6（宽）*16（高）点阵列数字字母符号等半角类
输入参数：c：显示的字符；
-----------------------------------------------*/
void lcd_write_en(uint8_t row, uint8_t page, uint8_t c) //row:列 page:页 dd:字符
{
    uint8_t i;      
    
    lcd_goto_xy(row * 6, page);// 列，页 
    for(i = 0; i < 6; i++) 
    {
        lcd_write_dat(shuzi[c * 12 + i]); 
    }
    
    lcd_goto_xy(row*6, page + 1);// 列，页 
    for(i = 6; i < 12; i ++) 
    {
        lcd_write_dat(shuzi[c * 12 + i]); 
    }       
} 





