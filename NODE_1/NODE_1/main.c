/*
 * Term_Project_main.c
 *
 * Created: 27.09.2022 19:34:22
 * Author : Espen
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
//#include "MENU/MENUdrv.h"
#include "CAN/CANdrv.h"

int main(void)
{
	USART_Init(MYUBRR);
	XMEM_init();
	//Int_INIT();
	ADC_Init();
	oled_init();
	//spi_init_master();
	//mcp2515_init();

	//printf("her\n\r");
	//spi_init_master();
	//oled_refresh_rate_init();
	

 	/*//LAB 3
	ADC_calibrate();
	adc_pos pos;
	adc_dir dir; */

	//LAB 4
	//oled_refresh_rate_init();
	
	
	//LAB 5
	mcp2515_init();
	can_msg melding;
	melding = can_handle_msg(0, 3, "Hei");
	//printf("length: %d\n\r", melding.data_len);
	//melding = can_recieve_msg(BUFFER0);*/
	sei();	

	/* oled_reset();
	ADC_calibrate();*/ 
    while (1) 
    {	
		/*//LAB 3
		pos = adc_get_pos();
		dir	= adc_get_dir(pos);
		printf("X pos: %d, Y pos: %d \n\r", pos.x, pos.y);
		printf("Dir: %d \n\r", dir);
		_delay_ms(1000); */

		/* //LAB 4
		update_menu_main_counter();
		menu_print_screen();
		_delay_ms(200);
		return_menu_pos(); */
		
		
		//LAB 5
		//can_send_msg(&melding, BUFFER0);
		//_delay_ms(400);
		//can_msg melding2 = can_recieve_msg(BUFFER0);
		//printf("%d\n\r", melding.data[0]);
		//printf("%d\n\r", melding2.data[0]);
		
		/*
		can_msg melding2 = can_recieve_msg(BUFFER0);
		printf("data0: %d\n\r", melding2.data[0]);
		printf("data1: %d\n\r", melding2.data[1]);
		printf("data2: %d\n\r", melding2.data[2]);
		
		_delay_ms(1000);
		*/
		//LAB
		
    }
}

/*
ISR(TIMER0_COMP_vect){
	
	
}*/