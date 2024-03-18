#include  "msp430.h"
#include  <string.h>
#include  "functions.h"
#include  "LCD.h"
#include  "ports.h"
#include  "macros.h"

extern volatile unsigned char update_display;
extern volatile long int Time_Sequence;
unsigned int blink_count;
extern volatile int one_time;

extern volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
extern unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

volatile unsigned int debounce_count;
int debouncedCountSW1 = 0;
int debouncedCountSW2 = 0;
int pressedSW1 = 0;
int pressedSW2 = 0;

extern int time;
extern unsigned volatile int DAC_data;

//volatile unsigned int Time_Sequence_2;

//#pragma vector = TIMER0_B0_VECTOR
//__interrupt void Timer0_B0_ISR(void){
////------------------------------------------------------------------------------
//// TimerB0 0 Interrupt handler
////----------------------------------------------------------------------------
// // ...... Add What you need happen in the interrupt ......
//    TB0CCR0 += TB0CCR0_INTERVAL; // Add Offset to TBCCR0
//    Time_Sequence++;
//    update_display = TRUE;
////----------------------------------------------------------------------------
//}

#pragma vector = TIMER0_B0_VECTOR // Timer B0 – 0 Capture compare
__interrupt void Timer0_B0_ISR(void){
//--------------------------------------------------------------------
// TimerB0 0 Interrupt handler
//--------------------------------------------------------------------
    // LCD Backlight
     // if(blink_count++ > FIFTY_MS_COUNT) {
//     if(blink_count++ > TWENTY_MS_COUNT) {
//         blink_count = 0;                       // Reset for next count
////         P6OUT ^= LCD_BACKLITE;                 // Flip State of LCD_BACKLITE
//         update_display = 1;
//     }
//    // Time Sequence
//     one_time = 1;
     if(Time_Sequence++ > S150){  // S1250 for 1 sec, 1 for close to 200msec
         Time_Sequence = 0;
         update_display = TRUE;
         time++;
     }



      ADCCTL0 |= ADCSC;                      // Start next sample
      TB0CCR0 += TB0CCR0_INTERVAL;               // Add interval Offset to TACCR0
//     }
//     update_display = TRUE;
//     ADCCTL0 |= ADCENC;                     // Enable Conversions
//     ADCCTL0 |= ADCSC;                      // Start next sample
//     TB0CCR0 += TB0CCR0_INTERVAL;               // Add interval Offset to TACCR0

     // Add counter to count 200msec worth of interrupts then set update_display = TRUE;


//--------------------------------------------------------------------
}

#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){ // change name
//----------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TBIV) handler
//----------------------------------------------------------------------------
    switch(__even_in_range(TB0IV,14)){
        case 0: break;                      // No interrupt
        case 2:                             // CCR1 Used for SW1 Debounce
            if (debouncedCountSW1++ > FIFTY_MS_COUNT) {
                debouncedCountSW1 = 0;
                TB0CCTL1 &= ~CCIE;              // 1. Disable Timer B0 CCR1
                P4IFG &= ~SW1;                  // 2. Clear SW1 Interrupt Flag
                P4IE   |=  SW1;                 // 3. Enable SW1 Interrupt
                TB0CCTL0 |= CCIE;


//                strcpy(display_line[0], " SWITCH 1 ");
//                strcpy(display_line[1], "          ");
//                strcpy(display_line[2], "          ");
//                strcpy(display_line[3], "          ");
//                display_changed = TRUE;
            }
            // TB0CCTL1 &= ~CCIFG;
//            time++;  // ???
            TB0CCR1 += TB0CCR1_INTERVAL;    // Add offset to TBCCR1

            break;
        case 4:                             // CCR2 Used for SW2 Debounce
            pressedSW2 = 1;
            if (debouncedCountSW2++ > FIFTY_MS_COUNT) {
                debouncedCountSW2 = 0;
                TB0CCTL2 &= ~CCIE;              // 1. Disable Timer B0 CCR2
                P2IFG &= ~SW2;                  // 2. Clear SW2 Interrupt Flag
                P2IE   |=  SW2;                 // 3. Enable SW2 Interrupt
                TB0CCTL0 |= CCIE;
//                strcpy(display_line[0], " SWITCH 2 ");
//                strcpy(display_line[1], "          ");
//                strcpy(display_line[2], "          ");
//                strcpy(display_line[3], "          ");
//                display_changed = TRUE;

            }
            // TB0CCTL2 &= ~CCIFG;
            TB0CCR2 += TB0CCR2_INTERVAL;    // Add offset to TBCCR2
            break;
       case 14:                             // overflow available for greater than 1 second timer
//           DAC_data = DAC_data - 100;
//           SAC3DAT = DAC_data;
//           if ( DAC_data <= 3000 ) {  // higher for lower voltage
//               DAC_data = 3000;
//               TB0CTL &= ~TBIE;
//           }
           break;
       default: break;
    }
}





