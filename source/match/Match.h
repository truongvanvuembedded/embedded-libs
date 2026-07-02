
//==================================================================================================
//
// 	File Name		Match.h
//	Customer
//	Coding			V.Vu
//	History			Ver.0.01
//	Outline			Match header file
//
//==================================================================================================
//==================================================================================================
//	Local Compile Option
//==================================================================================================
#ifndef MATCH_H
#define MATCH_H

#include "Define.h"

//==================================================================================================
//	define
//==================================================================================================
// Match type
#define U1_MATCH_TYPE_U1 ((U1)0)
#define U1_MATCH_TYPE_U2 ((U1)1)
#define U1_MATCH_TYPE_S1 ((U1)2)
#define U1_MATCH_TYPE_S2 ((U1)3)
//==================================================================================================
//	Structure
//==================================================================================================
// Match data structure
typedef struct
{
    void* vp_BefData;   // Previous data
    void* vp_NewData;   // New data
    void* vp_Data;      // Actual data
    U1* pu1_MatchCnt;   // Counter
    U1 u1_MatchCntRef;  // Counter refer
    U1 u1_MatchType;    // Match type
} ST_MATCH_DATA;
// Match structure for unsigned 1-byte data (U1)
typedef struct
{
    U1 u1_BefData;   // Previous value
    U1 u1_Data;      // Actual matched value
    U1 u1_MatchCnt;  // Counter
} ST_MATCH_U1;
// Match structure for unsigned 2-byte data (U2)
typedef struct
{
    U2 u2_BefData;   // Previous value
    U2 u2_Data;      // Actual matched value
    U1 u1_MatchCnt;  // Counter
} ST_MATCH_U2;
// Match structure for signed 1-byte data (S1)
typedef struct
{
    S1 s1_BefData;   // Previous value
    S1 s1_Data;      // Actual matched value
    U1 u1_MatchCnt;  // Counter
} ST_MATCH_S1;
// Match structure for signed 2-byte data (S2)
typedef struct
{
    S2 s2_BefData;   // Previous value
    S2 s2_Data;      // Actual matched value
    U1 u1_MatchCnt;  // Counter
} ST_MATCH_S2;

//==================================================================================================
//	Function Prototype
//==================================================================================================
void Match_Check(const ST_MATCH_DATA* apst_Match);
#endif /* MATCH_H */
       /* ************************************* End of File ******************************************** */