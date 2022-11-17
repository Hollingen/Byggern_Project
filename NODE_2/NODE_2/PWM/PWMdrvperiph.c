#include "PWMdrvperiph.h"

#define PWM_center_val 12141
#define PWM_range_val 350
#define PWM_period_val 13125


void PWM_init()
{
    //MCLK    PERIOD     PRESCALER     CHANNEL
    //84MHz   20ms       128           5
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;                                      // Enabling peripheral clock for PWM
	PIOC->PIO_PDR |= PIO_PDR_P19;                                           // Set PWM pin to an output
	PIOC->PIO_ABSR |= PIO_ABSR_P19;                                         // Enable peripheral B for P19
	
	
	PWM->PWM_CH_NUM[5].PWM_CMR |= PWM_CMR_CPRE_MCK_DIV_128;           // Prescales MCLK with 128
	uint32_t CPRD = PWM_period_val;                                                  //CPRD = (84MHz*20ms)/128
	uint32_t CDTY = PWM_center_val;
	PWM->PWM_CH_NUM[5].PWM_CPRD |= PWM_CPRD_CPRD(CPRD);               //Set period to 20ms
	
	PWM->PWM_CH_NUM[5].PWM_CDTY |= PWM_CDTY_CDTY(CDTY); //Set duty cycle to 1.5 ms 
	
	PWM->PWM_ENA |= PWM_ENA_CHID5;                                          //Enables PWM channel 0 

}

uint32_t PWM_set_period_percentage(int16_t value)
{
	
	
	if (value > 100) {
		value = 100;
	} else if (value < -100) {
		value = -100;
	}
		
	uint32_t pwm_value =  PWM_center_val - (value * PWM_range_val)/100;
	
	PWM->PWM_CH_NUM[5].PWM_CDTYUPD = (pwm_value);
	return pwm_value;
}