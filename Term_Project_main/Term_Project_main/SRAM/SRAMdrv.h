#ifndef SRAMDRV_H_
#define SRAMDRV_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE_ADDRESS 0x1000
#define SRAM_ADDRESS 0x1800
#define SRAM_ADDRESS_SPACE 0x0800

void XMEM_init(void);
void XMEM_write(uint8_t data, uint16_t addr);
uint8_t XMEM_read(uint16_t addr);
void SRAM_test(void);


#endif //__SRAMDRV__