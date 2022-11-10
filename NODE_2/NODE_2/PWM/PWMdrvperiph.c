void PWM_setup() {
  // PWM Set-up on pin: DAC1
  PMC_PCER1 |= PMC_PCER1_PID36;                     // Enable PWM 
  PIOB_ABSR |= PIO_ABSR_P18;
  PIOB_ABSR |= PIO_ABSR_P19;                        // Set PWM pin perhipheral type A or B, in this case B
  PIOB_PDR |= PIO_PDR_P18; 
  PIOB_PDR |= PIO_PDR_P19;                          // Set PWM pin to an output
  PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(1);      // Set the PWM clock rate to 84MHz (84MHz/1) 
  PWM_CMR0 = PWM_CMR_CPRE_CLKA;                     // Enable single slope PWM and set the clock source as CLKA
  PWM_CPRD0 = 2100;                                  // Set the PWM frequency 84MHz/40kHz = 2100 
  PWM_CDTY0 = 1050;                                  // Set the PWM duty cycle 50% (2100/2=1050)
  PWM_ENA = PWM_ENA_CHID0;                          // Enable the PWM channel     
}
void PWM_init_periph(){
    PMC->PMC_PCER1 |= PMC_PCER1_PID36;                      // Enable peripheral TC6 (TC2 Channel 0)
    PIOC->PIO_ABSR |= PIO_ABSR_P18 | PIO_ABSR_P19;          // Switch the multiplexer to peripheral B for TIOA6 and TIOB6
    PIOC->PIO_PDR |= PIO_PDR_P18 | PIO_PDR_P19; 
    TC2->TC_CHANNEL[0].TC_CMR = TC_CMR_BCPC_SET |           // Set TIOB on counter match with RC0
                            TC_CMR_ACPC_SET |           // Set TIOA on counter match with RC0
                            TC_CMR_BCPB_CLEAR |         // Clear TIOB on counter match with RB0
                            TC_CMR_ACPA_CLEAR |         // Clear TIOA on counter match with RA0
                            TC_CMR_WAVE |               // Enable wave mode
                            TC_CMR_WAVSEL_UP_RC |       // Count up with automatic trigger on RC compare
                            TC_CMR_EEVT_XC0 |           // Set event selection to XC0 to make TIOB an output
                            TC_CMR_TCCLKS_TIMER_CLOCK1; // Set the timer clock to TCLK1 (MCK/2 = 84MHz/2 = 42MHz)

    NVIC_SetPriority(TC6_IRQn, 0);    // Set the Nested Vector Interrupt Controller (NVIC) priority for TC6 to 0 (highest) 
    NVIC_EnableIRQ(TC6_IRQn);         // Connect TC6 to Nested Vector Interrupt Controller (NVIC)

    TC2->TC_CHANNEL[0].TC_RA = 5250;                        // Load the RA0 register
    TC2->TC_CHANNEL[0].TC_RB = 5250;                        // Load the RB0 register
    TC2->TC_CHANNEL[0].TC_RC = 10500;                       // Load the RC0 register
    TC2->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG | TC_CCR_CLKEN; // Enable the timer TC6
    
}

void TC6_Handler()                                         // ISR TC6 (TC2 Channel 0)
{
  if (TC2->TC_CHANNEL[0].TC_SR & TC_SR_CPCS)               // Check for RC compare condition
  {
    // Add you code here...
  }
}