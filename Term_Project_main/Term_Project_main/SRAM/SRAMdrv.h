#ifndef __SRAMDRV__
#define __SRAMDRV__

void XMEM_init(void);
void XMEM_write(uint8_t data, uint16_t addr);
uint8_t XMEM_read(uint16_t addr);


#endif //__SRAMDRV__