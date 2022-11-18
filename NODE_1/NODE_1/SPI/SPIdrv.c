#include "SPIdrv.h"


void spi_init_master(){
    // Set MOSI and SCK - og SS - output, all others input
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
		
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

	spi_set_ss_high();
	
}

void spi_write_char(char cData){

    SPDR = cData;
    //Wait for send to complete

	loop_until_bit_is_set(SPSR, SPIF);
}

char spi_read_char(){
    SPDR = 0xAA;
	// Wait for reception to complete

    loop_until_bit_is_set(SPSR, SPIF);
	// Return char in data register
	return SPDR;

}

void spi_set_ss_high(){
    PORTB |= (1<<DD_SS);
}

void spi_clear_ss(){
    PORTB &= ~(1<<DD_SS);
}