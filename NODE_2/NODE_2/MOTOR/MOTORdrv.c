#include "MOTORdrv.h"
#include <stdio.h>
#include <stdlib.h>
#include "..\TIMER\timerdrv.h"



void motor_init(){
    //PIOD output motor
	motor_encoder_init();
    PMC->PMC_PCER0 |= PMC_PCER0_PID13;
    PIOD->PIO_PER |= DIR | EN | NOT_OE | NOT_RST | SEL;  

	PIOD->PIO_OER |= DIR | EN | NOT_OE | NOT_RST | SEL;


        //Set channel
    PMC->PMC_PCER1 |= PMC_PCER1_PID38;
    DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
    // Enables a 8 clock cycle startup periode
    DACC->DACC_MR |= DACC_MR_STARTUP_8;
    
    DACC->DACC_CHER |= DACC_CHER_CH1;
    // DIS enables freerunning mode
    DACC->DACC_MR|= DACC_MR_TRGEN_DIS;
    // Enabling refresh rate under 20us to prevent loss of voltage
    DACC->DACC_MR |= DACC_MR_REFRESH(0x1);
    
    
    PIOD->PIO_SODR |= NOT_OE | NOT_RST;

}

void motor_encoder_init() {

    //PMC->PMC_PCER1 |= PMC_PCER1_PID38;
    PIOC->PIO_PER |= 0b111111110;
    
    
}

uint16_t motor_encoder_read() {

	uint16_t encoder_value_low = 0;
	uint16_t encoder_value_high = 0;
	uint16_t encoder_value = 0;
    PIOD->PIO_CODR = NOT_OE;
    PIOD->PIO_CODR = SEL;

    old_delay_us(20);

    uint32_t PIOC_PIN_DATA = PIOC->PIO_PDSR;

    encoder_value_high =  (PIOC_PIN_DATA & (0x1FE));

    PIOD->PIO_SODR = SEL;

    old_delay_us(20);
        

    uint32_t PIOC_PIN_DATA1 = PIOC->PIO_PDSR;
    encoder_value_low = (PIOC_PIN_DATA1 & (0x1FE));

    

    encoder_value = (encoder_value_high << 7) | encoder_value_low ;

    PIOD->PIO_SODR = NOT_OE;
	
	/*if(encoder_value > 60000){
		encoder_value = 0;
	}*/
    return encoder_value;
    
/*
1: Set !OE low, to sample and hold the encoder value
2: Set SEL low to output high byte
3: Wait approx. 20 microseconds for output to settle
4: Read MJ2 to get high byte
5: Set SEL high to output low byte
6: Wait approx. 20 microseconds
7: Read MJ2 to get low byte
8: Set !OE to high
*/
}


void motor_control_speed(int8_t position){

	int32_t DACC_value = abs(position*1000/1405) + 2000;
    if (position > 0){
        PIOD->PIO_SODR |= DIR;
        PIOD->PIO_SODR |= EN;
    }
    else if (position < 0) {
        PIOD->PIO_CODR |= DIR;        
        PIOD->PIO_SODR |= EN;
    }
    else{PIOD->PIO_CODR |= EN;;}
	//printf("%d\n\r", position);
	uint16_t test = DACC_value;
    DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
    DACC->DACC_CDR = test;
	//printf("%d\n\r", test);
    //for (int i = 0; i>100000; i++);

    
}

uint16_t rs_map(uint8_t rs_raw, uint16_t max_enc){
	uint16_t rs_mapped;
	rs_mapped = rs_raw * max_enc/255;
    //rs_mapped = abs(rs_raw-255) * max_enc/255;
	
	return rs_mapped;
}