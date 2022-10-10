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


void spi_init_master(){
    // Set MOSI and SCK - og SS - output, all others input
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<SPIE);
	spi_set_ss_high();
}

void spi_init_slave(){
    //
    // Set MISO output, all others input
	DDR_SPI = (1<<DD_MISO);
	// Enable SPI
	SPCR = (1<<SPE);
}

void spi_write_char(char character){
    SPDR = character;
    //Wait for send to complete
    loop_until_bit_is_set(SPSR, SPIF)
}

char spi_read_char(){
    SPDR = 0xFF;
	// Wait for reception to complete
    loop_until_bit_is_set(SPSR, SPIF);
	// Return char in data register
	return SPDR;
}

void spi_set_ss_high(){
    PORTB |= (1 << DD_SS)
}

void spi_clear_ss(){
    PORTB &= ~(1 << DD_SS);
}