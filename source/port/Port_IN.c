//========================================================================================
//
//	File Name		Port_IN.c
//	CPU Type
//	Builder
//	Customer
//	Coding			V.Vu
//	History			Ver.0.01	2025.10.10
//
//	Memo			Port_IN
//
//========================================================================================
//========================================================================================
//	#pragma section
//========================================================================================

//========================================================================================
//	Header File
//========================================================================================
#include "Define.h"  // Common Define
#include "Port_IN.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: Port_IN
//	Function: Port input processing
//
//	Argument: *ast_Parts : SW state structure pointer
//			au1_Port: Port status (Hi level ¨ U1HI, Lo level ¨ U1LO)
//			*apst_Spec : Port specification
//	Return:
//	Created:
//	Memo: Perform I/O input every main cycle and set it to Flag
//
///////////////////////////////////////////////////////////////////////////////////////////
void Port_IN(ST_PORT* ast_Parts, const U1 au1_Port, const ST_PORT_SPEC* const apst_Spec)
{
    if (au1_Port == apst_Spec->u1_OnLevel)
    {                                 // When the input state is on
        ast_Parts->u1_NowSts = U1ON;  // Current status ON
        ast_Parts->u2_OffC = U2MIN;   // OFF counter clear
        ast_Parts->u2_OnC++;          // On counter++
        if (ast_Parts->u2_OnC >= apst_Spec->u2_OnTimes)
        {                                               // ON counter Continuous number or more
            ast_Parts->u2_OnC = apst_Spec->u2_OnTimes;  // Max Guard
            if (ast_Parts->u1_Sts != U1ON)
            {                                  // Switch
                ast_Parts->u1_OnEdg = U1ON;    // ON trigger ON
                ast_Parts->u1_OffEdg = U1OFF;  // OFF trigger OFF
            }
            ast_Parts->u1_Sts = U1ON;  // On status confirmed
        }
    }
    else
    {                                  // When the input state is off
        ast_Parts->u1_NowSts = U1OFF;  // Current status OFF
        ast_Parts->u2_OnC = U2MIN;     // ON counter clear
        ast_Parts->u2_OffC++;          // Off counter++
        if (ast_Parts->u2_OffC >= apst_Spec->u2_OffTimes)
        {                                                 // OFF counter Continuous number or more
            ast_Parts->u2_OffC = apst_Spec->u2_OffTimes;  // Max Guard
            if (ast_Parts->u1_Sts != U1OFF)
            {                                 // Switch
                ast_Parts->u1_OnEdg = U1OFF;  // ON trigger OFF
                ast_Parts->u1_OffEdg = U1ON;  // OFF trigger ON
            }
            ast_Parts->u1_Sts = U1OFF;  // Off status confirmed
        }
    }
}

/* *************************************End of File ********************************** */
