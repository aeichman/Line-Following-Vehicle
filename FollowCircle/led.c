//------------------------------------------------------------------------------
//
//  Description:
//
//  Adam Eichman
//  Jan 2024
//  Built with Code Composer Version: CCS12.6.0.00007_win64
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include  "macros.h"

extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
extern volatile unsigned char display_changed;




void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P6OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}

void Carlson_StateMachine(void){
    switch(Time_Sequence){
      case 250:                        //
        if(one_time){
          Init_LEDs();
          lcd_BIG_mid();
          display_changed = 1;
          one_time = 0;
        }
        Time_Sequence = 0;             //
        break;
      case 200:                        //
        if(one_time){
//          P1OUT &= ~RED_LED;            // Change State of LED 4
          P6OUT |= GRN_LED;            // Change State of LED 5
          one_time = 0;
        }
        break;
      case 150:                         //
        if(one_time){
          P1OUT |= RED_LED;            // Change State of LED 4
          P6OUT &= ~GRN_LED;            // Change State of LED 5
          one_time = 0;
        }
        break;
      case 100:                         //
        if(one_time){
//          lcd_4line();
          lcd_BIG_bot();
          P6OUT |= GRN_LED;            // Change State of LED 5
          display_changed = 1;
          one_time = 0;
        }
        break;
      case  50:                        //
        if(one_time){
          one_time = 0;
        }
        break;                         //
      default: break;
    }
}
