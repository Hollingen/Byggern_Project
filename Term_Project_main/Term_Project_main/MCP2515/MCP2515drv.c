#include "MCP2515drv.h"




uint8_t mcp2515_init(){
    uint8_t value ;
    SPI_init(); // Initialize SPI
    mcp2515_reset(); // Send reset - command
    // Self - test
    mcp2515_read(MCP_CANSTAT, &value);
    if ((value & MODE_MASK) != MODE_CONFIG) {
    printf ("MCP2515 is NOT in configuration mode after reset !\n");
    return 1;
    }
    // More initialization
    return 0;
}


uint8_t mcp2515_read (uint8_t address){
    uint8_t result;
    PORTB &= ~(1 << CAN_CS); // Select CAN - controller
    spi_write_char(MCP_READ); // Send read instruction
    spi_write_char(address); // Send address
    result = SPI_read() ; // Read result
    PORTB |= (1 << CAN_CS); // Deselect CAN - controller
    return result;
}

void mcp2515_reset(){
    PORTB &= ~(1 << CAN_CS); // Select CAN - controller
    spi_write_char(MCP_RESET);   //Write reset bit to SPI
    PORTB |= (1 << CAN_CS); // Deselect CAN - controller
}

void mcp2515_write(uint8_t address, uint8_t data){
    PORTB &= ~(1 << CAN_CS); // Select CAN - controller
    spi_write_char(MCP_WRITE); // Send write instruction
    spi_write_char(address); // Send address
    spi_write_char(data); // Send data
    PORTB |= (1 << CAN_CS); // Deselect CAN - controller
}

void mcp2515_request_to_send(){
    PORTB &= ~(1 << CAN_CS); // Select CAN - controller
    spi_write_char(MCP_RTS_ALL);   //Write RTS bit to SPI
        //IKKE FERDIG

    
}