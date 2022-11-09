#ifndef CANDRV_H_
#define CANDRV_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "../SPI/SPIdrv.h"
#include "../MCP2515/MCP2515drv.h"

typedef struct{
    uint16_t id;
    uint8_t data_len;
    char data[8];
} can_msg;

can_msg can_handle_msg(uint16_t id, uint8_t size, char msg[8]);
void can_send_msg(can_msg* msg, BUFFER buffer);
can_msg can_recieve_msg(BUFFER buffer);
void interrupt_handler(void);
