#include "unity.h"
#include "Define.h"
#include "button.h"

/* ===== Mock functions ===== */

/* Mock hardware read function: simulate button press/release */
static U1 mock_read_pressed(void)
{
    return U1HI;
}
static U1 mock_read_released(void)
{
    return U1LO;
}

/* Mock callback function */
static U1 u1_CallBack_Called = U1MIN;

static void mock_init()
{
}

static void mock_callback(ST_BUTTON* pst_Button)
{
    (void)pst_Button;
    u1_CallBack_Called++;
}

/* ===== Test hooks ===== */
void setUp(void)
{
    u1_CallBack_Called = 0;  // reset before each test
}

void tearDown(void)
{
}

/* ===== Tests ===== */

/* Test initialization with NULL pointer should fail */
void test_Button_Init_should_return_false_on_NULL_pointer(void)
{
    TEST_ASSERT_FALSE(u1_Button_Init(NULL, U1HI, NULL, NULL, NULL));
}

/* Test initialization with valid pointer should succeed */
void test_Button_Init_should_initialize_button(void)
{
    ST_BUTTON st_Button;
    TEST_ASSERT_TRUE(u1_Button_Init(&st_Button, U1HI, mock_init, mock_read_pressed, (pf_button_callback)mock_callback));
    TEST_ASSERT_EQUAL(U1OFF, st_Button.u1_Enable);
    TEST_ASSERT_EQUAL(U1ON, st_Button.u1_CounterEnable);
    TEST_ASSERT_EQUAL(U1HI, st_Button.u1_OnLevel);
    TEST_ASSERT_EQUAL(U1OFF, st_Button.u1_Status);
    TEST_ASSERT_EQUAL(U4MIN, st_Button.u4_Counter);
}

/* Test Button_Enable sets u1_Enable to ON */
void test_Button_Enable_should_enable_button(void)
{
    ST_BUTTON st_Button = {0};
    Button_Enable(&st_Button);
    TEST_ASSERT_EQUAL(U1ON, st_Button.u1_Enable);
}

/* Test Button_Disable sets u1_Enable to OFF */
void test_Button_Disable_should_disable_button(void)
{
    ST_BUTTON st_Button = {0};
    Button_Disable(&st_Button);
    TEST_ASSERT_EQUAL(U1OFF, st_Button.u1_Enable);
}

/* Test short press detection */
void test_Button_Timer_Polling_short_press(void)
{
    ST_BUTTON st_Button;
    U1 au1_PressSta = U1HI;
    U1 au1_CallBack_Cnt = U1MIN;

    /* mock function */
    U1 mock_read_pressed(void)
    {
        return au1_PressSta;
    }
    void mock_callback(ST_BUTTON * pst_Button)
    {
        /* Hold press detected */
        if (au1_CallBack_Cnt == U1MIN)
        {
            TEST_MESSAGE("Hold press detected");
            TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_SHORT_HOLD_PRESS, st_Button.u1_Status);
        }
        /* Short press valid detected */
        else if (au1_CallBack_Cnt == 1)
        {
            TEST_MESSAGE("Short press valid detected");
            TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_SHORT_RELEASE_PRESS, st_Button.u1_Status);
        }
        /* Increate counter callback */
        au1_CallBack_Cnt++;
    }
    /* Init */
    u1_Button_Init(&st_Button, U1HI, mock_init, mock_read_pressed, (pf_button_callback)mock_callback);
    /* Enable */
    Button_Enable(&st_Button);
    /* Simulate a press for short press duration */
    for (U4 au4_ForC = U4MIN; au4_ForC < U4_BUTTON_SHORT_PRESS_MIN_TIME; au4_ForC++)
    {
        Button_Timer_Polling(&st_Button);
    }

    /* Release button and check for SHORT_RELEASE_PRESS state */
    au1_PressSta = U1LO;
    Button_Timer_Polling(&st_Button);
}

/* Test long press detection */
void test_Button_Timer_Polling_long_press(void)
{
    ST_BUTTON st_Button;
    U1 au1_PressSta = U1HI;
    U1 au1_CallBack_Cnt = U1MIN;

    /* mock function */
    U1 mock_read_pressed(void)
    {
        return au1_PressSta;
    }

    void mock_callback(ST_BUTTON * pst_Button)
    {
        /* Hold press detected */
        if (au1_CallBack_Cnt == U1MIN)
        {
            TEST_MESSAGE("Hold press detected");
            TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_SHORT_HOLD_PRESS, st_Button.u1_Status);
        }
        /* Long press valid detected */
        else if (au1_CallBack_Cnt == 1)
        {
            TEST_MESSAGE("Long press valid detected");
            TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_LONG_PRESS, st_Button.u1_Status);
        }
        /* Increate counter callback */
        au1_CallBack_Cnt++;
    }
    /* Init */
    u1_Button_Init(&st_Button, U1HI, mock_init, mock_read_pressed, (pf_button_callback)mock_callback);
    /* Enable */
    Button_Enable(&st_Button);

    /* Simulate a press for long press duration */
    for (U4 au4_ForC = U4MIN; au4_ForC < U4_BUTTON_LONG_PRESS_TIME; au4_ForC++)
    {
        Button_Timer_Polling(&st_Button);
    }
    /* If still press it not effect */
    for (U4 au4_ForC = U4MIN; au4_ForC < U4_BUTTON_LONG_PRESS_TIME; au4_ForC++)
    {
        Button_Timer_Polling(&st_Button);
    }
    /* Release */
    au1_PressSta = U1LO;
    Button_Timer_Polling(&st_Button);
    TEST_MESSAGE("Button release");
    TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_RELEASE, st_Button.u1_Status);
}

