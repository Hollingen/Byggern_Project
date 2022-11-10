/*
 * Term_Project_main.c
 *
 * Created: 27.09.2022 19:34:22
 * Author : eirik
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "UART/UARTdrv.h"
#include "SRAM/SRAMdrv.h"
#include "ADC/ADCdrv.h"
#include "OLED/OLEDdrv.h"
#include "SPI/SPIdrv.h"
#include "MCP2515/MCP2515drv.h"

int main(void)
{
	USART_Init(MYUBRR);
	XMEM_init();
	Int_INIT();
	ADC_Init();
	oled_init();
	spi_init_master();
	//mcp2515_init();

	//printf("her\n\r");
	//spi_init_master();
	//oled_refresh_rate_init();
	sei();	
	

	//LAB 3
	ADC_calibrate();
	adc_pos pos;
	adc_dir dir;

	//LAB 4
	oled_refresh_rate_init();

	//LAB 5
	
    while (1) 
    {	
		//LAB 3
		pos = adc_get_pos();
		dir	= adc_get_dir(pos);
		printf("X pos: %d, X dir: %d \n\r", pos.x, dir.x);
		printf("Y pos: %d, Y dir: %d \n\r", pos.y, dir.y);
		_delay_ms(1000);

		//LAB 4
		update_menu_main_counter();
		menu_print_screen();

		//LAB 5

		//LAB
		
    }
}

/*
ISR(TIMER0_COMP_vect){
	
	
}*/