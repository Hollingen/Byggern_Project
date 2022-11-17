#include "MOTORdrv.h"



void motor_init(){
    //PIOD output motor
    //PIOC input encoder
    PMC->PMC_PCER0 |= PMC_PCER0_PID13;
    PIOD->PIO_PER |= DIR | EN | NOT_OE | NOT_RST | SEL;  

	PIOD->PIO_OER |= DIR | EN | NOT_OE | NOT_RST | SEL;


        //Set channel
    DACC->DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;
    DACC->DACC_MR |= DACC_MR_STARTUP_8;
    
    DACC->DACC_CHER |= DACC_CHER_CH1;
    DACC->DACC_TRGEN   |= DACC_MR_TRGEN_DIS;

}

int16_t motor_encoder_read() {

	int16_t encoder_value_low = 0;
	int16_t encoder_value_high = 0;
	int16_t encoder_value = 0;
	uint16_t mapped_encoder_value;
    PIOB->PIO_CODR = NOT_OE;
    PIOB->POI_CODR = SEL;

    //Delay 20 usec
    
    uint32_t PIOC_PIN_DATA = PIOC->PIO_PDSR;

    encoder_value_high =  (PIOC_PIN_DATA & (0x1FE));

    PIOD->PIO_SODR = SEL;
    //delay 20 usec

    uint32_t PIOC_PIN_DATA1 = PIOC->PIO_PDSR;
    encoder_value_low = (PIOC_PIN_DATA & (0x1FE));

    PIOB->PIO_SODR = NOT_OE;

    uint16_t encoder_value = (encoder_value_high << 7) | encoder_value_low;

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

    int32_t DACC_value = abs(direction_value*DACC_RANGE/1405) + DACC_MIN_VALUE;
    if (position > 0){
        PIOD->PIO_SODR = DIR;
        PIOD->PIO_PER |= EN;
    }
    else if (position < 0) {
        PIOD->PIO_CODR = DIR;        
        PIOD->PIO_PER |= EN;
    }
    else{PIOD->PIO_PDR |= EN;;}


    DACC->DACC_CDR = position;
    for (int i = 0; i>1000000; i++);

    
}
