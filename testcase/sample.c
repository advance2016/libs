#include "ut.h"
#include "ut_main.h"

SETUP(test)
{
    return 0;
}

TEARDOWN(test)
{
    return 0;
}

TEST(test, sample)
{
    char *test = "Hello";
    int32_t len = strlen(test);
    CU_ASSERT_EQUAL(len,5);

}

TEST(test, sample2)
{
    char *test = "Hello";
    int32_t len = strlen(test);
    CU_ASSERT_EQUAL(len, 4);

}

TEST(test, sample3)
{
    char *test = "Hello";
    int32_t len = strlen(test);
    CU_ASSERT_EQUAL(len, 3);

}

