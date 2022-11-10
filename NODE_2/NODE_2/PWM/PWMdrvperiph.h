#ifndef PWMDRVPERIPH_H_
#define PWMDRVPERIPH_H_

#include "sam.h"
#include "sam3x8e.h"
//#include <avr/io.h>
//#include <stdio.h>
//#include <avr/interrupt.h> 



void PWM_init(void);
uint32_t PWM_set_period_percentage(int16_t value);

#endif