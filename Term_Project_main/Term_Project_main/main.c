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
	printf("her\n\r");
	spi_init_master();
	oled_refresh_rate_init();
	
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
		//spi_write_char('a');
		//pos = adc_get_pos();
		//dir = adc_get_dir(pos);

		//printf("Positions X: %d%%  Y: %d%%\n\r", pos.x, pos.y);
		//printf("Direction: %d\n\r", dir);
		//_delay_ms(1000);
		//spi_read_char();
		for (int i = 0; i<=9;i++){
			menu_print_screen(i,0);
			_delay_ms(2000);
		}
    }
}


ISR()