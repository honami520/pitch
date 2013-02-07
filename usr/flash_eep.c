#include "flash_eep.h"


extern uint16_t VirtAddVarTab[NB_OF_VAR];

void flash_init(void)
{
    FLASH_Unlock();
    EE_Init();
}


void eep_write16(uint8_t addr, uint16_t dat)
{
    EE_WriteVariable(0xaa00 + addr, dat);
}

void eep_write32(uint8_t addr, uint32_t dat)
{
    EE_WriteVariable(0xaa00 + addr, (uint16_t)(dat >> 16));
    EE_WriteVariable(0xaa00 + addr + 1, (uint16_t)(dat & 0x0000ffff));
}

uint16_t eep_read16(uint8_t addr)
{
    uint16_t rt = 0;

    EE_ReadVariable(0xaa00 + addr, &rt);

    return rt;
}

uint32_t eep_read32(uint8_t addr)
{
    uint32_t rt = 0;
    uint16_t tmp = 0;

    EE_ReadVariable(0xaa00 + addr, &tmp);
    rt = tmp << 16;
    EE_ReadVariable(0xaa00 + addr + 1, &tmp);
    rt |= tmp;

    return rt;
}



//将初始化数据从EEPROM中读出，或者写入初始化数据
void eep_init(void)
{
	flash_init();

}






