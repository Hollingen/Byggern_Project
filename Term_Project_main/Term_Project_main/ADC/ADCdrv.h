#ifndef ADCDRV_H_
#define ADCDRV_H_

#define F_CPU 4915200UL
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// ADDRESS FOR ADC MEMORY SPACE
#define ADC_ADDRESS 0x1400
#define ADC_ADDRESS_SPACE 0x0400

// CHANNELS
#define x_axis_ch 0
#define y_axis_ch  1
#define left_slider_ch 2
#define right_slider_ch 3 

// USEFUL DEFINITIONS
#define ADC_MAX_VALUE 255
#define ADC_THRESHHOLD 4

typedef enum{
	NEUTRAL,
	UP,
	DOWN,
	LEFT,
	RIGHT
} adc_dir;

typedef struct{
	int8_t X;
	int8_t Y;
} adc_pos;

typedef struct{
	uint8_t X;
	uint8_t Y;
} adc_offset;


void ADC_Init(void);
uint8_t ADC_read(uint8_t channel);
void ADC_calibrate(void);
void int_Init(void);
adc_pos adc_get_pos(void);
adc_dir adc_get_dir(adc_pos pos);


#endif //__ADCDRV__