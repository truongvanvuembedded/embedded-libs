//==================================================================================================
//
//	File Name	:	Bit_Field.h
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
//	Local Compile Option
//==================================================================================================
#ifndef BIT_FIELD_H
#define BIT_FIELD_H

#include "Define.h"

//===================================================================================================
//	constant
//===================================================================================================
#define U1_BITFIELD_1BYTE    ((U1)1)  // Bit field width 1BYTE variable
#define U1_BITFIELD_2BYTE_LE ((U1)2)  // Bit field width 2BYTE little endian variable
#define U1_BITFIELD_2BYTE_BE ((U1)3)  // Bit field width 2BYTE big endian variable
#define U1_BITFIELD_4BYTE_LE ((U1)4)  // Bit field width 4BYTE little endian variable
#define U1_BITFIELD_4BYTE_BE ((U1)5)  // Bit field width 4BYTE big endian variable

// time ----------------------------------------------------------------------------------

//==================================================================================================
//	Structure
//==================================================================================================

typedef struct
{
    U1 u1_BytePos;  // Byte position (array index)
    U1 u1_BitPos;   // Bit position (LSB = 0, MSB = 31)
    U1 u1_BitLen;   // Bit length (specify the lsb position and specify how many bits there are in the msb direction)
    U1 u1_Type;     // data type
    void* vp_Data;  // pointer to data
                    //(get data from or write data to the destination of this pointer)
} ST_BIT_LAYOUT;    // bit layout structure

//===================================================================================================
//	function
//===================================================================================================
void BitField_Init(void);  // Bit encode/decode processing initialization

// extract bits from array
void BitDecodeList(const ST_BIT_LAYOUT* acpst_LayoutList, const U1 acu1_Len, const U1* acpu1_SrcData);
// 1Byte type bit decoding
void BitDecode_1Byte(const ST_BIT_LAYOUT* acpst_Layout, const U1* acpu1_SrcData);
// 2Byte type Bit decoding Little endian
void BitDecode_2ByteLE(const ST_BIT_LAYOUT* acpst_Layout, const U1* acpu1_SrcData);
// 2Byte type bit decoding big endian
void BitDecode_2ByteBE(const ST_BIT_LAYOUT* acpst_Layout, const U1* acpu1_SrcData);
// 4Byte type Bit decoding Little endian
void BitDecode_4ByteLE(const ST_BIT_LAYOUT* acpst_Layout, const U1* acpu1_SrcData);
// 4Byte type bit decoding big endian
void BitDecode_4ByteBE(const ST_BIT_LAYOUT* acpst_Layout, const U1* acpu1_SrcData);

// Save the value of a variable to a specified position in an array
void BitEncodeList(const ST_BIT_LAYOUT* acpst_LayoutList, const U1 acu1_Len, U1* apu1_DstData);
// 1Byte type bit encoding
void BitEncode_1Byte(const ST_BIT_LAYOUT* acpst_Layout, U1* apu1_DstData);
// 2Byte type Bit encoding Little endian
void BitEncode_2ByteLE(const ST_BIT_LAYOUT* acpst_Layout, U1* apu1_DstData);
// 2Byte type Bit encoding Big endian
void BitEncode_2ByteBE(const ST_BIT_LAYOUT* acpst_Layout, U1* apu1_DstData);
// 4Byte type Bit encoding Little endian
void BitEncode_4ByteLE(const ST_BIT_LAYOUT* acpst_Layout, U1* apu1_DstData);
// 4Byte type Bit encoding Big endian
void BitEncode_4ByteBE(const ST_BIT_LAYOUT* acpst_Layout, U1* apu1_DstData);

#endif  // BIT_FIELD_H
/* *************************************End of File ******************************************** */
