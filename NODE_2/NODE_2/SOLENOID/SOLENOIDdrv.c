#include "SOLENOIDdrv.h"

void solenoid_init(){
    //Enable IO
    PIOA->PIO_PER  |= PIO_PA16;
    //Set pin A0 as output
    PIOA->PIO_OER  |= PIO_PA16;
    //Disable pull up
    PIOA->PIO_PUDR |= PIO_PA16;
    //Set pin low
    PIOA->PIO_SODR |= PIO_PA16;
}

void solenoid_pulse(){
	//Setting and resetting pin for solenoid, with an ideal delay inbetween
    PIOA->PIO_CODR |= PIO_PA16;
    //Need timer inbetween
    delay_us(15000);
    PIOA->PIO_SODR |= PIO_PA16;
}