#include "MENUdrv.h"



#define number_of_strings 9
//Add strings to use in game. Update PROGMEM according to 
//
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
char buffer[16];  //15 is the max length of chars on the screen to avoid scrolling
                  //The screen is really 16 but we use on space on the front for - to indicate where we are

volatile uint8_t menu_main_counter = 0;
volatile uint8_t menu_children_counter = 0;


void menu_print_screen(uint8_t menu_main_counter, uint8_t menu_children_counter){
    uint8_t scroll_number = 0;
    uint8_t string_scroll_number = 0;
    uint8_t middle = 4;
    int start = 0;
    start = menu_main_counter - middle;
    if(start < 0){
        start = number_of_strings - abs(start);
    }
    string_scroll_number = start;
    
    oled_reset();
    oled_goto_pos(4, 0);
    oled_print_char('>');
    oled_home();
    for (int i = 0; i < 8; i++){
        if(string_scroll_number > 8){
            string_scroll_number = 0;
        }
        oled_goto_pos(i, 16);
        //Check to see if the counter is higher than number of elements
        strcpy_P(buffer, (char *)pgm_read_word(&(menu_main_strings[string_scroll_number])));
        oled_print(buffer);
        string_scroll_number ++;
    }

}


void menu_main_scroll_logic(uint8_t number_of_strings, uint8_t menu_main_counter){
    if(menu_main_counter > number_of_strings)
        menu_main_counter = 0;
}

void update_menu_main_counter(){
    adc_dir var = adc_get_dir(adc_get_pos());
    if(var == UP){
        menu_main_counter --;
    }
    else if (var == DOWN){
        menu_main_counter ++;
    }
    if(menu_main_counter > number_of_strings)
        menu_main_counter = 0;
}


