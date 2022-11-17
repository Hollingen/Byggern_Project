#ifndef MOTORDRV_H_
#define MOTORDRV_H_

#include "sam.h"
#include "sam3x8e.h"

#define DIR             PIO_PD10
#define EN              PIO_PD9
#define SEL             PIO_PD2
#define NOT_RST         PIO_PD1
#define NOT_OE          PIO_PD0

void motor_init(void);
void motor_encoder_init(void);
int16_t motor_encoder_read(void);
void motor_control_speed(int8_t position);




#endif