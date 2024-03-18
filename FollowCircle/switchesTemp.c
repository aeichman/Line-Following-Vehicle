#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include  "macros.h"


unsigned int okay_to_look_at_switch1;
unsigned int sw1_position = RELEASED;
char count_debounce_SW1;
unsigned int okay_to_look_at_switch2;
unsigned int sw2_position = RELEASED;
char count_debounce_SW2;


void Run_Circle(void);
void Run_Triangle(void);
void Run_Infinity(void);

//------------------------------------------------------------------------------
void Switches_Process1(void){
//------------------------------------------------------------------------------
// This function calls the individual Switch Functions
//------------------------------------------------------------------------------
    Switch1_Process();
    Switch2_Process();
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void Switch1_Process(void){
//------------------------------------------------------------------------------
// Switch 1 Configurations
//------------------------------------------------------------------------------
    if (okay_to_look_at_switch1 && sw1_position){
        if (!(P4IN & SW1)){
//            sw1_position = PRESSED;
//            okay_to_look_at_switch1 = NOT_OKAY;
//            count_debounce_SW1 = DEBOUNCE_RESTART; // Fix me
            // Do something

        }
    }

    if (count_debounce_SW1 <= DEBOUNCE_TIME){
        count_debounce_SW1++;
    }  else{
            okay_to_look_at_switch1 = OKAY;
            if (P4IN & SW1){
               sw1_position = RELEASED;
            }
    }

}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
void Switch2_Process(void){
//------------------------------------------------------------------------------
// Switch 2 Configurations
//------------------------------------------------------------------------------
    if (okay_to_look_at_switch2 && sw2_position){
        if (!(P2IN & SW2)){
            sw2_position = PRESSED;
            okay_to_look_at_switch2 = NOT_OKAY;
            count_debounce_SW2 = DEBOUNCE_RESTART;
            // do something here
        }
    }
    if (count_debounce_SW2 <= DEBOUNCE_TIME){
        count_debounce_SW2++;
    }else{
        okay_to_look_at_switch2 = OKAY;
        if (P2IN & SW2){
        sw2_position = RELEASED;

        }
     }
}
//------------------------------------------------------------------------------
