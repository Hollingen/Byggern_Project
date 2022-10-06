#ifndef OLEDDRV_H_
#define OLEDDRV_H_

#include <avr/pgmspace.h>
#include <string.h>

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#define OLED_COMMAND_ADDRESS  0x1000
#define OLED_DATA_ADDRESS 0x1200

void oled_write_command(uint8_t data);
void oled_write_data(uint8_t data);
void oled_init(void);
void oled_reset(void);
void oled_home(void);
void oled_goto_line(int line);
void oled_goto_column(int column);
void oled_fill_line(int line);
void oled_clear_line(int line);
void oled_goto_pos(int row, int column);
void oled_print_char(char character);
void oled_print(const char string[]);

#endif //OLEDDRV_H_