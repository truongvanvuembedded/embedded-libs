//==================================================================================================
//
//	File Name		Port_IN.h
//	CPU Type
//	Builder
//	Customer
//	Coding			V.Vu
//	History			Ver.0.01	2025.10.10
//
//	Memo			Port_IN
//
//==================================================================================================

#ifndef PORT_IN_H
#define PORT_IN_H

#include "Define.h"

//==================================================================================================
//	define
//==================================================================================================

//==================================================================================================
//	Struct Template
//==================================================================================================
typedef struct
{
    U2 u2_OnC;     // Port ON counter
    U2 u2_OffC;    // Port OFF counter
    U1 u1_Sts;     // Port Determined state
    U1 u1_OnEdg;   // Port ON trigger
    U1 u1_OffEdg;  // Port OFF trigger
    U1 u1_NowSts;  // Port Current status
} ST_PORT;

typedef struct
{
    U2 u2_OnTimes;   // On continuous count number
    U2 u2_OffTimes;  // Off continuous count number
    U1 u1_OnLevel;   // On recognized port level
} ST_PORT_SPEC;      // Port specifications

//==================================================================================================
//	Function Prototype
//==================================================================================================
void Port_IN(ST_PORT* ast_Parts, const U1 au1_Port, const ST_PORT_SPEC* const apst_Spec);

#endif /* Port in h */
/* *************************************End of File ******************************************** */
