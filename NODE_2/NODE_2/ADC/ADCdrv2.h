#ifndef ADCDRV2_H_
#define ADCDRV2_H_

#include "sam3x8e.h"
#include <stdio.h>
#include <stdint.h>


#include "sam.h"

void ADC2_init(void);
uint16_t ADC2_read(void);

#endif