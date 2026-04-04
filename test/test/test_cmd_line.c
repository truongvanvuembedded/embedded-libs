#include "unity.h"
#include "Define.h"
#include "cmd_line.h"

#define TEST_CMD_LINE_MAX_SIZE ((U1)20)

static U1 u1_TestHandler_Called;
static U1 u1_EchoHandler_Called;
static U1* pu1_LastArg;

static void mock_test_handler(void* apv_Arg)
{
    pu1_LastArg = (U1*)apv_Arg;
    u1_TestHandler_Called++;
}

static void mock_echo_handler(void* apv_Arg)
{
    pu1_LastArg = (U1*)apv_Arg;
    u1_EchoHandler_Called++;
}

/* clang-format off */
static ST_CMD_LINE st_CmdTable[] =
{
    { (U1*)"TEST", NULL, mock_test_handler },
    { (U1*)"ECHO", NULL, mock_echo_handler },
    { NULL, NULL, NULL }
};
/* clang-format on */

void setUp(void)
{
    u1_TestHandler_Called = U1MIN;
    u1_EchoHandler_Called = U1MIN;
    pu1_LastArg = NULL;
}

void tearDown(void)
{
}

void test_CmdLine_Parser_Should_return_tbl_not_found_when_table_is_NULL(void)
{
    U1 au1_Cmd[] = "TEST";

    TEST_ASSERT_EQUAL(U1_CMD_TBL_NOT_FOUND, u1_CmdLine_Parser(NULL, au1_Cmd));
    TEST_ASSERT_EQUAL(U1MIN, u1_TestHandler_Called);
}

void test_CmdLine_Parser_Should_return_not_found_for_unknown_command(void)
{
    U1 au1_Cmd[] = "UNKNOWN";

    TEST_ASSERT_EQUAL(U1_CMD_NOT_FOUND, u1_CmdLine_Parser(st_CmdTable, au1_Cmd));
    TEST_ASSERT_EQUAL(U1MIN, u1_TestHandler_Called);
    TEST_ASSERT_EQUAL(U1MIN, u1_EchoHandler_Called);
}

void test_CmdLine_Parser_Should_return_not_found_for_empty_string(void)
{
    U1 au1_Cmd[] = "";

    TEST_ASSERT_EQUAL(U1_CMD_NOT_FOUND, u1_CmdLine_Parser(st_CmdTable, au1_Cmd));
    TEST_ASSERT_EQUAL(U1MIN, u1_TestHandler_Called);
}

void test_CmdLine_Parser_Should_return_not_found_for_string_with_only_spaces(void)
{
    U1 au1_Cmd[] = "   ";

    TEST_ASSERT_EQUAL(U1_CMD_NOT_FOUND, u1_CmdLine_Parser(st_CmdTable, au1_Cmd));
    TEST_ASSERT_EQUAL(U1MIN, u1_TestHandler_Called);
}

void test_CmdLine_Parser_Should_invoke_test_handler_for_valid_command_without_arguments(void)
{
    U1 au1_Cmd[] = "TEST";

    TEST_ASSERT_EQUAL(U1_CMD_SUCCESS, u1_CmdLine_Parser(st_CmdTable, au1_Cmd));
    TEST_ASSERT_EQUAL(U1TRUE, u1_TestHandler_Called);
    TEST_ASSERT_EQUAL(U1MIN, u1_EchoHandler_Called);
    TEST_ASSERT_NOT_NULL(pu1_LastArg);
    TEST_ASSERT_EQUAL((U1)'T', pu1_LastArg[0]);
}

void test_CmdLine_Parser_Should_invoke_echo_handler_for_valid_command_with_arguments(void)
{
    U1 au1_Cmd[] = "ECHO arg1 arg2";

    TEST_ASSERT_EQUAL(U1_CMD_SUCCESS, u1_CmdLine_Parser(st_CmdTable, au1_Cmd));
    TEST_ASSERT_EQUAL(U1MIN, u1_TestHandler_Called);
    TEST_ASSERT_EQUAL(U1TRUE, u1_EchoHandler_Called);
    TEST_ASSERT_NOT_NULL(pu1_LastArg);
    TEST_ASSERT_EQUAL((U1)'E', pu1_LastArg[0]);
    TEST_ASSERT_EQUAL_STRING("ECHO arg1 arg2", (const char*)pu1_LastArg);
}

void test_CmdLine_Parser_Should_return_too_long_for_overlong_command(void)
{
    U1 au1_Cmd[TEST_CMD_LINE_MAX_SIZE + 2];
    for (U1 au1_Index = 0; au1_Index < TEST_CMD_LINE_MAX_SIZE + 1; au1_Index++)
    {
        au1_Cmd[au1_Index] = 'A';
    }
    au1_Cmd[TEST_CMD_LINE_MAX_SIZE + 1] = 0;

    TEST_ASSERT_EQUAL(U1_CMD_TOO_LONG, u1_CmdLine_Parser(st_CmdTable, au1_Cmd));
    TEST_ASSERT_EQUAL(U1MIN, u1_TestHandler_Called);
}
