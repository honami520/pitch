/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-May-2012
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"
#include <stdio.h>
#include "eeprom.h"
#include "flash_eep.h"
#include "cog12864.h"
#include "key.h"
#include "io.h"
#include "pwm.h"
#include "ntc.h"


uint8_t time_1ms_flag = 0;
uint8_t time_10ms_flag = 0;
uint8_t time_100ms_flag = 0;
uint8_t time_1s_flag = 0;

//key
uint8_t key_val[3][3];
uint16_t key_num[9];
uint8_t key_flag[9];


//ntc
uint16_t adc_dma_buf[5];
int8_t ntc_now;     //用于当前温度显示
int8_t ntc_temp;
uint8_t hot_enable;


//eeprom
uint16_t VirtAddVarTab[NB_OF_VAR] =
{
    0xaa00, 0xaa01, 0xaa02, 0xaa03, 0xaa04, 0xaa05, 0xaa06, 0xaa07,
    0xaa08, 0xaa09, 0xaa0a, 0xaa0b, 0xaa0c, 0xaa0d, 0xaa0e, 0xaa0f,
    0xaa10,
};



//6*16字符
uint8_t shuzi[]={
/*--  文字:  0  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0xF8,0x04,0x04,0x04,0xF8,0x00,0x01,0x02,0x02,0x02,0x01,0x00,

/*--  文字:  1  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x00,0x08,0xFC,0x00,0x00,0x00,0x00,0x02,0x03,0x02,0x00,0x00,

/*--  文字:  2  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x18,0x84,0x44,0x24,0x18,0x00,0x03,0x02,0x02,0x02,0x02,0x00,

/*--  文字:  3  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x08,0x04,0x24,0x24,0xD8,0x00,0x01,0x02,0x02,0x02,0x01,0x00,

/*--  文字:  4  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x40,0xB0,0x88,0xFC,0x80,0x00,0x00,0x00,0x00,0x03,0x02,0x00,

/*--  文字:  5  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x3C,0x24,0x24,0x24,0xC4,0x00,0x01,0x02,0x02,0x02,0x01,0x00,

/*--  文字:  6  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0xF8,0x24,0x24,0x2C,0xC0,0x00,0x01,0x02,0x02,0x02,0x01,0x00,

/*--  文字:  7  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x0C,0x04,0xE4,0x1C,0x04,0x00,0x00,0x00,0x03,0x00,0x00,0x00,

/*--  文字:  8  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0xD8,0x24,0x24,0x24,0xD8,0x00,0x01,0x02,0x02,0x02,0x01,0x00,

/*--  文字:  9  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=6x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=6x16  --*/
0x38,0x44,0x44,0x44,0xF8,0x00,0x00,0x03,0x02,0x02,0x01,0x00,

};

uint8_t hanzi[]=
{
/*--  文字:  单  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
0x00,0x00,0x7C,0x55,0x56,0xFC,0x56,0x55,0x54,0x7C,0x00,0x00,0x01,0x01,0x01,0x01,
0x01,0x07,0x01,0x01,0x01,0x01,0x01,0x00,


/*--  文字:  单  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --
0x00,0x00,0x3E,0xAA,0x6A,0x3F,0x6A,0xAA,0x2A,0x3E,0x00,0x00,0x80,0x80,0x80,0x80,
0x80,0xE0,0x80,0x80,0x80,0x80,0x80,0x00,
*/

/*--  文字:  片  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
0x00,0x00,0xFF,0x48,0x48,0x48,0x4F,0xC8,0x08,0x08,0x08,0x00,0x04,0x02,0x01,0x00,
0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,

/*--  文字:  机  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
0x84,0x64,0xFF,0x24,0x44,0xFE,0x02,0x02,0xFF,0x02,0x00,0x00,0x01,0x00,0x07,0x04,
0x02,0x01,0x00,0x00,0x07,0x04,0x07,0x00,

/*--  文字:  开  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
0x20,0x22,0x22,0xFE,0x22,0x22,0x22,0xFE,0x22,0x23,0x22,0x00,0x04,0x04,0x02,0x01,
0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,

/*--  文字:  发  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
0x08,0x0E,0x88,0x78,0x2F,0xE8,0x28,0xA9,0x6A,0x08,0x08,0x00,0x04,0x02,0x05,0x04,
0x02,0x02,0x01,0x02,0x02,0x04,0x04,0x00,

/*--  文字:  工  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
0x00,0x02,0x02,0x02,0x02,0xFE,0x02,0x02,0x03,0x02,0x00,0x00,0x04,0x04,0x04,0x04,
0x04,0x07,0x04,0x04,0x04,0x04,0x04,0x00,

/*--  文字:  作  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
0x10,0x08,0xFC,0x13,0x08,0x04,0xFF,0x24,0x24,0x24,0x04,0x00,0x00,0x00,0x07,0x00,
0x00,0x00,0x07,0x01,0x01,0x01,0x01,0x00,

/*--  文字:  室  --*/
/*--  宋体9;  此字体下对应的点阵为：宽x高=12x12   --*/
/*--  高度不是8的倍数，现调整为：宽度x高度=12x16  --*/
0x04,0x06,0x4A,0x6A,0x5A,0xCB,0x4A,0x5A,0x6A,0x4A,0x06,0x00,0x04,0x04,0x05,0x05,
0x05,0x07,0x05,0x05,0x05,0x04,0x04,0x00,

};

    

void systick_init(void);


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
