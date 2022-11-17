#include "TIMERdrv.h"

void timer_init(){
    //Enable TC clock TC0
    
    PMC->PMC_PCER0 |= PMC_PCER0_PID27;
    //Enable ch 0
    TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKEN;
    //Rising edge
    //TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_CPCTRG;
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG;



}

void old_delay_us(uint32_t microsec){
    //Reset counter
    //uint32_t now_time;
    uint32_t hvorfor = TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG;
    //Read counter value
    //0.000001 / (1/84MHz) / 2 = num of microsec per count
    uint32_t now_time = TC0->TC_CHANNEL[0].TC_CV;
	uint32_t prev_time = now_time;
    while((now_time - prev_time) < (microsec*42)){
        now_time = TC0->TC_CHANNEL[0].TC_CV;
    }
}