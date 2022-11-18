#include "SOLENOIDdrv.h"
#include "../TIMER/timerdrv.h"
static uint8_t already_shot = 0;
void solenoid_init(){
    //Enable IO
    PIOA->PIO_PER  |= PIO_PA16;
    //Set pin A0 as output
    PIOA->PIO_OER  |= PIO_PA16;
    //Set pin low
    PIOA->PIO_CODR |= PIO_PA16;
}

void solenoid_pulse(){
	//SEtting and clearing pin A0 to "shoot" the solenoid
    PIOA->PIO_SODR |= PIO_PA16;
    //Need timer inbetween
	delay_us(20000);
    PIOA->PIO_CODR |= PIO_PA16;
}

void solenoid_shoot(uint8_t js_button){
    if(js_button && !already_shot){
        solenoid_pulse();
        already_shot = 1;
    }else if(!js_button){
        already_shot = 0;
    }
}