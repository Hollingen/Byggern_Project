void timer_init(){
    //Enable TC clock TC0
    
    PMC->PMC_PCER0 |= PMC_PCER0_PID27;
    //Enable ch 0
    TC0->TC_CHANNEL[0].TC_CCR |= TC_CCR_CLKEN;
    //Rising edge
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_CPCTRG;
    


}