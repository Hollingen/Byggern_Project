#include "ADCdrv.h"


uint8_t neutral_data_x = 0;
uint8_t neutral_data_y = 0;
uint8_t right_data = 0;
uint8_t left_data = 0;
uint8_t up_data = 0;
uint8_t down_data = 0;

uint8_t BUSY_flag = 0;

typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT,
} adc_dir;

void ADC_Init(void){

    TCCR1A = (1<<COM1A1)|(1<<WGM11);  // Clear OCnA/OCnB on Compare Match, set OCnA/OCnB at TOP.
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10);   // Fast PWM, TOP=ICRn, Update OCRnx on TOP. // Prescaler = 1
	ICR1 = 5;
	OCR1A = 2;  // 50% Duty Cycle, ~0,8Mhz
	
	DDRD |= (1<<PD5);

}

uint8_t ADC_read(uint8_t channel){
	
	volatile *adc_in = (char *) ADC_ADDRESS;
	
	uint8_t test0, test1, test2, test3;
	
	adc_in[0] = 0x00;
	
	sei();
	while(!BUSY_flag){};
	cli();
	
	test0 = XMEM_read(0x400);
	test1 = XMEM_read(0x400);
	test2 = XMEM_read(0x400);
	test3 = XMEM_read(0x400);
	
	switch (channel){
		case 0:
			return test0;
			break;
		case 1:
			return test1;
			break;
		case 2:
			return test2;
			break;
		case 3:
			return test3;
			break;
		default:
			break;
	}
	
}

void ADC_calibrate(void){
	neutral_data_x = ADC_read(x_axis_ch);
	neutral_data_y = ADC_read(y_axis_ch);
	printf("x offset: %d, y offset: %d\n\r", neutral_data_x, neutral_data_y);
}

void Int_INIT(void){
	
    GICR |= (1<<INT0);
	
	MCUCR |= (1<<ISC00);
	MCUCR |= (1<<ISC01);
	
	sei();
}



ISR(INT0_vect){
    BUSY_flag = 1;
}
