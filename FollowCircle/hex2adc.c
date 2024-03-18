#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include  "macros.h"
#include  <stdio.h>



// globals
char thousands;
char hundreds;
char tens;
char ones;
char adc_char[4];



extern volatile unsigned char update_display;
extern char display_line[4][11];
extern char *display[4];



//-----------------------------------------------------------------
// Hex to BCD Conversion
// Convert a Hex number to a BCD for display on an LCD or monitor
//
//-----------------------------------------------------------------
void HEXtoBCD(int hex_value){
  //  int value;
    int i;
    for(i=0; i < 4; i++) {
        adc_char[i] = '0';
    }

    while (hex_value > 999){
        hex_value = hex_value - 1000;
        thousands = thousands + 1;
        adc_char[0] = 0x30 + thousands;
    }
    thousands = 0;
    while (hex_value > 99){
        hex_value = hex_value - 100;
        hundreds = hundreds + 1;
        adc_char[1] = 0x30 + hundreds;
    }
    hundreds = 0;
    while (hex_value > 9){
        hex_value = hex_value - 10;
        tens = tens + 1;
        adc_char[2] = 0x30 + tens;
    }
    tens = 0;
    adc_char[3] = 0x30 + hex_value;
}
//-----------------------------------------------------------------

//-------------------------------------------------------------
// ADC Line insert
// Take the HEX to BCD value in the array adc_char and place it
// in the desired location on the desired line of the display.
// char line => Specifies the line 1 thru 4
// char location => Is the location 0 thru 9
//
//-------------------------------------------------------------
void adc_line(char line, char location){
//-------------------------------------------------------------
     int i;
     unsigned int real_line;
     real_line = line - 1;
     for(i=0; i < 4; i++) {
         display_line[real_line][i+location] = adc_char[i];
         update_display = TRUE;
     }

}
//------------

//void displayTime( char line, char location, int num ) {
//    char num_str[7];
//    unsigned int real_line;
//    real_line = line - 1;
//
//    snprintf(num_str, sizeof(num_str), "%d", num);
//
//    int i;
//    for (i = 0; num_str[i] != '\0'; i++) {
//        display_line[real_line][i + location] = num_str[i];
//
//    }
//}

void displayTime(char line, char location, int num) {
    char num_str[7];
    unsigned int real_line;
    int i;
    real_line = line - 1;
    int seconds = num * 200 / 1000;
    int fifth_of_a_second = 2 * (((num * 200) % 1000) / 200);

    snprintf(num_str, sizeof(num_str), "%d.%d", seconds, fifth_of_a_second);

    for (i = 0; num_str[i] != '\0'; i++) {
        display_line[real_line][i + location] = num_str[i];
    }
}
