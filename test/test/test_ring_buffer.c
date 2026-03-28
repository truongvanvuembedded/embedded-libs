#include "unity.h"
#include "ring_buffer.h"

/* ===== Mock functions ===== */
static ST_RING_BUFFER st_RingBuf;
static U1 u1_Buf[10]; // buffer size = 10

void setUp(void)
{
    // Called before each test
    RingBuffer_Init(&st_RingBuf, u1_Buf, sizeof(u1_Buf));
}

void tearDown(void)
{
    // Called after each test
}

void test_RingBuffer_Init_ShouldBeEmpty(void)
{
    TEST_ASSERT_TRUE(u1_RingBufferIsEmpty(&st_RingBuf));
    TEST_ASSERT_FALSE(u1_RingBufferIsFull(&st_RingBuf));
    TEST_ASSERT_EQUAL_UINT16(0, st_RingBuf.u2_SizeFilled);
}

void test_RingBuffer_Put_Data_ShouldAddData(void)
{
    RingBuffer_Put_Data(&st_RingBuf, 0x55);
    TEST_ASSERT_FALSE(u1_RingBufferIsEmpty(&st_RingBuf));
    TEST_ASSERT_EQUAL_UINT16(1, st_RingBuf.u2_SizeFilled);
}

void test_RingBuffer_Get_Data_ShouldReturnData(void)
{
    U1 au1_Data;
    RingBuffer_Put_Data(&st_RingBuf, 0xAA);
    U1 au1_Result = u1_RingBuffer_Get_Data(&st_RingBuf, &au1_Data);
    TEST_ASSERT_EQUAL_UINT8(0xAA, au1_Data);
    TEST_ASSERT_EQUAL_UINT8(1, au1_Result); // assuming 1 = success
    TEST_ASSERT_TRUE(u1_RingBufferIsEmpty(&st_RingBuf));
}

void test_RingBuffer_ShouldBeFullAfterMaxWrites(void)
{
    for (U2 au2_ForC = 0; au2_ForC < sizeof(u1_Buf); au2_ForC++)
    {
        RingBuffer_Put_Data(&st_RingBuf, (U1)au2_ForC);
    }
    TEST_ASSERT_TRUE(u1_RingBufferIsFull(&st_RingBuf));
    TEST_ASSERT_FALSE(u1_RingBufferIsEmpty(&st_RingBuf));
    /* Check data which was written */
    for (U2 au2_ForC = 0; au2_ForC < sizeof(u1_Buf); au2_ForC++)
    {
        U1 au1_Data;
        U1 au1_Result = u1_RingBuffer_Get_Data(&st_RingBuf, &au1_Data);
        TEST_ASSERT_TRUE(au1_Result);
        TEST_ASSERT_EQUAL_UINT8((U1)au2_ForC, au1_Data);
        TEST_ASSERT_EQUAL_UINT8(1, au1_Result);
    }
}

void test_RingBuffer_ShouldReturnEmptyWhenNoData(void)
{
    U1 au1_Data;
    U1 au1_Result = u1_RingBuffer_Get_Data(&st_RingBuf, &au1_Data);
    TEST_ASSERT_EQUAL_UINT8(0, au1_Result); // assuming 0 = fail / no data
}

void test_RingBuffer_Overwrite_ShouldKeepLatestData(void)
{
    // Ghi đầy buffer
    for (U2 au2_ForC = 0; au2_ForC < sizeof(u1_Buf); au2_ForC++)
    {
        RingBuffer_Put_Data(&st_RingBuf, (U1)au2_ForC);
    }
    TEST_ASSERT_TRUE(u1_RingBufferIsFull(&st_RingBuf));

    /* Write 3 more bytes, overwriting oldest data */
    RingBuffer_Put_Data(&st_RingBuf, 100);
    RingBuffer_Put_Data(&st_RingBuf, 101);
    RingBuffer_Put_Data(&st_RingBuf, 102);

    /* Buffer is still full */
    TEST_ASSERT_TRUE(u1_RingBufferIsFull(&st_RingBuf));
    TEST_ASSERT_EQUAL_UINT16(sizeof(u1_Buf), st_RingBuf.u2_SizeFilled);

    /* Read all data */
    U1 au1_Data;
    U2 au2_ReadCnt = 0;
    U1 au1_Expected[] = {3,4,5,6,7,8,9,100,101,102}; // 0,1,2 were overwritten
    while (!u1_RingBufferIsEmpty(&st_RingBuf))
    {
        U1 au1_Result = u1_RingBuffer_Get_Data(&st_RingBuf, &au1_Data);
        TEST_ASSERT_TRUE(au1_Result);
        TEST_ASSERT_EQUAL_UINT8(au1_Expected[au2_ReadCnt], au1_Data);
        au2_ReadCnt++;
    }
    TEST_ASSERT_EQUAL_UINT16(sizeof(u1_Buf), au2_ReadCnt);
    TEST_ASSERT_TRUE(u1_RingBufferIsEmpty(&st_RingBuf));
    TEST_ASSERT_FALSE(u1_RingBufferIsFull(&st_RingBuf));
}