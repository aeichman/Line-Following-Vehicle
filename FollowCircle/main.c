//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
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


// Function Prototypes
void main(void);
void Init_Conditions(void);
void Display_Process(void);
void Init_LEDs(void);
void forward(void);
void reverse(void);
void TurnL(void);
void TurnR(void);
void Stop(void);
void Switches_Process1(void);

void Run_Straight(void);

void Init_Timer_B0(void);
void Init_REF(void);
void Init_DAC(void);

  // Global Variables
volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

volatile int one_time; // was char
unsigned int test_value;
char chosen_direction;
char change;

// Project 3
unsigned int wheel_move;
//char forward;
char start_moving;
unsigned int moving;




// Project 4
//unsigned int Last_Time_Sequence;
unsigned int cycle_time;


extern unsigned int okay_to_look_at_switch1;
extern unsigned int okay_to_look_at_switch2;
unsigned int right_motor_count;
unsigned int left_motor_count;
unsigned volatile long int Time_Sequence = 0;


// Project 5
extern int ADC_Left_Detect;
extern int ADC_Right_Detect;
extern int ADC_Thumb;
void wait1(void);
void run2Line(void);
void wait4(void);
void turn2Line(void);
void runCircle(void);
void turn2Center(void);
void run2Center(void);
void displayTime( char line, char location, int num );



int time = 0;
int time_change;
int event = 0;
char last_event;
unsigned int Last_Time_Sequence;
unsigned int state = WAIT;


void main(void){
//    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
  PM5CTL0 &= ~LOCKLPM5;
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings

  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_LCD();                          // Initialize LCD
  Init_Timer_B0();
  Init_ADC();
  Init_Timer_B3();
//  Init_REF();
//  Init_DAC();



//P2OUT &= ~RESET_LCD;
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//  strcpy(display_line[0], "   NCSU   ");
//  strcpy(display_line[1], " WOLFPACK ");
//  strcpy(display_line[2], "  ECE306  ");
//  strcpy(display_line[3], "  GP I/O  ");
//  display_changed = TRUE;
//  Display_Update(0,0,0,0);


  okay_to_look_at_switch1 = OKAY;
  okay_to_look_at_switch2 = OKAY;

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
//    Carlson_StateMachine();            // Run a Time Based State Machine
//    Switches_Process1();                // Check for switch state change
    Display_Process();                 // Update Display
    P3OUT ^= TEST_PROBE;               // Change State of TEST_PROBE OFF

    if(((P6IN & L_FORWARD) && (P6IN & L_REVERSE))) {
        Stop();
        P1OUT |= RED_LED;
    }
    if(((P6IN & R_FORWARD) && (P6IN & R_REVERSE))) {
        Stop();
        P1OUT |= RED_LED;
    }


    HEXtoBCD(ADC_Left_Detect);
    adc_line(1, 0);

    HEXtoBCD(ADC_Right_Detect);
    adc_line(2, 0);

    if (event == CIRCLE) {
        displayTime(4, 0, time);
    }




//    HEXtoBCD(ADC_Thumb);
//    adc_line(3, 0);

    display_changed = TRUE;


    switch (event) {
        case IDLE:
            wait1();
            break;
        case RUN_OUT:
            run2Line();
            break;
        case WAIT2:
            wait4();
            break;
        case TURN1:
            turn2Line();
            break;
        case CIRCLE:
            runCircle();
            break;
        case TURN2:
            turn2Center();
            break;
        case RUN_IN:
            run2Center();
            break;
        case END:

            break;
        default: break;
    }



  }
//------------------------------------------------------------------------------

}

