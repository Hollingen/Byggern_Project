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

int main(void)
{
	USART_Init(MYUBRR);
	XMEM_init();
	ADC_Init();
    /* Replace with your application code */
    while (1) 
    {
    }
}

