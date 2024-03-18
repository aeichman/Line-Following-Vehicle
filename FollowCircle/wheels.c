//------------------------------------------------------------------------------
//
//  Description: This file contains the functions to move the wheels on the car
//
//  Adam Eichman
//  Feb 2024
//  Built with Code Composer Version: CCS12.6.0.00007_win64
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include  "macros.h"

extern int time;
extern int time_change;
extern int event;
extern int ADC_Left_Detect;
extern int ADC_Right_Detect;
extern unsigned volatile long int Time_Sequence;
extern unsigned int Last_Time_Sequence;
extern char display_line[4][11];
extern volatile unsigned char display_changed;

extern unsigned int black;
extern int white;
extern int ADC_Left_Detect;
extern int ADC_Right_Detect;

extern unsigned int state;

unsigned int wait = 0;

extern unsigned int blackL;
extern unsigned int blackR;
extern int whiteL;
extern int whiteR;

unsigned int lastSide = 0;


void Stop(void) {
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void forward(void) {
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;

    RIGHT_FORWARD_SPEED = SLOW_R;
    LEFT_FORWARD_SPEED = SLOW_L;

}

void forward_ST(void) {
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;

    RIGHT_FORWARD_SPEED = SLOW_R2;
    LEFT_FORWARD_SPEED = SLOW_L2;

}


void reverse(void) {
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;

    RIGHT_REVERSE_SPEED = SLOW_R;
    LEFT_REVERSE_SPEED = SLOW_L;

}

void reverseLeft(void) {
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;

    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = SLOW_L;
}

void reverseRight(void) {
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;

    RIGHT_REVERSE_SPEED = SLOW_L;
    LEFT_REVERSE_SPEED = WHEEL_OFF;
}


void turnLeft(void) {
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;

    RIGHT_FORWARD_SPEED = SLOW_R;
    LEFT_FORWARD_SPEED = WHEEL_OFF;

}

void turnLeftIP(void) {
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;

    RIGHT_FORWARD_SPEED = SLOW_R2;
    LEFT_REVERSE_SPEED = SLOW_L2;
}

void turnRightIP(void) {
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;

    RIGHT_REVERSE_SPEED = SLOW_R;
    LEFT_FORWARD_SPEED = SLOW_L;
}

void turnRight(void) {
    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = WHEEL_OFF;
    RIGHT_REVERSE_SPEED = WHEEL_OFF;
    LEFT_REVERSE_SPEED = WHEEL_OFF;

    RIGHT_FORWARD_SPEED = WHEEL_OFF;
    LEFT_FORWARD_SPEED = SLOW_L;
}


void wait1(void){
    if (wait == NO) {
        time = 0;
        wait = YES;
    }
    if (time == 15){  // Time_Sequence
         Last_Time_Sequence = time;
         time_change = 1;
         event = RUN_OUT;
         wait = NO;
    }
}

void run2Line(void) {
    forward_ST();
    strcpy(display_line[2], "Run 2 Line");
    display_changed = TRUE;
    if ( ADC_Right_Detect > (whiteR + 100) ) {
        Stop();
        display_changed = TRUE;
        event = WAIT2;
    }
}

void wait4(void) {
    strcpy(display_line[2], "   Wait   ");
    display_changed = TRUE;
    if (wait == NO) {
        time = 0;
        wait = YES;
    }
    if (time == 15){  // Time_Sequence
         Last_Time_Sequence = time;
         event = TURN1;
         wait = NO;
    }
}

void turn2Line(void) {
    turnRightIP();

    strcpy(display_line[2], "Go 2 Line ");
    display_changed = TRUE;

    if ( ADC_Right_Detect > (blackL - 150) ) {
        Stop();
        event = CIRCLE; // CIRCLE
        time = 0;
    }
}


void runCircle(void) {
    if (wait == NO) {
        time = 0;
        wait = YES;
        strcpy(display_line[2], " Circle   ");
        strcpy(display_line[3], "          ");
        display_changed = TRUE;
    }

    if (time >= 425) {
        wait = NO;
        event = TURN2;
        time = 0;
    }


    else if ( (ADC_Right_Detect < (whiteR + 25)) && (ADC_Left_Detect < (whiteL + 25)) ){
        Stop();
//        strcpy(display_line[3], "  WHITE   ");
        reverse();
        display_changed = TRUE;

    }


    else if ( (ADC_Left_Detect < (whiteL + 225)) ) {
        Stop();

        reverseRight();

//        strcpy(display_line[3], "  RIGHT   ");
        display_changed = TRUE;
        lastSide = RIGHT;
    }


    else if ( (ADC_Right_Detect < (whiteR + 225)) ) {
        Stop();
        reverseLeft();
//        strcpy(display_line[3], "  LEFT    ");
        display_changed = TRUE;
        lastSide = LEFT;
    }

    else {
        Stop();
        forward();
//        strcpy(display_line[3], "  BLACK   ");
        display_changed = TRUE;
    }



}

void turn2Center(void) {
    turnRight();
    if (wait == NO) {
        time = 0;
        wait = YES;
    }
    strcpy(display_line[2], "Turn 2 Mid ");
    display_changed = TRUE;
    if (time == 10){  // Time_Sequence
         Last_Time_Sequence = time;
         time_change = 1;
         event = RUN_IN;
         wait = NO;
         time = 0;
    }

}

void run2Center(void) {
    forward();
    strcpy(display_line[2], " Run 2 Mid");
    display_changed = TRUE;
    if (wait == NO) {
        time = 0;
        wait = YES;
    }
    if (time == 15){  // Time_Sequence
         Last_Time_Sequence = time;
         time_change = 1;
         event = END;
         Stop();
         strcpy(display_line[2], "  Center  ");
         display_changed = TRUE;
         wait = NO;
    }
}




