
//==================================================================================================
//
// 	File Name		cmd_line.h
//	Customer
//	Coding			V.Vu
//	History			Ver.0.01	2026.03.28	V.Vu New
//	Outline			Comand line header file
//
//==================================================================================================
//==================================================================================================
//	Local Compile Option
//==================================================================================================
#ifndef CMD_LINE
#define CMD_LINE

#include "Define.h"
//==================================================================================================
//	define
//==================================================================================================
/* Return value */
#define U1_CMD_TBL_NOT_FOUND ((U1)0)
#define U1_CMD_SUCCESS       ((U1)1)
#define U1_CMD_NOT_FOUND     ((U1)2)
#define U1_CMD_TOO_LONG      ((U1)3)
//==================================================================================================
//	structure
//==================================================================================================
/* Function pointer of cmd line handler */
typedef void (*pf_cmdline_handler)(void* arg);
/* Data structure of command line object */
typedef struct
{
    U1* pu1_Cmd;                   /* Pointer to buffer containe command line value */
    U1* pu1_Info;                  /* Pointer to buffer containe command line info value */
    pf_cmdline_handler pf_handler; /* Callback function when cmd match */
} ST_CMD_LINE;
//==================================================================================================
//	Function Prototype
//==================================================================================================
U1 u1_CmdLine_Parser(ST_CMD_LINE* apst_CmdLineTable, U1* apu1_Cmd);

#endif /* CMD_LINE */
/* ************************************* End of File ******************************************** */
