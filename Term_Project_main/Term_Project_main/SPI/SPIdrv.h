#ifndef SPIDRV_H_
#define SPIDRV_H_

#include <avr/io.h>
#include "spi.h"
#include "uart.h"
#include <avr/interrupt.h>
#include "MCP2515.h"
#include <stdio.h>
#include <avr/sfr_defs.h>


//The SPI bus uses the DDRB register with pins from PB4-PB7
#define DDR_SPI DDRB
#define DD_SS PB4
#define DD_MOSI PB5
#define DD_MISO PB6
#define DD_SCK PB7

void spi_init_master(void);
void spi_init_slave(void);
void spi_write_char(char character);
char spi_read_char(void);
void spi_set_ss_high(void);
void spi_clear_ss(void);

#endif //SPIDRV_H_