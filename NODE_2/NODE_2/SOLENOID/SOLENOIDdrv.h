#ifndef SOLENOIDDRV_H_
#define SOLENOIDDRV_H_

#include "sam.h"
#include "sam3x8e.h"
#include "../TIMER/TIMERdrv.h"

void solenoid_init(void);
void solenoid_pulse(void);
void solenoid_shoot(uint8_t js_button);


#endif