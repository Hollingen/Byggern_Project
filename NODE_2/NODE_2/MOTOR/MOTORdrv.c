#include "MOTORdrv.h"


void motor_Init(){
    //PIOB output motor
    //PIOC input encoder
    
    PIOB->PIO_PER |= 0x607; 

    DACC->DACC_MR |= DACC_MR_REFRESH(0x1);
	DACC->DACC_MR |= DACC_MR_STARTUP_8;
    DACC->DACC_CHER |= DACC_CHER_CH0;
    DACC->DACC_TRGEN   |= DACC_MR_TRGEN_DIS;
    PIOB->PIO_OER |= 0x607;



}

int16_t encoder_Read() {

	int16_t encoder_value_low = 0;
	int16_t encoder_value_high = 0;
	int16_t encoder_value = 0;
	uint16_t mapped_encoder_value;
    PIOB->PIO_CODR = NOT_OE;
    PIOB->POI_CODR = SEL;


    uint32_t PIOC_PIN_DATA = PIOC->PIO_PDSR;

    encoder_value_high =  (PIOC_PIN_DATA & (0x1FE));

    PIOD->PIO_SODR = SEL;

    
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