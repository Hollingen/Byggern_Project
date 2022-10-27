#ifndef UARTDRV_H_
#define UARTDRV_H_

#include <avr/io.h>
#include <stdio.h>

#define FOSC 4915200UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_Init(unsigned int ubrr);


#endif //__UARTDRV__