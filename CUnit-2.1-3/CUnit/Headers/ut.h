#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"



#define SETUP(suitname)                                                     \
                                                                            \
    void setup_##suitname##_fun(void);                                      \
                                                                            \
    __attribute__((constructor)) void setup_##suitname##_CONSTRUCT(void)    \
    {                                                                       \
        ut_register_setup(#suitname, setup_##suitname##_fun);
    }                                                                       \
                                                                            \
    void setup_##suitname##_fun(void)                                       \


#define TEARDOWN(suitname)
                                                                            \
    void teardown_##suitname##_fun(void);                                      \
                                                                            \
    __attribute__((constructor)) void teardown_##suitname##_CONSTRUCT(void)    \
    {                                                                       \
        ut_register_teardown(#suitname, teardown_##suitname##_fun);
    }                                                                       \
                                                                            \
    void teardown_##suitname##_fun(void)                                       \


#define TEST(suitname, casename)
                                                                            \
    void testcase_##suitname##_##casename##_fun(void);                                      \
                                                                            \
    __attribute__((constructor)) void testcase_##suitname##_##casename##_CONSTRUCT(void)    \
    {                                                                       \
        ut_register_testcase(#suitname, #casename
                            , testcase_##suitname##_##casename##_fun);
    }                                                                       \
                                                                            \
    void testcase_##suitname##_##casename##_fun(void)                                       \

