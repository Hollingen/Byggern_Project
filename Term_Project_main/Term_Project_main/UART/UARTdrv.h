#ifndef __UARTDRV__
#define __UARTDRV__

#define FOSC 4915200UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_Init(unsigned int ubrr);


#endif //__UARTDRV__