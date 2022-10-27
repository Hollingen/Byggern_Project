#include "MCP2515drv.h"
#include "../SPI/SPIdrv.h"




uint8_t mcp2515_init(){
    uint8_t value;
	spi_init_master(); // Initialize SPI
    mcp2515_reset(); // end reset - command
    // Self - testS
	//mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_CONFIG);

    value = mcp2515_read(MCP_CANSTAT);
	//printf("value: %d\n\r", value);
    if ((value & MODE_MASK) != MODE_CONFIG) {
        printf ("MCP2515 is NOT in config mode after reset !\n\r");
		return -1;
    }
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_LOOPBACK);
	printf("value: %d\n\r", value);

    return 0;
}


uint8_t mcp2515_read(uint8_t address){
	uint8_t value;
    DDRB &= ~(1 << PB4); // Select CAN - controller

    spi_write_char(MCP_READ); // Send read instruction
    spi_write_char(address); // Send address
	
    value = spi_read_char() ; // Read result
    
	DDRB |= (1 << PB4); // Deselect CAN - controller
	return value;
}

void mcp2515_reset(){
    DDRB &= ~(1 << PB4); // Select CAN - controller
    spi_write_char(MCP_RESET);   //Write reset bit to SPI
    DDRB |= (1 << PB4); // Deselect CAN - controller
}

void mcp2515_write(uint8_t address, uint8_t data){
    DDRB &= ~(1 << PB4); // Select CAN - controller
    spi_write_char(MCP_WRITE); // Send write instruction
    spi_write_char(address); // Send address
    spi_write_char(data); // Send data
    DDRB |= (1 << PB4); // Deselect CAN - controller
}

void mcp2515_request_to_send(){
    DDRB &= ~(1 << PB4); // Select CAN - controller
    spi_write_char(MCP_RTS_ALL);   //Write RTS bit to SPI
    DDRB |= (1 << PB4); // Deselect CAN - controller
}

uint8_t mcp2515_read_status(){
    uint8_t status;
    DDRB &= ~(1 << PB4); // Select CAN - controller
    spi_write_char(MCP_READ_STATUS);   //Write read_status bit to SPI
    status = spi_read_char();
    DDRB |= (1 << PB4); // Deselect CAN - controller

    return status;

}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
    DDRB &= ~(1 << DD_SS); // Select CAN - controller
    spi_write_char(MCP_BITMOD);   //Write read_status bit to SPI
    spi_write_char(address); // Send address
    spi_write_char(mask); // Send mask
    spi_write_char(data); // Send data
    DDRB |= (1 << DD_SS); // Deselect CAN - controller
}