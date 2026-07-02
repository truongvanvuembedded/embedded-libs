//==================================================================================================
//
//	File Name	:	Bit_Field.c
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
#include "Define.h"
#include "Bit_Field.h"  // Bit encode/decode declaration

//===================================================================================================
//	Local define
//===================================================================================================
// Numerical value ----------------------------------------------------------------------------------

// time ----------------------------------------------------------------------------------

//==================================================================================================
//	Local define I/O
//==================================================================================================
#define U1_MASK_U1_SIZE ((U1)8)
#define U1_MASK_U2_SIZE ((U1)16)
#define U1_MASK_U4_SIZE ((U1)32)

//==================================================================================================
//	Local Struct Template
//==================================================================================================

//===================================================================================================
//	Local RAM (RAM with initial values is not used)
//===================================================================================================
static U1 u1_BitMask[U1_MASK_U1_SIZE];
static U2 u2_BitMask[U1_MASK_U2_SIZE];
static U4 u4_BitMask[U1_MASK_U4_SIZE];

//==================================================================================================
//	Local Function Prototype
//==================================================================================================

//===================================================================================================
//	Source code
//===================================================================================================
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitField_Init
//	Function: Bit encoding/decoding processing Initialization
//
//	Argument: -
//	Return value: -
//	Created:
//	Change: -
//	Remarks:
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitField_Init(void)
{
    U1 au1_ForC;
    U1 au1_Mask;
    U2 au2_Mask;
    U4 au4_Mask;

    au1_Mask = U1MIN;
    for (au1_ForC = U1MIN; au1_ForC < U1_MASK_U1_SIZE; au1_ForC++)
    {
        au1_Mask |= (U1)0x01;
        u1_BitMask[au1_ForC] = au1_Mask;
        au1_Mask <<= 1;
    }

    au2_Mask = U2MIN;
    for (au1_ForC = U1MIN; au1_ForC < U1_MASK_U2_SIZE; au1_ForC++)
    {
        au2_Mask |= (U2)0x0001;
        u2_BitMask[au1_ForC] = au2_Mask;
        au2_Mask <<= 1;
    }

    au4_Mask = U4MIN;
    for (au1_ForC = U1MIN; au1_ForC < U1_MASK_U4_SIZE; au1_ForC++)
    {
        au4_Mask |= (U4)0x00000001;
        u4_BitMask[au1_ForC] = au4_Mask;
        au4_Mask <<= 1;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitDecodeList
//	Function: Retrieve bits from array
//
//	Argument: pst_LayoutList: Array of structures specifying the layout of bits to be extracted
//			acu1_Len : Array length of pst_LayoutList
//			acu1_SrcData: Array from which to retrieve data
//	Return value: -
//	Created:
//	Change: -
//	Remarks:
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitDecodeList(const ST_BIT_LAYOUT* acpst_LayoutList, const U1 acu1_Len, const U1* acpu1_SrcData)
{
    U1 au1_ForC;
    const ST_BIT_LAYOUT* acpst_Layout;
    // Execute on entire list of arguments
    for (au1_ForC = U1MIN; au1_ForC < acu1_Len; au1_ForC++)
    {
        acpst_Layout = &(acpst_LayoutList[au1_ForC]);
        // Look at the Type and call the appropriate decoding function
        switch (acpst_Layout->u1_Type)
        {
            case U1_BITFIELD_1BYTE:
                BitDecode_1Byte(acpst_Layout, acpu1_SrcData);
                break;
            case U1_BITFIELD_2BYTE_LE:
                BitDecode_2ByteLE(acpst_Layout, acpu1_SrcData);
                break;
            case U1_BITFIELD_2BYTE_BE:
                BitDecode_2ByteBE(acpst_Layout, acpu1_SrcData);
                break;
            case U1_BITFIELD_4BYTE_LE:
                BitDecode_4ByteLE(acpst_Layout, acpu1_SrcData);
                break;
            case U1_BITFIELD_4BYTE_BE:
                BitDecode_4ByteBE(acpst_Layout, acpu1_SrcData);
                break;
            default:
                break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitDecode_1Byte
//	Function: 1Byte type bit decoding
//
//	Argument: acpst_Layout: Structure specifying the layout of the bits to be extracted
//			acu1_SrcData: Array from which to retrieve data
//	Return value: -
//	Created:
//	Change: -
//	Remarks:
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitDecode_1Byte(const ST_BIT_LAYOUT* acpst_Layout, const U1* acpu1_SrcData)
{
    U1 au1_Data;  // Data temporary storage destination

    au1_Data = acpu1_SrcData[acpst_Layout->u1_BytePos];    // Extracting bytes
    au1_Data >>= acpst_Layout->u1_BitPos;                  // Adjust data arrangement to LSB
    au1_Data &= u1_BitMask[acpst_Layout->u1_BitLen - 1U];  // Mask the extracted data

    *((U1*)acpst_Layout->vp_Data) = au1_Data;  // Save to storage location
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitDecode_2ByteLE
//	Function: 2Byte type bit decoding little endian
//
//	Argument: acpst_Layout: Structure specifying the layout of the bits to be extracted
//			acu1_SrcData: Array from which to retrieve data
//	Return value: -
//	Created:
//	Change: -
//	Remarks:
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitDecode_2ByteLE(const ST_BIT_LAYOUT* acpst_Layout, const U1* acpu1_SrcData)
{
    U2 au2_Data;  // Data temporary storage destination

    // Extract in 2-byte little endian
    au2_Data = (U2)((U2)acpu1_SrcData[acpst_Layout->u1_BytePos]);
    au2_Data |= (U2)((U2)acpu1_SrcData[acpst_Layout->u1_BytePos + 1U] << 8);

    au2_Data >>= acpst_Layout->u1_BitPos;                  // Adjust data arrangement to LSB
    au2_Data &= u2_BitMask[acpst_Layout->u1_BitLen - 1U];  // Mask the extracted data

    *((U2*)acpst_Layout->vp_Data) = au2_Data;  // Save to storage location
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitDecode_2ByteBE
//	Function: 2Byte type bit decoding big endian
//
//	Argument: acpst_Layout: Structure specifying the layout of the bits to be extracted
//			acu1_SrcData: Array from which to retrieve data
//	Return value: -
//	Created:
//	Change: -
//	Remarks:
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitDecode_2ByteBE(const ST_BIT_LAYOUT* acpst_Layout, const U1* acpu1_SrcData)
{
    U2 au2_Data;  // Data temporary storage destination

    // Extract in 2-byte big endian
    au2_Data = (U2)((U2)acpu1_SrcData[acpst_Layout->u1_BytePos] << 8);
    au2_Data |= (U2)((U2)acpu1_SrcData[acpst_Layout->u1_BytePos + 1U]);

    au2_Data >>= acpst_Layout->u1_BitPos;                  // Adjust data arrangement to LSB
    au2_Data &= u2_BitMask[acpst_Layout->u1_BitLen - 1U];  // Mask the extracted data

    *((U2*)acpst_Layout->vp_Data) = au2_Data;  // Save to storage location
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitDecode_4ByteLE
//	Function: 4Byte type bit decoding little endian
//
//	Argument: acpst_Layout: Structure specifying the layout of the bits to be extracted
//			acu1_SrcData: Array from which to retrieve data
//	Return value: -
//	Created:
//	Change: -
//	Remarks:
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitDecode_4ByteLE(const ST_BIT_LAYOUT* acpst_Layout, const U1* acpu1_SrcData)
{
    U4 au4_Data;  // Data temporary storage destination

    // Extract 4 bytes little endian
    au4_Data = (U4)((U4)acpu1_SrcData[acpst_Layout->u1_BytePos]);
    au4_Data |= (U4)((U4)acpu1_SrcData[acpst_Layout->u1_BytePos + 1U] << 8);
    au4_Data |= (U4)((U4)acpu1_SrcData[acpst_Layout->u1_BytePos + 2U] << 16);
    au4_Data |= (U4)((U4)acpu1_SrcData[acpst_Layout->u1_BytePos + 3U] << 24);

    au4_Data >>= acpst_Layout->u1_BitPos;                  // Adjust data arrangement to LSB
    au4_Data &= u4_BitMask[acpst_Layout->u1_BitLen - 1U];  // Mask the extracted data

    *((U4*)acpst_Layout->vp_Data) = au4_Data;  // Save to storage location
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitDecode_4ByteBE
//	Function: 4Byte type bit decoding big endian
//
//	Argument: acpst_Layout: Structure specifying the layout of the bits to be extracted
//			acu1_SrcData: Array from which to retrieve data
//	Return value: -
//	Created:
//	Change: -
//	Remarks:
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitDecode_4ByteBE(const ST_BIT_LAYOUT* acpst_Layout, const U1* acpu1_SrcData)
{
    U4 au4_Data;  // Data temporary storage destination

    // Extract in 4-byte big endian
    au4_Data = (U4)((U4)acpu1_SrcData[acpst_Layout->u1_BytePos] << 24);
    au4_Data |= (U4)((U4)acpu1_SrcData[acpst_Layout->u1_BytePos + 1U] << 16);
    au4_Data |= (U4)((U4)acpu1_SrcData[acpst_Layout->u1_BytePos + 2U] << 8);
    au4_Data |= (U4)((U4)acpu1_SrcData[acpst_Layout->u1_BytePos + 3U]);

    au4_Data >>= acpst_Layout->u1_BitPos;                  // Adjust data arrangement to LSB
    au4_Data &= u4_BitMask[acpst_Layout->u1_BitLen - 1U];  // Mask the extracted data

    *((U4*)acpst_Layout->vp_Data) = au4_Data;  // Save to storage location
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitEncodeList
//	Function: Save the value of a variable to a specified position in an array
//
//	Argument: acpst_LayoutList: Array of structures specifying bit layout
//			acu1_Len : Array length of pst_LayoutList
//			acu1_DstData: Array of data storage destination
//	Return value: -
//	Created:
//	Change: -
//	Note: Since data is written using an OR operation, initialize the save destination to 0.
//			It is desirable to write all 0s to the array data.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitEncodeList(const ST_BIT_LAYOUT* acpst_LayoutList, const U1 acu1_Len, U1* apu1_DstData)
{
    U1 au1_ForC;
    const ST_BIT_LAYOUT* acpst_Layout;
    // Execute on entire list of arguments
    for (au1_ForC = U1MIN; au1_ForC < acu1_Len; au1_ForC++)
    {
        acpst_Layout = &(acpst_LayoutList[au1_ForC]);
        // Look at the Type and call the appropriate encoding function
        switch (acpst_Layout->u1_Type)
        {
            case U1_BITFIELD_1BYTE:
                BitEncode_1Byte(acpst_Layout, apu1_DstData);
                break;
            case U1_BITFIELD_2BYTE_LE:
                BitEncode_2ByteLE(acpst_Layout, apu1_DstData);
                break;
            case U1_BITFIELD_2BYTE_BE:
                BitEncode_2ByteBE(acpst_Layout, apu1_DstData);
                break;
            case U1_BITFIELD_4BYTE_LE:
                BitEncode_4ByteLE(acpst_Layout, apu1_DstData);
                break;
            case U1_BITFIELD_4BYTE_BE:
                BitEncode_4ByteBE(acpst_Layout, apu1_DstData);
                break;
            default:
                break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitEncode_1Byte
//	Function: 1Byte type bit encoding
//
//	Argument: acpst_Layout: Structure specifying the layout of bits to write
//			acu1_DstData: Array of data storage destination
//	Return value: -
//	Created:
//	Change: -
//	Note: Since data is written using an OR operation, initialize the save destination to 0.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitEncode_1Byte(const ST_BIT_LAYOUT* acpst_Layout, U1* apu1_DstData)
{
    U1 au1_Data;  // Data temporary storage destination

    au1_Data = *((U1*)acpst_Layout->vp_Data);              // Extracting bytes
    au1_Data &= u1_BitMask[acpst_Layout->u1_BitLen - 1U];  // Mask the extracted data
    au1_Data <<= acpst_Layout->u1_BitPos;                  // Align data arrangement

    apu1_DstData[acpst_Layout->u1_BytePos] |= au1_Data;  // Save to storage location
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitEncode_2ByteLE
//	Function: 2Byte type bit encoding little endian
//
//	Argument: acpst_Layout: Structure specifying the layout of bits to write
//			acu1_DstData: Array of data storage destination
//	Return value: -
//	Created:
//	Change: -
//	Note: Since data is written using an OR operation, initialize the save destination to 0.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitEncode_2ByteLE(const ST_BIT_LAYOUT* acpst_Layout, U1* apu1_DstData)
{
    U2 au2_Data;  // Data temporary storage destination

    au2_Data = *((U2*)acpst_Layout->vp_Data);              // data retrieval
    au2_Data &= u2_BitMask[acpst_Layout->u1_BitLen - 1U];  // Mask the extracted data
    au2_Data <<= acpst_Layout->u1_BitPos;                  // Align data arrangement

    // Saved as 2-byte little endian
    apu1_DstData[acpst_Layout->u1_BytePos] |= (U1)(au2_Data);
    apu1_DstData[acpst_Layout->u1_BytePos + 1U] |= (U1)(au2_Data >> 8);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitEncode_2ByteBE
//	Function: 2Byte type bit encoding big endian
//
//	Argument: acpst_Layout: Structure specifying the layout of bits to write
//			acu1_DstData: Array of data storage destination
//	Return value: -
//	Created:
//	Change: -
//	Note: Since data is written using an OR operation, initialize the save destination to 0.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitEncode_2ByteBE(const ST_BIT_LAYOUT* acpst_Layout, U1* apu1_DstData)
{
    U2 au2_Data;  // Data temporary storage destination

    au2_Data = *((U2*)acpst_Layout->vp_Data);              // data retrieval
    au2_Data &= u2_BitMask[acpst_Layout->u1_BitLen - 1U];  // Mask the extracted data
    au2_Data <<= acpst_Layout->u1_BitPos;                  // Align data arrangement

    // Saved as 2-byte big endian
    apu1_DstData[acpst_Layout->u1_BytePos] |= (U1)(au2_Data >> 8);
    apu1_DstData[acpst_Layout->u1_BytePos + 1U] |= (U1)(au2_Data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitEncode_4ByteLE
//	Function: 4Byte type bit encoding little endian
//
//	Argument: acpst_Layout: Structure specifying the layout of bits to write
//			acu1_DstData: Array of data storage destination
//	Return value: -
//	Created:
//	Change: -
//	Note: Since data is written using an OR operation, initialize the save destination to 0.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
void BitEncode_4ByteLE(const ST_BIT_LAYOUT* acpst_Layout, U1* apu1_DstData)
{
    U4 au4_Data;  // Data temporary storage destination

    au4_Data = *((U4*)acpst_Layout->vp_Data);              // data retrieval
    au4_Data &= u4_BitMask[acpst_Layout->u1_BitLen - 1U];  // Mask the extracted data
    au4_Data <<= acpst_Layout->u1_BitPos;                  // Align data arrangement

    // 4 bytes Saved as little endian
    apu1_DstData[acpst_Layout->u1_BytePos] |= (U1)(au4_Data);
    apu1_DstData[acpst_Layout->u1_BytePos + 1U] |= (U1)(au4_Data >> 8);
    apu1_DstData[acpst_Layout->u1_BytePos + 2U] |= (U1)(au4_Data >> 16);
    apu1_DstData[acpst_Layout->u1_BytePos + 3U] |= (U1)(au4_Data >> 24);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Name: BitEncode_4ByteBE
//	Function: 4Byte type bit encoding big endian
//
//	Argument: acpst_Layout: Structure specifying the layout of bits to write
//			acu1_DstData: Array of data storage destination
//	Return value: -
//	Created:
//	Change: -
//	Note: Since data is written using an OR operation, initialize the save destination to 0.
//
////////////////////////////////////////////////////////////////////////////////////////////////////
/** */

void BitEncode_4ByteBE(const ST_BIT_LAYOUT* acpst_Layout, U1* apu1_DstData)
{
    U4 au4_Data;  // Data temporary storage destination

    au4_Data = *((U4*)acpst_Layout->vp_Data);              // data retrieval
    au4_Data &= u4_BitMask[acpst_Layout->u1_BitLen - 1U];  // Mask the extracted data
    au4_Data <<= acpst_Layout->u1_BitPos;                  // Align data arrangement

    // Saved as 4-byte big endian
    apu1_DstData[acpst_Layout->u1_BytePos] |= (U1)(au4_Data >> 24);
    apu1_DstData[acpst_Layout->u1_BytePos + 1U] |= (U1)(au4_Data >> 16);
    apu1_DstData[acpst_Layout->u1_BytePos + 2U] |= (U1)(au4_Data >> 8);
    apu1_DstData[acpst_Layout->u1_BytePos + 3U] |= (U1)(au4_Data);
}
/* *************************************End of File ******************************************** */
