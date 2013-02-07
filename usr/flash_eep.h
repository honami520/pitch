#ifndef _FLASH_EEP_H__
#define _FLASH_EEP_H__

#include "stm32f0xx.h"
#include "eeprom.h"

#define PASS_WORD       0x1f2e3d4c




void flash_init(void);
void eep_write16(uint8_t addr, uint16_t dat);
void eep_write32(uint8_t addr, uint32_t dat);
uint16_t eep_read16(uint8_t addr);
uint32_t eep_read32(uint8_t addr);
void eep_init(void);



#endif













