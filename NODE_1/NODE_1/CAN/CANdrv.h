#ifndef CANDRV_H_
#define CANDRV_H_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "../SPI/SPIdrv.h"
#include "../MCP2515/MCP2515drv.h"

struct can_msg{
    uint16_t id;
    uint8_t data_len;
    char data[8];
};

