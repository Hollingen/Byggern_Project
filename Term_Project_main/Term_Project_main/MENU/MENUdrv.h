#ifndef MENUDRV_H_
#define MENUDRV_H_

#include "../OLED/OLEDdrv.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include "../ADC/ADCdrv.h"

const char text_main_menu[] PROGMEM = "Main menu";
const char text_play[] PROGMEM = "Play :)";
const char text_settings[] PROGMEM = "Settings";
const char text_highscores[] PROGMEM = "Highscores";
const char text_placeholder1[] PROGMEM = "placeholder1";
const char text_placeholder2[] PROGMEM = "placeholder2";
const char text_placeholder3[] PROGMEM = "placeholder3";
const char text_placeholder4[] PROGMEM = "placeholder4";
const char text_quit[] PROGMEM = "Quit";

void menu_print_screen(uint8_t menu_main_counter, uint8_t menu_children_counter);
void menu_main_scroll_logic(uint8_t number_of_strings, uint8_t menu_main_counter);
void oled_refresh_rate_init(void);

#endif // MENUDRV_H_