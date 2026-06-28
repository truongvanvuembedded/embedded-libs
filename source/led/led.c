//==================================================================================================
//
//	File Name	:	led.c
//	CPU Type	:
//	IDE			:
//	Customer
//	Version		:	Ver.0.01
//	Coding		:	V.Vu
//	History		:	28/03/2026
//	Outline		:
//
//==================================================================================================
//==================================================================================================
//	#pragma section
//==================================================================================================

//==================================================================================================
//	Local Compile Option
//==================================================================================================

//==================================================================================================
//	Header File
//==================================================================================================
#include "led.h"
#include "Define.h"
//==================================================================================================
//	Local define
//==================================================================================================

//==================================================================================================
//	Local define I/O
//==================================================================================================

//==================================================================================================
//	Local Struct Template
//==================================================================================================

//==================================================================================================
//	Local RAM
//==================================================================================================

//==================================================================================================
//	Local ROM
//==================================================================================================

//==================================================================================================
//	Local Function Prototype
//==================================================================================================

//==================================================================================================
//	Source Code
//==================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name		:	Led_Init
//	Function	:	Initialize LED object and assign platform-specific control functions
//
//	Argument	:	ST_LED *pst_Led      - pointer to LED object
//					pf_led_ctrl pf_Init  - hardware initialization function (This function must determine init level of led)
//					pf_led_ctrl pf_On    - function to turn LED on (active level depends on hardware)
//					pf_led_ctrl pf_Off   - function to turn LED off (active level depends on hardware)
//	Return		:	void
//	Created		:	28/03/2026
//	Changed		:	-
//	Remarks		:	User must provide correct control functions according to hardware design
//					(active-high or active-low). This abstraction ensures portability across platforms.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void Led_Init(ST_LED* pst_Led, pf_led_ctrl pf_Init, pf_led_ctrl pf_On, pf_led_ctrl pf_Off)
{
    /* Init led object */
    pst_Led->u1_Blink_Enable = U1FALSE;
    pst_Led->u1_Status = U1OFF;
    pst_Led->u4_Counter = U4MIN;
    pst_Led->u4_Duty = U4MIN;
    pst_Led->u4_Period = U4MIN;
    /* Init led control function */
    pst_Led->pf_Init = pf_Init;
    pst_Led->pf_On = pf_On;
    pst_Led->pf_Off = pf_Off;

    /* Init led */
    if (pf_Init)
    {
        pf_Init();
    }
    /* Set default led to off */
    if (pf_Off)
    {
        pf_Off();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name		:	Led_On
//	Function	:	Turn on the LED using the assigned control function
//
//	Argument	:	ST_LED *pst_Led - pointer to LED object
//	Return		:	void
//	Created		:	28/03/2026
//	Changed		:	-
//	Remarks		:	The actual ON level depends on the user-provided pf_On function
//					(active-high or active-low handled at platform layer).
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void Led_On(ST_LED* pst_Led)
{
    pst_Led->u1_Status = U1ON;
    if (pst_Led->pf_On)
    {
        pst_Led->pf_On();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name		:	Led_Off
//	Function	:	Turn off the LED using the assigned control function
//
//	Argument	:	ST_LED *pst_Led - pointer to LED object
//	Return		:	void
//	Created		:	28/03/2026
//	Changed		:	-
//	Remarks		:	The actual OFF level depends on the user-provided pf_Off function
//					(active-high or active-low handled at platform layer).
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void Led_Off(ST_LED* pst_Led)
{
    pst_Led->u1_Status = U1OFF;
    if (pst_Led->pf_Off)
    {
        pst_Led->pf_Off();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name		:	Led_Toggle
//	Function	:	Toggle the LED state (ON <-> OFF)
//
//	Argument	:	ST_LED *pst_Led - pointer to LED object
//	Return		:	void
//	Created		:	28/03/2026
//	Changed		:	-
//	Remarks		:	State is toggled based on current status and uses pf_On/pf_Off internally,
//					ensuring hardware abstraction at platform layer.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void Led_Toggle(ST_LED* pst_Led)
{
    if (pst_Led->u1_Status == U1OFF)
    {
        Led_On(pst_Led);
    }
    else
    {
        Led_Off(pst_Led);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name		:	Led_Blink_Set
//	Function	:	Enable blinking mode with specified frequency and duty cycle
//
//	Argument	:	ST_LED *pst_Led - pointer to LED object
//					U4 u4_Period       - blinking frequency
//					U4 u4_Duty       - duty cycle
//	Return		:	void
//	Created		:	28/03/2026
//	Changed		:	-
//	Remarks		:	Blinking is handled in software and requires periodic polling.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void Led_Blink_Set(ST_LED* pst_Led, U4 u4_Period, U4 u4_Duty)
{
    pst_Led->u1_Blink_Enable = U1TRUE;
    pst_Led->u4_Period = u4_Period;
    pst_Led->u4_Duty = u4_Duty;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name		:	Led_Blink_Reset
//	Function	:	Disable blinking mode and restore manual LED control
//
//	Argument	:	ST_LED *pst_Led - pointer to LED object
//	Return		:	void
//	Created		:	28/03/2026
//	Changed		:	-
//	Remarks		:	LED will stop blinking and remain in its last state.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void Led_Blink_Reset(ST_LED* pst_Led)
{
    pst_Led->u1_Blink_Enable = U1FALSE;
    pst_Led->u4_Period = U4MIN;
    pst_Led->u4_Duty = U4MIN;
    pst_Led->u4_Counter = U4MIN;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name		:	Led_Blink_Polling
//	Function	:	Update LED blinking state based on timing parameters
//
//	Argument	:	ST_LED *pst_Led - pointer to LED object
//	Return		:	void
//	Created		:	28/03/2026
//	Changed		:	-
//	Remarks		:	Must be called periodically (e.g., in main loop or timer task)
//					to ensure correct blinking behavior.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void Led_Blink_Polling(ST_LED* pst_Led)
{
    if (pst_Led->u1_Blink_Enable)
    {
        pst_Led->u4_Counter++;

        /* ON phase: keep LED ON during duty time */
        if (pst_Led->u4_Counter <= pst_Led->u4_Duty)
        {
            if (pst_Led->u1_Status != U1ON)
            {
                Led_On(pst_Led);
            }
        }
        /* OFF phase: turn LED OFF for the remaining period */
        else if (pst_Led->u4_Counter < pst_Led->u4_Period)
        {
            if (pst_Led->u1_Status != U1OFF)
            {
                Led_Off(pst_Led);
            }
        }
        /* Reset counter at end of cycle */
        else if (pst_Led->u4_Counter >= pst_Led->u4_Period)
        {
            pst_Led->u4_Counter = U4MIN;
        }
    }
}