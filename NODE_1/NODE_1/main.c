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
	Int_INIT();
	ADC_Init();
	oled_init();


	//printf("her\n\r");
	//spi_init_master();
	//oled_refresh_rate_init();
	
	//ADC_calibrate();
	adc_pos pos;
	adc_dir dir;

	//LAB 5
	mcp2515_init();
	sei();
	can_msg melding;
		
	uint8_t game_on = 0;
	ADC_calibrate();
	//menu_print_screen();
    while (1) 
    {	
		
		//THE GAME
		if(game_on == 0){
			update_menu_main_counter();
			menu_print_screen();
			_delay_ms(200);
			uint8_t menu = return_menu_pos();
			if(menu == 1){
				game_on = 1;
				printf("GAME IS ON\n\r");
			}
			//printf("%d", menu);
		}else if(game_on){
			
			pos = adc_get_pos();
			uint8_t rs_data = ADC_read(CHANNEL_RS);
			
			dir	= adc_get_dir(pos);
			//printf("X pos: %d, Y pos: %d \n\r", pos.x, pos.y);
			//printf("Dir: %d \n\r", dir);
			signed char m[8] = {pos.x, pos.y, check_js_button(), rs_data, game_on};
			melding = can_handle_msg(0, 5, m);
			can_send_msg(&melding, BUFFER0);
			_delay_ms(10);
			
		}
		/*
		pos = adc_get_pos();
		uint8_t rs_data = ADC_read(CHANNEL_RS);
		
		dir	= adc_get_dir(pos);
		printf("X pos: %d, Y pos: %d \n\r", pos.x, pos.y);
		printf("Dir: %d \n\r", dir);
		signed char m[8] = {pos.x, pos.y, check_js_button(), rs_data};
		melding = can_handle_msg(0, 4, m);
		can_send_msg(&melding, BUFFER0);
		_delay_ms(10); */

		/* //LAB 4
		 */
		
		
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