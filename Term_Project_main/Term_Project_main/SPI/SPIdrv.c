#include "SPIdrv.h"


void spi_init_master(){
    // Set MOSI and SCK - og SS - output, all others input
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS);
	
	//DDR_SPI &= ~(1<<DD_MISO);
	
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);//|(1<<SPIE);
	//SPCR &= ~((1<<CPOL)|(1<<CPHA));
	spi_set_ss_high();
	//Comment
	
}
/*
void spi_init_slave(){
    //
	//DDR_SPI &= ~((1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SS));
    DDR_SPI = (1<<DD_MISO);
	// Set MISO output, all others input
	//DDR_SPI = (1<<DD_MISO);
	// Enable SPI
	SPCR = (1<<SPE);
}
*/
void spi_write_char(char cData){
	//char flushbuffer;
    SPDR = cData;
    //Wait for send to complete

	loop_until_bit_is_set(SPSR, SPIF);
	//while(!(SPSR & (1<<SPIF)));
	//flushbuffer = SPDR;
}

char spi_read_char(){
    SPDR = 0xAA;
	// Wait for reception to complete

    loop_until_bit_is_set(SPSR, SPIF);
	//while(!(SPSR & (1<<SPIF)));
	// Return char in data register
	return SPDR;

}

void spi_set_ss_high(){
    PORTB |= (1<<DD_SS);
}

void spi_clear_ss(){
    PORTB &= ~(1<<DD_SS);
}