#include "ADCdrv2.h"

void ADC2_init(){

    // Setting FREERUN mode, no trigger neeeded
    // Starts a new conversion when it's done
    ADC->ADC_MR = ADC_MR_FREERUN;
    // Choosing channel 0
    ADC->ADC_CHER = ADC_CHER_CH0;
    // Starting the ADC conversion
    ADC->ADC_CR = ADC_CR_START;
    
}

uint16_t ADC2_read(){
    // Reading from channel 0
    uint16_t readings = ADC->ADC_CDR[0];

    return readings;
}


