#ifndef TIMERDRV_H_
#define TIMERDRV_H_


#include "sam.h"
#include "sam3x8e.h"

#define CLK_FREQ 84000000


void timer_init();
void old_delay_us(uint32_t microsec)

#endif