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

    if(mcp2515_brp_init() < 0){
        return -2;
    }
	
    can_interrupt_en();
	
	mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	mcp2515_read(MCP_CANSTAT, &value);
	printf("value: %d\n\r", value);
	if ((value & MODE_MASK) != MODE_NORMAL) {
        printf ("MCP2515 is NOT in config mode after reset !\n\r");
		return 1;
    }

    return 0;
}

void can_interrupt_en(){
	
    // making pd3 input
    DDRD &= ~(1<<PD3);
    // Enablign external interrupt on MCU on INT1
    GICR |= (1<<INT1);
	
	MCUCR |= (1<<ISC01);
	MCUCR |= (1<<ISC11);

}

uint8_t mcp2515_brp_init(){

    // SJW<2:0> = 0b000 (0)-> 1 * Tq
    // BRP<5:0> = 0b00100 (4) -> BRP * Tosc
    mcp2515_bit_modify(MCP_CNF1, MCP_CNF1_MASK, MCP_CNF1_VAL);
    value = mcp2515_read(MCP_CNF1);
	//printf("value: %d\n\r", value);
    if ((value & MCP_CNF1_MASK) != MCP_CNF1_VAL) {
        printf ("Wrong CNF1 value !\n\r");
		return -1;
    }

    // PHSEG1<5:3> = 0b110 (6) -> PS1 = (PHSEG + 1) * Tq
    // PHSEG2<2:0> = 0b001 (1) -> Progseg = (PHSEG2 + 1) * Tq
    mcp2515_bit_modify(MCP_CNF2, MCP_CNF2_MASK, MCP_CNF2_VAL);
    value = mcp2515_read(MCP_CNF1);
	//printf("value: %d\n\r", value);
    if ((value & MCP_CNF1_MASK) != MCP_CNF1_VAL) {
        printf ("Wrong CNF2 value !\n\r");
		return -1;
    }
    
    // PHSEG2<2:0> = 0b101 (5) -> PS2 = (PHSEG2 + 1) * Tq
    mcp2515_bit_modify(MCP_CNF3, MCP_CNF3_MASK, MCP_CNF3_VAL);
    value = mcp2515_read(MCP_CNF1);
	//printf("value: %d\n\r", value);
    if ((value & MCP_CNF1_MASK) != MCP_CNF1_VAL) {
        printf ("Wrong CNF3 value !\n\r");
		return -1;
    }

    return 0;
}


uint8_t mcp2515_read(uint8_t address, uint8_t *value){

    PORTB &= ~(1 << PB4); // Select CAN - controller

    spi_write_char(MCP_READ); // Send read instruction
    spi_write_char(address); // Send address
	
    value = spi_read_char() ; // Read result
    
	PORTB |= (1 << PB4); // Deselect CAN - controller
	//*value = result;
}

void mcp2515_reset(){
    PORTB &= ~(1 << PB4); // Select CAN - controller
    spi_write_char(MCP_RESET);   //Write reset bit to SPI
    PORTB |= (1 << PB4); // Deselect CAN - controller
}

void mcp2515_write(uint8_t address, uint8_t data){
    PORTB &= ~(1 << PB4); // Select CAN - controller
    spi_write_char(MCP_WRITE); // Send write instruction
    spi_write_char(address); // Send address
    spi_write_char(data); // Send data
    PORTB |= (1 << PB4); // Deselect CAN - controller
}

void mcp2515_request_to_send(uint8_t buffer){
    PORTB &= ~(1 << PB4); // Select CAN - controller
    //spi_write_char(MCP_RTS_ALL);   Write RTS bit to SPI
    spi_write_char(buffer);
    PORTB |= (1 << PB4); // Deselect CAN - controller
}

uint8_t mcp2515_read_status(){
    uint8_t status;
    PORTB &= ~(1 << PB4); // Select CAN - controller
    spi_write_char(MCP_READ_STATUS);   //Write read_status bit to SPI
    status = spi_read_char();
	PORTB |= (1 << PB4); // Deselect CAN - controller

    return status;

}

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
    PORTB &= ~(1 << DD_SS); // Select CAN - controller
    spi_write_char(MCP_BITMOD);   //Write read_status bit to SPI
    spi_write_char(address); // Send address
    spi_write_char(mask); // Send mask
    spi_write_char(data); // Send data
    PORTB |= (1 << DD_SS); // Deselect CAN - controller
}

