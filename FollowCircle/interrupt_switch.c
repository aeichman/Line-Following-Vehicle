#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include  "macros.h"

int sw1Status = 0;
int sw2Status = 0;
extern char event;
int time_changed = 0;
int unsigned black = 0;
int white = 0;

int unsigned blackL = 0;
int unsigned blackR = 0;

int whiteL = 0;
int whiteR = 0;

extern char display_line[4][11];
extern volatile unsigned char display_changed;
extern int ADC_Left_Detect;
extern int ADC_Right_Detect;

extern unsigned int Last_Time_Sequence;
extern int time;

#define min(a, b) (((a) < (b)) ? (a) : (b))

#pragma vector=PORT4_VECTOR
__interrupt void switch1_interrupt(void) {
    // Switch 1
    if (P4IFG & SW1) {
        TB0CCTL0 &= ~CCIE;
        P4IE &=  ~SW1;                      // 1. Disable Switch 1
        P4IFG &= ~SW1;                      // 2. Clear Switch 1 Flag
        TB0CCR1 &= ~CCIFG;
//        TB0CCTL1 &= ~CCIFG;                  // 3. Clear TimerB0 Interrupt Flag for Capture Compare Register 1
        TB0CCTL1 |= CCIE;                   // 5. Enable TimerB0_1
        TB0CCR1 += TB0CCR1_INTERVAL;        // 4. Add Interval to TB0R for TB0CCR1
        // TB0CCR1 &= ~CCIFG;

        if (sw1Status == 0) {
            P2OUT |= IR_LED;
            sw1Status = 1;
            strcpy(display_line[2], " EMIT= ON ");
            display_changed = TRUE;
            event = WAIT;
            time_changed = 0;

        } else {
            P2OUT &= ~IR_LED;
            sw1Status = 0;
            strcpy(display_line[2], " EMIT= OFF");
            display_changed = TRUE;
        }


    }
    //------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
// Port 2 interrupt for switch 2, it is disabled for the duration
// of the debounce time. Debounce time is set for 1 second
#pragma vector=PORT2_VECTOR
__interrupt void switch2_interrupt(void) {
    // Switch 2
    if (P2IFG & SW2) {
        TB0CCTL0 &= ~CCIE;
        P2IE &= ~SW2;                       // 1. Disable Switch 1
        P2IFG &= ~SW2;                      // P2.3 IFG SW2 flag cleared
        TB0CCR2 &= ~CCIFG;
//        TB0CCTL2 &= ~CCIFG;                  // 3. Clear TimerB0 Interrupt Flag for Capture Compare Register 1 (debounce)
        TB0CCTL2 |= CCIE;                   // 5. Enable TimerB0_1
        TB0CCR2 += TB0CCR1_INTERVAL;        // 4. Add Interval to TB0R for TB0CCR2
        // TB0CCR2 &= ~CCIFG;

        if (sw2Status == 0) {
            sw2Status = 1;
            black = min(ADC_Left_Detect, ADC_Right_Detect);
            blackL = ADC_Left_Detect;
            blackR = ADC_Right_Detect;
            strcpy(display_line[3], "BLACK CAP ");
            display_changed = TRUE;

        } else if (sw2Status == 1) {
            sw2Status = 2;
            white = min(ADC_Left_Detect, ADC_Right_Detect);
            whiteL = ADC_Left_Detect;
            whiteR = ADC_Right_Detect;
            strcpy(display_line[3], "WHITE CAP ");
            display_changed = TRUE;
        } else {
            sw2Status = 0;
            strcpy(display_line[3], "    GO    ");
            display_changed = TRUE;
            event = IDLE;
        }


    }
    //------------------------------------------------------------------------------
}
