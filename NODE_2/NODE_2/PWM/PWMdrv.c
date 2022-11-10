#include <avr/io.h>

#include "PWMdrv.h"

#define SYS_CLK_FREQ		84000000

static uint16_t pwm_freq;


void PWM_init(float period_ms, unsigned long clk_freq){
	
	//Set fast PWM mode
	set_bit(TCCR1B, WGM13);
	set_bit(TCCR1B, WGM12);
	set_bit(TCCR1A, WGM11);
	clear_bit(TCCR1A, WGM10);
	
	//Set compare output on PB5 (OC1A)
	set_bit(TCCR1A, COM1A1);
	clear_bit(TCCR1A, COM1A0);

	// Set prescaler 256
	set_bit(TCCR1B, CS12);
	clear_bit(TCCR1B, CS11);
	clear_bit(TCCR1B, CS10);
	pwm_freq = (clk_freq/256);
    ICR1 = pwm_freq*period_ms - 0.5;
	// Set PB5 to output mode
	set_bit(DDRB, PB5);
    
}

void PWM_pulse(pulse_len_s){

    OCR1A = (pulse_len_s * pwm_freq) - 0.5;
}