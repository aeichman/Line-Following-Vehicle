#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include  "macros.h"


void Init_Timer_B0(void) {
//--------------------------------------------------------------------
// Timer B0 initialization sets up both B0_0, B0_1-B0_2 and overflow
    TB0CTL = RESET_REGISTER; // Clear TB0 Control Register
    TB0EX0 = RESET_REGISTER; // Clear TBIDEX Register
    TB0CTL |= TASSEL__SMCLK; // SMCLK source
    TB0CTL |= MC__CONTINOUS; // Continuous up to 0xFFFF and overflow
    TB0CTL |= ID__2; // Divide clock by 2
    TB0EX0 |= TAIDEX__8; // Divide clock by an additional 8
    TB0CTL |= TBCLR; // Resets TB0R,
    // Capture Compare 0
//    #pragma vector = TIMER0_B0_VECTOR
    // Capture Compare 0
    TB0CCR0 = TB0CCR0_INTERVAL; // CCR0
    TB0CCTL0 |= CCIE; // CCR0 enable interrupt

    // Capture Compare 1,2, Overflow
//    #pragma vector = TIMER0_B1_VECTOR
    // Capture compare 1
    TB0CCR1 = TB0CCR1_INTERVAL;// CCR1
    TB0CCTL1 |= CCIE; // CCR1 enable interrupt
    TB0CCTL1 &= ~CCIFG;
    TB0CCTL1 &= ~CCIE;

    // Capture compare 2
    TB0CCR2 = TB0CCR2_INTERVAL;// CCR2
    TB0CCTL2 |= CCIE; // CCR2 enable interrupt
    TB0CCTL2 &= ~CCIFG;
    TB0CCTL2 &= ~CCIE;

    // Overflow
    TB0CTL |= TBIE; // enable Overflow Interrupt // disable for bat power
    TB0CTL &= ~TBIFG; // Clear Overflow Interrupt flag
//--------------------------------------------------------------------
}

void Init_Timer_B3(void) {
//------------------------------------------------------------------------------
// SMCLK source, up count mode, PWM Right Side
// TB3.1 P6.0 LCD_BACKLITE
// TB3.2 P6.1 R_FORWARD
// TB3.3 P6.2 R_REVERSE !! 6.3
// TB3.4 P6.3 L_FORWARD !! 6.2
// TB3.5 P6.4 L_REVERSE
//------------------------------------------------------------------------------
    TB3CTL = TBSSEL__SMCLK;             // SMCLK
    TB3CTL |= MC__UP;                   // Up Mode
    TB3CTL |= TBCLR;                    // Clear TAR
    PWM_PERIOD = WHEEL_PERIOD;          // PWM Period [Set this to 50005]

    TB3CCTL1 = OUTMOD_7;                // CCR1 reset/set
    LCD_BACKLITE_DIMING = PERCENT_80;   // P6.0 Right Forward PWM duty cycle

    TB3CCTL2 = OUTMOD_7;                // CCR2 reset/set
    RIGHT_FORWARD_SPEED = WHEEL_OFF;    // P6.1 Right Forward PWM duty cycle

    TB3CCTL3 = OUTMOD_7;                // CCR3 reset/set 4
    LEFT_FORWARD_SPEED = WHEEL_OFF;     // P6.2 Right Reverse PWM duty cycle   !! 6.3 Right reverse

    TB3CCTL4 = OUTMOD_7;                // CCR4 reset/set 3
    RIGHT_REVERSE_SPEED = WHEEL_OFF;    // P6.3 Left Forward PWM duty cycle !! 6.2 Left forward

    TB3CCTL5 = OUTMOD_7;                // CCR5 reset/set
    LEFT_REVERSE_SPEED = WHEEL_OFF;     // P6.4 Left Reverse PWM duty cycle
//------------------------------------------------------------------------------
}


