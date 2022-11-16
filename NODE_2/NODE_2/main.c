/*
 * NODE_2.c
 *
 * Created: 03.11.2022 10:30:16
 * Author : eirik ;)
 */ 


#include <stdio.h>
#include <stdint.h>

//#include <util/delay>
#include "sam.h"
#include "UART/uart.h"
#include "UART/printf-stdarg.h"
#include "CAN/can_interrupt.h"
#include "CAN/can_controller.h"
#include "sam3x8e.h"




#define can_br 0x290165

int main(void)
{
    /* Initialize the SAM system */
	
    SystemInit();
	//PWM_init();
	can_init_def_tx_rx_mb(can_br);
	configure_uart();
	//WTD->WTD_MR = WTD_MR_WDDIS;
	CAN_MESSAGE meld; 
    uint8_t what;
	sei();
	CAN0_Handler();
	//can_receive(&meld, 0);
	//printf("%d", meld.data[0]);
    /* Replace with your application code */
    while (1) {
		
		
		
    }
}
