#include "ADCdrv2.h"


#define IR_THRESHOLD 500

static uint32_t IR_prev_value, IR_value;
static uint8_t goal_counter = 0;
uint8_t IR_goal = 0;


void ADC2_init(){

    // SEting the peropheral clock
    PMC->PMC_PCER1 |= PMC_PCER1_PID37;

    // Setting FREERUN mode, no trigger neeeded
    // Starts a new conversion when it's done
    ADC->ADC_MR = ADC_MR_FREERUN;

    // Choosing channel 4
    // a.k.a PA22 a.k.a AD3
    ADC->ADC_CHER = ADC_CHER_CH4;

    // Starting the ADC conversion
    //ADC->ADC_CR = ADC_CR_START;
    
}

uint16_t ADC2_read(){
    // Reading from channel 0
    uint16_t readings = ADC->ADC_CDR[4];

    return readings;
}


uint8_t IR_check_goal(){
    uint16_t IR_value = ADC2_read();
    if((IR_value < IR_THRESHOLD) && (IR_prev_value >= IR_THRESHOLD) && !IR_goal) {
		IR_prev_value = IR_value;
		IR_goal = 1;
		return 1;
	} else {
		IR_prev_value = IR_value;
		return 0;
	}
}

void IR_reset()
{
	IR_goal = 0;
    
}



