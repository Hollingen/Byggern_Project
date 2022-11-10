/*
 * NODE_2.c
 *
 * Created: 03.11.2022 10:30:16
 * Author : eirik ;)
 */ 


#include <stdio.h>
#include "sam.h"
#include "CAN/can_interrupt.h"

#define can_br 0x290165

int main(void)
{
    /* Initialize the SAM system */
	
    SystemInit();
	//PWM_init();
	configure_uart();
    uint8_t check = can_init_def_tx_rx_mb(can_br);
    if(check != 0){
		printf("nei\n\r");
    }
   

    /* Replace with your application code */
    while (1) 
    {
    }
}
