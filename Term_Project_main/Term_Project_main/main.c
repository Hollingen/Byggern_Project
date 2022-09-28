/*
 * Term_Project_main.c
 *
 * Created: 27.09.2022 19:34:22
 * Author : eirik
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "UART/UARTdrv.c"

int main(void)
{
	USART_Init(MYUBRR);
    /* Replace with your application code */
    while (1) 
    {
    }
}

