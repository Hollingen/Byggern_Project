#include "MENUdrv.h"
#include "OLEDdrv.h"
#include <stdlib.h>
#include <util/delay.h>
#include <avr/pgmspace.h>






const char text_main_menu[] PROGMEM = "Main menu";
const char text_play[] PROGMEM = "Play :)";
const char text_settings[] PROGMEM = "Settings";
const char text_highscores[] PROGMEM = "Highscores";
const char text_placeholder1[] PROGMEM = "placeholder1";
const char text_placeholder2[] PROGMEM = "placeholder2";
const char text_placeholder3[] PROGMEM = "placeholder3";
const char text_placeholder4[] PROGMEM = "placeholder4";
const char text_quit[] PROGMEM = "Quit";

//Add strings to use in game. Update PROGMEM according to 
const char *const menu_main_strings[] PROGMEM = {
    text_main_menu,
    text_play,
    text_settings,
    text_highscores,
    text_placeholder1,
    text_placeholder2,
    text_placeholder3,
    text_placeholder4,
    text_quit
};


//Have to use this to copy the value from memory into the program
// strcpy_P(buffer, (char *)pgm_read_word(&(menu_main_strings[i])));
//It will be copied into this buffer
char buffer[15];  //15 is the max length of chars on the screen to avoid scrolling
                  //The screen is really 16 but we use on space on the front for - to indicate where we are

uint8_t menu_main_counter = 0;
uint8_t menu_children_counter = 0;


void menu_print_screen(uint8_t menu_main_counter, uint8_t menu_children_counter){
    oled_reset();
    oled_home();
    oled_print_char("-");
    for (int i = 0; i < 8; i++){
        oled_goto_pos(i, 8);
        strcpy_P(buffer, (char *)pgm_read_word(&(menu_main_strings[i])));
        oled_print(buffer);
    }

}








