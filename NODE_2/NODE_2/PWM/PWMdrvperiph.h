#ifndef PWMDRVPERIPH_H_
#define PWMDRVPERIPH_H_

#include "sam.h"
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h> 


void PWM_setup(void);
void PWM_init_periph(void);
void TC6_Handler(void);

#endif