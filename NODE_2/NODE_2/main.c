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
#include "MOTOR/MOTORdrv.h"
#include "TIMER/timerdrv.h"
#include "PID/PIDdrv.h"


#define can_br 0x290165

int main(void)
{
    /* Initialize the SAM system */
	
    SystemInit();
	can_init_def_tx_rx_mb(can_br);
	configure_uart();
	WDT->WDT_MR = WDT_MR_WDDIS;
	CAN_MESSAGE meld; 
	pidData_t pidData;
	
	CAN0_Handler();
	timer_init();
	PWM_init();
	PWM_set_period_percentage(100);
	ADC2_init();
	
	solenoid_init();
	motor_init();
	PID_init(3, 1, 0, (1/50),&pidData);
	//motor_encoder_init();
	
	
	//can_receive(&meld, 0);
	//printf("%d", meld.data[0]);
    /* Replace with your application code */
	uint8_t game_on = 0;
	uint8_t goal = 0;
	
	int16_t pid_output;
    while (1) {
		
		if(!game_on && !goal){
			meld = get_msg();
			uint8_t game_data = meld.data[4];
			game_on = game_data;
			if(game_on){
				printf("THE GAME IS ON!\n\r");
			}
			//printf("%d\n\r",meld.data[4]);
		}else if(game_on){
			//printf("GAME IS ON\n\r");
			meld = get_msg();
			int8_t js_data;
			uint8_t rs_data = meld.data[3];
			//printf("%d\n\r", meld.data[2]);
			solenoid_shoot(meld.data[2]);
		
			PWM_width(meld.data[0]);
			uint16_t rs = rs_map(rs_data, 1524);

			int16_t encoder_data =  motor_encoder_read();
			pid_output = PID_ctrl(rs, encoder_data, &pidData);
			/*printf("RS: %d ", rs);
			printf("Encoder Val: %d ", encoder_data);
			printf("PID value: %d\r\n", pid_output);*/
			motor_control_speed(pid_output);

			goal = IR_check_goal();
			if(goal){
				printf("GAME OVER\n\r");
			}

			delay_us(20000);
			
		}
		if(goal){
			game_on = 0;
			
		}
		/*// LAB 7
		meld = get_msg();
		uint8_t rs_data = meld.data[3];
		uint16_t rs = rs_map(rs_data, 1524);
		//printf("%d ",rs);
		
		//printf("%d\n\r", rs_data);
		int16_t encoder_data =  motor_encoder_read();
		//int16_t encoder_data_mapped = (encoder_data / 1524) * 255;
		//printf("%d\n\r", encoder_data);
		//motor_control_speed(position);
		pid_output = PID_ctrl(rs, encoder_data, &pidData);
		printf("RS: %d ", rs);
		printf("Encoder Val: %d ", encoder_data);
		printf("PID value: %d\r\n", pid_output);
		motor_control_speed(pid_output);*/
		
		/*
		/*if(abs(meld.data[0]) > 95){
			meld.data[0] = 100;
		}else{
			meld.data[0] = 50;
		}*/
		//motor_control_speed(meld.data[0]);
	
		//printf("%d %d %d\n\r", meld.data[0], meld.data[1], meld.data[2]);
		//SHOOT(meld.data[2]);
		
		/*PWM_set_period_percentage(meld.data[0]);
		printf("%d\n\r", meld.data[0]);*/
		//Setting and resetting pin for solenoid, with an ideal delay inbetween
		/*
		uint16_t ir = ADC2_read();
		
		printf("%d\n\r", ir);
		for(int i=0; i<12500000; i++){
		}*/
		
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
		/*
		for(int i = 600; i < 1500; i += 100){
			motor_control_speed(i);
			printf("%d\n\r", i);
			
			old_delay_us(1000000);
		}*/
		
		
	}
}
