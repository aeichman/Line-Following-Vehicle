//------------------------------------------------------------------------------
//
//  Description:
//
//  Adam Eichman
//  Jan 2024
//  Built with Code Composer Version: CCS12.6.0.00007_win64
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x40) // GREEN LED 1
#define TEST_PROBE           (0x01) // 0 TEST PROBE


// STATES ======================================================================
#define NONE                ('N')

#define WHEEL_COUNT_TIME    (20)
#define RIGHT_COUNT_TIME    (14)
#define LEFT_COUNT_TIME     (20)
#define TRAVEL_DISTANCE     (20)
#define WAITING2START       (50)

#define PRESSED             (0)
#define NOT_OKAY            (0)
#define DEBOUNCE_RESTART    (0)
#define DEBOUNCE_TIME       (30)
#define OKAY                (0x01)
#define RELEASED            (1)

// Timer Intervals
#define TB0CCR0_INTERVAL    (20000)
#define TB0CCR1_INTERVAL    (25000)
#define TB0CCR2_INTERVAL    (25000)  //50000 = 200ms

#define TASSEL__SMCLK       (0x0200)

// Main While loop switch cases
#define Time_Sequence_Rate  (50) // 50 millisecods
#define S1250               (1250/Time_Sequence_Rate) // 1.25 seconds
#define S1000               (1000/Time_Sequence_Rate) // 1 second
#define S750                (750/Time_Sequence_Rate) // 0.75 seconds
#define S500                (500/Time_Sequence_Rate) // 0.50 seconds
#define S250                (250/Time_Sequence_Rate) // 0.25 seconds
#define S150                (150/Time_Sequence_Rate) // 0.20 seconds


#define ID_1                (0x0040) /* /2 */
#define ID_2                (0x0080) /* /4 */
#define ID_3                (0x00c0) /* /8 */
#define ID__2               (0x0040) /* /2 */
#define ID__4               (0x0080) /* /4 */
#define ID__8               (0x00c0) /* /8 */

#define TAIDEX_0            (0x0000) /* Divide by 1 */
#define TAIDEX_1            (0x0001) /* Divide by 2 */
#define TAIDEX_2            (0x0002) /* Divide by 3 */
#define TAIDEX_3            (0x0003) /* Divide by 4 */
#define TAIDEX_4            (0x0004) /* Divide by 5 */
#define TAIDEX_5            (0x0005) /* Divide by 6 */
#define TAIDEX_6            (0x0006) /* Divide by 7 */
#define TAIDEX_7            (0x0007) /* Divide by 8 */
#define TAIDEX__1           (0x0000) /* Divide by 1 */
#define TAIDEX__2           (0x0001) /* Divide by 2 */
#define TAIDEX__3           (0x0002) /* Divide by 3 */
#define TAIDEX__4           (0x0003) /* Divide by 4 */
#define TAIDEX__5           (0x0004) /* Divide by 5 */
#define TAIDEX__6           (0x0005) /* Divide by 6 */
#define TAIDEX__7           (0x0006) /* Divide by 7 */
#define TAIDEX__8           (0x0007) /* Divide by 8 */

#define TWOHUND_MS_COUNT    (30)
#define FIFTY_MS_COUNT      (10)
#define TWENTY_MS_COUNT     (2) // was 5

#define RESET_REGISTER      (0)


#define FALSE                  (0x00) //
#define TRUE                   (0x01) //
#define MOTOR                  (0x00) //
#define SMCLK_OFF              (0x00) //
#define SMCLK_ON               (0x01) //
#define PORTS                  (0x00) // RED LED 0
#define PWM_MODE               (0x01) // GREEN LED 1

#define SLOW_R2                (9000)
#define SLOW_L2                (15000)



#define SLOW_R                 (12000)
#define SLOW_L                 (10000)
#define FAST                   (50000)
#define PERCENT_100            (50000)
#define PERCENT_80             (45000)
#define PERCENT_60             (30000)

#define WHEEL_OFF              (0x00)
#define PWM_PERIOD             (TB3CCR0)
#define WHEEL_PERIOD           (50005)
#define LCD_BACKLITE_DIMING    (TB3CCR1)
#define RIGHT_FORWARD_SPEED    (TB3CCR3)  // 2 Old values
#define RIGHT_REVERSE_SPEED    (TB3CCR5)  // 4
#define LEFT_FORWARD_SPEED     (TB3CCR2)  // 3
#define LEFT_REVERSE_SPEED     (TB3CCR4)  // 5
#define STEP                   (2000)
#define FORWARD                (0x00) // FORWARD
#define REVERSE                (0x01) // REVERSE

#define WAIT                   (0)
#define IDLE                   (1)
#define RUN_OUT                (2)
#define WAIT2                  (3)
#define TURN1                  (4)
#define CIRCLE                 (5)
#define TURN2                  (6)
#define RUN_IN                 (7)
#define END                    (8)

#define NO                     (0)
#define YES                    (1)

#define LEFT                   (10)
#define RIGHT                  (11)


