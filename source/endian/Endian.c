//==================================================================================================
//	File Name	: Endian.c
//	CPU Type	:
//	Builder		:
//	Coding		: V.Vu New
//	History		:
//	Outline		:
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
#include "Endian.h"  // Endian header file

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
//    Name    : Divide_LittleEndian_U2
//    Function: U2 type split processing
//    Argument: apu1_Buff : Address of storage array
//              au2_Divide: U2 type data to be divided
//    Return  : None
//    Created : 
//    Change  : 
//    Note    : 
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void Divide_LittleEndian_U2(U1* apu1_Buff, const U2 au2_Divide)
{
    U1 au1_Num;
    U2 au2_Data;

    au1_Num = U1MIN;
    au2_Data = au2_Divide & (U2)0x00FF;  // Get lower data (changed on 2015.06.18)
    apu1_Buff[au1_Num] = (U1)au2_Data;   // Store lower data
    au1_Num++;
    au2_Data = au2_Divide >> (U2)8;     // Move upper byte to lower (changed on 2015.06.18)
    au2_Data = au2_Data & (U2)0x00FF;   // Get top data (changed on 2015.06.18)
    apu1_Buff[au1_Num] = (U1)au2_Data;  // Store top data
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Name    : Divide_LittleEndian_U4
//    Function: U4 type split processing
//    Argument: apu1_Buff : Address of storage array
//              au4_Divide: U4 type data to be divided
//    Return  : None
//    Created : 
//    Change  : 
//    Note    : 
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void Divide_LittleEndian_U4(U1* apu1_Buff, const U4 au4_Divide)
{
    U1 au1_ForC;
    U1 au1_Shift;
    U4 au4_Data;

    au1_Shift = U1MIN;
    for (au1_ForC = U1MIN; au1_ForC < (U1)4; au1_ForC++)
    {
        au1_Shift = au1_ForC * (U1)8;                           // Number of shifts in bytes (changed on 2023.08.24)
        au4_Data = (au4_Divide >> au1_Shift) & (U4)0x000000FF;  // get data
        apu1_Buff[au1_ForC] = (U1)au4_Data;                     // store data
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Name    : u4_Unite_BigEndian
//    Function: Unite U4 data from Big Endian
//    Argument: apu1_Buff : Address of storage array
//    Return  : None
//    Created : 
//    Change  : 
//    Note    : 
//
////////////////////////////////////////////////////////////////////////////////////////////////////
U4 u4_Unite_BigEndian(const U1* apu1_Buff)
{
    U1 au1_ForC;
    U1 au1_Shift;
    U4 au4_Data;
    au4_Data = U4MIN;
    au1_Shift = U1MIN;
    for (au1_ForC = U1MIN; au1_ForC < (U1)4; au1_ForC++)
    {
        au1_Shift = (3 - au1_ForC) << (U1)3;
        au4_Data |= ((U4)0x000000FF & (U4)apu1_Buff[au1_ForC]) << au1_Shift;
    }
    return au4_Data;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Name    : u4_Unite_LittleEndian
//    Function: Unite U4 data from Little Endian
//    Argument: apu1_Buff : Address of storage array
//    Return  : None
//    Created : 
//    Change  : 
//    Note    : 
//
////////////////////////////////////////////////////////////////////////////////////////////////////
U4 u4_Unite_LittleEndian(const U1* apu1_Buff)
{
    U1 au1_ForC;
    U1 au1_Shift;
    U4 au4_Data;
    au4_Data = U4MIN;
    au1_Shift = U1MIN;
    for (au1_ForC = U1MIN; au1_ForC < (U1)4; au1_ForC++)
    {
        au1_Shift = au1_ForC << (U1)3;
        au4_Data |= ((U4)0x000000FF & (U4)apu1_Buff[au1_ForC]) << au1_Shift;
    }
    return au4_Data;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Name    : u2_Unite_BigEndian
//    Function: Unite U2 data from Big Endian
//    Argument: apu1_Buff : Address of storage array
//    Return  : None
//    Created : 
//    Change  : 
//    Note    : 
//
////////////////////////////////////////////////////////////////////////////////////////////////////
U2 u2_Unite_BigEndian(const U1* apu1_Buff)
{
    U1 au1_ForC;
    U1 au1_Shift;
    U2 au2_Data;

    au2_Data = U2MIN;
    au1_Shift = U1MIN;
    for (au1_ForC = U1MIN; au1_ForC < (U1)2; au1_ForC++)
    {
        au1_Shift = (1 - au1_ForC) << (U1)3;
        au2_Data |= (U2)apu1_Buff[au1_ForC] << au1_Shift;
    }
    return au2_Data;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Name    : u2_Unite_LittleEndian
//    Function: Unite U2 data from Little Endian
//    Argument: apu1_Buff : Address of storage array
//    Return  : None
//    Created : 
//    Change  : 
//    Note    : 
//
////////////////////////////////////////////////////////////////////////////////////////////////////
U2 u2_Unite_LittleEndian(const U1* apu1_Buff)
{
    U1 au1_ForC;
    U1 au1_Shift;
    U2 au2_Data;
    au2_Data = U2MIN;
    au1_Shift = U1MIN;
    for (au1_ForC = U1MIN; au1_ForC < (U1)2; au1_ForC++)
    {
        au1_Shift = au1_ForC << (U1)3;
        au2_Data |= (U2)apu1_Buff[au1_ForC] << au1_Shift;
    }
    return au2_Data;
}
/* *************************************End of File ******************************************** */