
//==================================================================================================
//
// 	File Name		led.h
//	Customer
//	Coding			V.Vu
//	History			Ver.0.01	2026.03.28	V.Vu New
//	Outline			Led header file
//
//==================================================================================================
//==================================================================================================
//	Local Compile Option
//==================================================================================================
#ifndef LED_H
#define LED_H

#include "Define.h"
//==================================================================================================
//	define
//==================================================================================================

//==================================================================================================
//	structure
//==================================================================================================
/* Function pointer of led control */
typedef void (*pf_led_ctrl)();
/* Data structure of led object */
typedef struct
{
    U1 u1_Blink_Enable; /* Flag to enable or disable blinking mode */
    U1 u1_Status;       /* Current LED state (on/off) */
    U4 u4_Duty;         /* Duty cycle for blinking (percentage or ratio) */
    U4 u4_Period;       /* Blinking period (cycle time total)*/
    U4 u4_Counter;      /* Internal counter for timing control */

    pf_led_ctrl pf_Init; /* Function pointer to initialize hardware */
    pf_led_ctrl pf_On;   /* Function pointer to turn LED on */
    pf_led_ctrl pf_Off;  /* Function pointer to turn LED off */
} ST_LED;
//==================================================================================================
//	Function Prototype
//==================================================================================================
void Led_Init(ST_LED* pst_Led, pf_led_ctrl pf_Init, pf_led_ctrl pf_On, pf_led_ctrl pf_Off);  // Initialize LED with hardware control functions
void Led_On(ST_LED* pst_Led);                                                                // Turn LED on
void Led_Off(ST_LED* pst_Led);                                                               // Turn LED off
void Led_Toggle(ST_LED* pst_Led);                                                            // Toggle LED state
void Led_Blink_Set(ST_LED* pst_Led, U4 u4_Freq, U4 u4_Duty);                                 // Configure blinking with frequency and duty cycle
void Led_Blink_Reset(ST_LED* pst_Led);                                                       // Stop blinking and return to normal control
void Led_Blink_Polling(ST_LED* pst_Led);                                                     // Update blinking state, must be called periodically
#endif                                                                                       /* LED_H */
/* ************************************* End of File ******************************************** */
