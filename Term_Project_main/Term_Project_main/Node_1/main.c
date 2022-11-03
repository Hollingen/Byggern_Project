/*
 * Term_Project_main.c
 *
 * Created: 27.09.2022 19:34:22
 * Author : eirik
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "NODE1/UART/UARTdrv.h"
#include "NODE1/SRAM/SRAMdrv.h"
#include "NODE1/ADC/ADCdrv.h"
#include "NODE1/OLED/OLEDdrv.h"
#include "NODE1/SPI/SPIdrv.h"
#include "NODE1/MCP2515/MCP2515drv.h"

int main(void)
{
	USART_Init(MYUBRR);
	XMEM_init();
	//Int_INIT();
	ADC_Init();
	oled_init();
	spi_init_master();
	//mcp2515_init();

	//printf("her\n\r");
	//spi_init_master();
	//oled_refresh_rate_init();
	//sei();	
	
	printf("men ikke her\n\r");
    /* Replace with your application code */
	
	//TESTE OLED;
	//oled_reset();
	//oled_home();
	//oled_print_char('t');

	ADC_calibrate();
	//oled_home();
	//oled_print("kisen,1234567891");
	adc_pos pos;
	adc_dir dir;
    while (1) 
    {	
		spi_write_char(0xFF);
		
		//_delay_ms(1000);
		//DDRB &= ~(1 << PB4);

		//spi_write_char(MCP_CNF1);
		//spi_write_char(0xAA);
		//DDRB |= (1 << PB4);
		//_delay_ms(10);
		//DDRB &= ~(1 << PB4);
		//value = spi_read_char();
		//spi_write_char(MCP_READ); // Send read instruction
		//spi_write_char(MCP_CNF1); // Send address
		 
		//value = spi_read_char() ; // Read result
		//mcp2515_write(MCP_CNF1, 0xAA);
		//printf("value: %d\n\r", value);
		//DDRB |= (1 << PB4);
		//'_delay_ms(100);
		//spi_write_char('a');
		//pos = adc_get_pos();
		//dir = adc_get_dir(pos);
		//mcp2515_init();
		//printf("Positions X: %d%%  Y: %d%%\n\r", pos.x, pos.y);
		//printf("Direction: %d\n\r", dir);
		_delay_ms(1000);
		//spi_read_char();'
		update_menu_main_counter();
		menu_print_screen();
		
    }
}

/*
ISR(TIMER0_COMP_vect){
	
	
}*/