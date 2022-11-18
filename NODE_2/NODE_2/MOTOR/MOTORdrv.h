#ifndef MOTORDRV_H_
#define MOTORDRV_H_

#include "sam.h"
#include "sam3x8e.h"

#define DIR             PIO_PD10
#define EN              PIO_PD9
#define SEL             PIO_PD2
#define NOT_RST         PIO_PD1
#define NOT_OE          PIO_PD0
#define MIN_VALUE		900

void motor_init(void);
void motor_encoder_init(void);
uint16_t motor_encoder_read(void);
void motor_control_speed(int16_t position);
uint16_t rs_map(uint8_t rs_raw, uint16_t max_enc);




#endif