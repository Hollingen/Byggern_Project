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
#include "PWM/PWMdrvperiph.h"
#include "SOLENOID/SOLENOIDdrv.h"


#define can_br 0x290165

int main(void)
{
    /* Initialize the SAM system */
	
    SystemInit();
	//PWM_init();
	can_init_def_tx_rx_mb(can_br);
	configure_uart();
	WDT->WDT_MR = WDT_MR_WDDIS;
	CAN_MESSAGE meld; 
	
	CAN0_Handler();
	solenoid_init();
	PWM_init();
	PWM_set_period_percentage(100);
	ADC2_init();
	
	//can_receive(&meld, 0);
	//printf("%d", meld.data[0]);
    /* Replace with your application code */
    while (1) {
		
		/*meld = get_msg();
		PWM_set_period_percentage(meld.data[0]);
		printf("%d\n\r", meld.data[0]);*/
		//Setting and resetting pin for solenoid, with an ideal delay inbetween
		
		uint16_t ir = ADC2_read();
		//delay_ch1_micro(12000);
		printf("%d\n\r", ir);
		for(int i=0; i<12500000; i++){
		}
		
		/*
		PIOA->PIO_SODR = PIO_PA16;
		//delay_ch1_micro(12000);
		
		for(int i=0; i<22500000; i++){
		}
		PIOA->PIO_CODR = PIO_PA16;
		for(int i=0; i<22500000; i++){
		}*/
		//printf("%d\n\r", meld.id);
		//CAN0_Handler();
		
		//PWM_set_period_percentage(-100);
		//CAN0_Handler();
		/*for(int i = 0; i < 100; i++){
			PWM_set_period_percentage(i);
		}*/
		
		
    }
}
