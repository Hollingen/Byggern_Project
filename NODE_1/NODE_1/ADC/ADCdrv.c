#include "ADCdrv.h"

adc_offset offset;

uint8_t BUSY_flag = 0;

void ADC_Init(void){

    TCCR1A = (1<<COM1A1)|(1<<WGM11);  // Clear OCnA/OCnB on Compare Match, set OCnA/OCnB at TOP.
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10);   // Fast PWM, TOP=ICRn, Update OCRnx on TOP. // Prescaler = 1
	ICR1 = 5;
	OCR1A = 2;  // 50% Duty Cycle, ~0,8Mhz
	DDRB &= ~(1<<PB2);
	PORTB |= (1<<PB2);
	//SFIOR &= ~(1<<PUD);
	
	DDRD |= (1<<PD5);

}

uint8_t ADC_read(uint8_t channel){
	
	volatile *adc_in = (char *) ADC_ADDRESS;
	
	uint8_t data_x, data_y, data_ls, data_rs;
	
	adc_in[0] = 0x00;
	
	//sei();

	GICR |= (1<<INT0);
	while(!BUSY_flag){};
	GICR &= ~(1<<INT0);
	
	//cli();
	
	data_x = XMEM_read(0x400);
	data_y = XMEM_read(0x400);
	data_ls = XMEM_read(0x400);
	data_rs = XMEM_read(0x400);
	
	switch (channel){
		case 0:
			return data_x;
			break;
		case 1:
			return data_y;
			break;
		case 2:
			return data_ls;
			break;
		case 3:
			return data_rs;
			break;
		default:
			break;
	}
	
}

void ADC_calibrate(void){
	offset.x = ADC_read(CHANNEL_X);
	offset.y = ADC_read(CHANNEL_Y);
	printf("x offset: %d, y offset: %d\n\r", offset.x, offset.y);
}

void Int_INIT(void){
	
    GICR |= (1<<INT0);
	
	MCUCR |= (1<<ISC00);
	MCUCR |= (1<<ISC01);
	
	
}

adc_pos adc_get_pos(){
	
	adc_pos pos;
	uint8_t adc_raw[2];

	adc_raw[0] = ADC_read(CHANNEL_X);
	adc_raw[1] = ADC_read(CHANNEL_Y);

	if (adc_raw[0] > offset.x){
		pos.x = (adc_raw[0] - offset.x)*100/(ADC_MAX_VALUE - offset.x);
	}else if(adc_raw[0] < offset.x){
		pos.x = -(offset.x - adc_raw[0])*100/offset.x;
	}

	if (adc_raw[1] > offset.y){
		pos.y = (adc_raw[1] - offset.y)*100/(ADC_MAX_VALUE - offset.y);
	}else if(adc_raw[1] < offset.y){
		pos.y = -(offset.y - adc_raw[1])*100/offset.y;
	}

	return pos;

}

adc_dir adc_get_dir(adc_pos pos){

	if(abs(pos.y) >= ADC_THRESHHOLD){
		if(pos.y >= ADC_THRESHHOLD){
			return UP;
		}else if(pos.y <= (-ADC_THRESHHOLD)){
			return DOWN;
		}
	}else if(abs(pos.x) >= ADC_THRESHHOLD){
		if(pos.x >= ADC_THRESHHOLD){
			return RIGHT;
		}else if(pos.x <= (-ADC_THRESHHOLD)){
			return LEFT;
		}
	}else{
		return NEUTRAL;
	}
}

uint8_t check_js_button(){
    if(!(PINB & (1<<PB2))) {
		return 1;
		while(!(PINB & (1<<PB2))){}
    }else{
		return 0;
	}
}

ISR(INT0_vect){
    BUSY_flag = 1;
}