/* Test that after long press is detected, holding button does not change counter or status */
void test_Button_Timer_Polling_hold_after_long_press_should_not_change_status(void)
{
    ST_BUTTON st_Button;
    U1 au1_PressSta = U1HI;
    /* mock function */
    U1 mock_read_pressed(void)
    {
        return au1_PressSta;
    }
    /* Init button */
    u1_Button_Init(&st_Button, U1HI, mock_init, mock_read_pressed, (pf_button_callback)mock_callback);
    Button_Enable(&st_Button);

    /* Step 1: Simulate press until long press is detected */
    for (U4 au4_ForC = 0; au4_ForC < U4_BUTTON_LONG_PRESS_TIME; au4_ForC++)
    {
        Button_Timer_Polling(&st_Button);
    }

    TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_LONG_PRESS, st_Button.u1_Status);
    TEST_ASSERT_EQUAL(2, u1_CallBack_Called);  // long and short press callback called

    /* Save counter after long press */
    U4 counter_after_long_press = st_Button.u4_Counter;

    /* Step 2: Keep holding the button for extra cycles */
    for (U4 au4_ForC = 0; au4_ForC < U4_BUTTON_LONG_PRESS_TIME; au4_ForC++)
    {
        Button_Timer_Polling(&st_Button);
        // Counter should not change
        TEST_ASSERT_EQUAL(counter_after_long_press, st_Button.u4_Counter);
        // Status should remain long press
        TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_LONG_PRESS, st_Button.u1_Status);
    }

    /* Callback should not be called again */
    TEST_ASSERT_EQUAL(2, u1_CallBack_Called);

    /* Step 3: Release button */
    au1_PressSta = U1LO;
    for (U4 au4_ForC = 0; au4_ForC < U4_BUTTON_LONG_PRESS_TIME; au4_ForC++)
    {
        Button_Timer_Polling(&st_Button);
        // After release, counter resets and status goes to RELEASE
        TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_RELEASE, st_Button.u1_Status);
        TEST_ASSERT_EQUAL(0, st_Button.u4_Counter);
    }
}

/* Test double press detection */
void test_Button_Timer_Polling_double_press(void)
{
    ST_BUTTON st_Button;
    U1 au1_PressSta = U1HI;
    U1 au1_CallBack_Cnt = U1MIN;

    /* mock function */
    U1 mock_read_pressed(void)
    {
        return au1_PressSta;
    }

    void mock_callback(ST_BUTTON * pst_Button)
    {
        /* Hold press detected */
        if (au1_CallBack_Cnt == U1MIN)
        {
            TEST_MESSAGE("Hold press detected");
            TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_SHORT_HOLD_PRESS, st_Button.u1_Status);
        }
        /* Short press valid detected */
        else if (au1_CallBack_Cnt == 1)
        {
            TEST_MESSAGE("Short press valid detected");
            TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_SHORT_RELEASE_PRESS, st_Button.u1_Status);
        }
        /* Double press valid detected */
        else if (au1_CallBack_Cnt == 2)
        {
            TEST_MESSAGE("Double press valid detected");
            TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_DOUBLE_PRESS, st_Button.u1_Status);
        }
        /* Increate counter callback */
        au1_CallBack_Cnt++;
    }
    /* Init */
    u1_Button_Init(&st_Button, U1HI, mock_init, mock_read_pressed, (pf_button_callback)mock_callback);
    /* Enable */
    Button_Enable(&st_Button);

    /* Simulate first short press */
    for (U4 au4_ForC = U4MIN; au4_ForC < U4_BUTTON_SHORT_PRESS_MIN_TIME; au4_ForC++)
    {
        Button_Timer_Polling(&st_Button);
    }

    /* Release button */
    au1_PressSta = U1LO;
    Button_Timer_Polling(&st_Button);

    /* Wait brief time before second press */
    for (U4 au4_ForC = U4MIN; au4_ForC < U4_BUTTON_SHORT_PRESS_MIN_TIME / 2; au4_ForC++)
    {
        Button_Timer_Polling(&st_Button);
    }

    /* Simulate second short press */
    au1_PressSta = U1HI;
    Button_Timer_Polling(&st_Button);

    /* Wait user release before detect next press state */
    for (U4 au4_ForC = U4MIN; au4_ForC < 1000; au4_ForC++)
    {
        Button_Timer_Polling(&st_Button);
    }

    /* Release state */
    au1_PressSta = U1LO;
    Button_Timer_Polling(&st_Button);
    TEST_ASSERT_EQUAL(U1_BUTTON_SW_STATE_RELEASE, st_Button.u1_Status);
    TEST_ASSERT_EQUAL(3, au1_CallBack_Cnt);
}
