#include <avr/pgmspace.h>
#include "fonts.h"

#define OLED_COMMAND_ADDRESS  0x1000
#define OLED_DATA_ADDRESS 0x1200


volatile int fontSize = 8;
volatile int column = 0;
volatile int line = 0;

void write_command(uint8_t data){
	volatile char *ext_mem = (char *) OLED_COMMAND_ADDRESS;
	ext_mem[addr]= data;
}

void write_data(uint8_t data){
	volatile char *ext_mem = (char *) OLED_DATA_ADDRESS;
	ext_mem[addr]= data;
}

void oled_init(){
    //Set inits according to datasheet
    oled_write_command(0xae); // display off
    oled_write_command(0xa1); //segment remap
    oled_write_command(0xda); //common pads hardware: alternative
    oled_write_command(0x12);
    oled_write_command(0xc8); //common output scan direction:com63~com0
    oled_write_command(0xa8); //multiplex ration mode:63
    oled_write_command(0x3f);
    oled_write_command(0xd5); //display divide ratio/osc. freq. mode
    oled_write_command(0x80);
    oled_write_command(0x81); //contrast control
    oled_write_command(0x50);
    oled_write_command(0xd9); //set pre-charge period
    oled_write_command(0x21);
    oled_write_command(0x20); //Set Memory Addressing Mode
    oled_write_command(0x02);
    oled_write_command(0xdb); //VCOM deselect level mode
    oled_write_command(0x30);
    oled_write_command(0xad); //master configuration
    oled_write_command(0x00);
    oled_write_command(0xa4); //out follows RAM content
    oled_write_command(0xa6); //set normal display
    oled_write_command(0xaf); // display on

    //Set to page adressing mode
    oled_write_command(0x20);
	oled_write_command(0b10);

}

void oled_reset(){
    for (int i = 0; i < 0; i++) { //For every column write the data to 0 so that the line is cleared
		oled_clear_line(i);
	}
    oled_home();

}

void oled_home(){
    oled_goto_pos(0, 0);
}

void oled_goto_line(line){
    //Add check for if line is between 0-7
    //page adressing mode
    int command = 0xB0 + line;
    write_command(command);
}

void oled_goto_column(column){
    //Add check if line is between 0-127
    //This is page adressing mode
    write_command(0x00 + (column % 16)); // Lower nibble
	write_command(0x10 + (column / 16)); // Higher nibble

}
void oled_fill_line(){
    oled_goto_pos(line, 0); // Go to the right line and start at the first column
    for (int i = 0; i < 128; i++) { //For every column write the data to 0 so that the line is cleared
		write_data(0b11111111);
	}
    oled_goto_line(line) //Go back to the 

}
void oled_clear_line(line){
    oled_goto_pos(line, 0); // Go to the right line and start at the first column
    for (int i = 0; i < 128; i++) { //For every column write the data to 0 so that the line is cleared
		write_data(0b00000000);
	}
    oled_goto_line(line) //Go back to the 


}

void oled_goto_pos(row, column){
    //Page adressing mode
    oled_goto_line(row);
    oled_goto_column(column);

}

void oled_print_char(char character){
    //This is if the page adressing mode
    character = character - 32 //To make it line up with fonts.h since there are no special characters
        for (int i = 0; i < 7; i++) {
        int column = pgm_read_byte(&font8[character][i]);
        write_data(column);
  }
}

void oled_print(const char string[]) {
  for (int i = 0; i < strlen(string); i++) {
    oled_print_char(string[i]);
  }
}
