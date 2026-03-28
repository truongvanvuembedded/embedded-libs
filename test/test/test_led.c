#include "unity.h"
#include "Define.h"
#include "led.h"

/* ===== Mock functions ===== */
static U1 u1_Led_State;

void mock_init(void)
{
}
void mock_on(void)
{
    u1_Led_State = U1ON;
}
void mock_off(void)
{
    u1_Led_State = U1OFF;
}

/* ===== Test hooks ===== */
void setUp(void)
{
    u1_Led_State = U1OFF;
}

void tearDown(void)
{
}

/* ===== Tests ===== */

void test_Led_On_should_turn_on_led(void)
{
    ST_LED st_Led;
    Led_Init(&st_Led, mock_init, mock_on, mock_off);

    Led_On(&st_Led);

    TEST_ASSERT_EQUAL(U1ON, u1_Led_State);
}

void test_Led_Off_should_turn_off_led(void)
{
    ST_LED st_Led;
    Led_Init(&st_Led, mock_init, mock_on, mock_off);

    Led_Off(&st_Led);

    TEST_ASSERT_EQUAL(U1OFF, u1_Led_State);
}

void test_Led_Toggle_should_toggle_state(void)
{
    ST_LED st_Led;
    Led_Init(&st_Led, mock_init, mock_on, mock_off);

    Led_On(&st_Led);
    Led_Toggle(&st_Led);
    TEST_ASSERT_EQUAL(U1OFF, u1_Led_State);

    Led_Toggle(&st_Led);
    TEST_ASSERT_EQUAL(U1ON, u1_Led_State);
}

void test_Led_Blink_should_follow_300ms_on_500ms_off(void)
{
    ST_LED st_Led;
    Led_Init(&st_Led, mock_init, mock_on, mock_off);

    /*
     * Assume Led_Blink_Polling() is called every 10ms:
     * → ON  300ms = 30 ticks
     * → OFF 500ms = 50 ticks
     * → Period    = 80 ticks
     */
    Led_Blink_Set(&st_Led, 80, 30);

    /* ===== ON phase (first 30 ticks) ===== */
    for (int i = 0; i < 30; i++)
    {
        Led_Blink_Polling(&st_Led);
        TEST_ASSERT_EQUAL(U1ON, u1_Led_State);
    }

    /* ===== OFF phase (next 50 ticks) ===== */
    for (int i = 0; i < 50; i++)
    {
        Led_Blink_Polling(&st_Led);
        TEST_ASSERT_EQUAL(U1OFF, u1_Led_State);
    }

    /* ===== New cycle should restart with ON ===== */
    Led_Blink_Polling(&st_Led);
    TEST_ASSERT_EQUAL(U1ON, u1_Led_State);
}

void test_Led_Blink_Reset_should_stop_blink_and_keep_current_state(void)
{
    ST_LED st_Led;
    Led_Init(&st_Led, mock_init, mock_on, mock_off);

    /*
     * Assume Led_Blink_Polling() is called every 10ms:
     * → ON  300ms = 30 ticks
     * → OFF 500ms = 50 ticks
     * → Period    = 80 ticks
     */
    Led_Blink_Set(&st_Led, 80, 30);

    /* ===== Run some ticks in ON phase ===== */
    for (int i = 0; i < 10; i++)
    {
        Led_Blink_Polling(&st_Led);
        TEST_ASSERT_EQUAL(U1ON, u1_Led_State);
    }

    /*
     * Reset blinking:
     * - Blink must be disabled
     * - Current LED state must be preserved (still ON)
     */
    Led_Blink_Reset(&st_Led);
    TEST_ASSERT_EQUAL(U1ON, u1_Led_State);

    /*
     * Manually turn OFF LED after reset
     * (to verify blinking no longer controls the LED)
     */
    Led_Off(&st_Led);
    TEST_ASSERT_EQUAL(U1OFF, u1_Led_State);

    /*
     * Even after many polling cycles:
     * - LED state must NOT change
     * - Because blinking is disabled
     */
    for (int i = 0; i < 100; i++)
    {
        Led_Blink_Polling(&st_Led);
        TEST_ASSERT_EQUAL(U1OFF, u1_Led_State);
    }
}