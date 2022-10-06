/*
 * Term_Project_main.c
 *
 * Created: 27.09.2022 19:34:22
 * Author : eirik
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "UART/UARTdrv.h"
#include "SRAM/SRAMdrv.h"
#include "ADC/ADCdrv.h"
#include "OLED/OLEDdrv.h"

int main(void)
{
	USART_Init(MYUBRR);
	XMEM_init();
	Int_INIT();
	ADC_Init();
	oled_init();
    /* Replace with your application code */
	
	//TESTE OLED;
	oled_reset();
	oled_home();
	oled_print_char('t');
    while (1) 
    {
		oled_fill_line(1);
		_delay_ms(1000);
		oled_clear_line(1);
        _delay_ms(1000);
    }
}

