#include "head_file.h"
#include "ut_core.h"



#define SETUP(suitname)                                                     \
                                                                            \
    int32_t setup_##suitname##_fun(void);                                      \
                                                                            \
    __attribute__((constructor)) void setup_##suitname##_CONSTRUCT(void)    \
    {                                                                       \
        ut_register_setup(#suitname, setup_##suitname##_fun);               \
    }                                                                       \
                                                                            \
    int32_t setup_##suitname##_fun(void)                                       


#define TEARDOWN(suitname)          \
                                                                            \
    int32_t teardown_##suitname##_fun(void);                                      \
                                                                            \
    __attribute__((constructor)) void teardown_##suitname##_CONSTRUCT(void)    \
    {                                                                       \
        ut_register_teardown(#suitname, teardown_##suitname##_fun);         \
    }                                                                       \
                                                                            \
    int32_t teardown_##suitname##_fun(void)                                       


#define TEST(suitname, casename)            \
                                                                            \
    void testcase_##suitname##_##casename##_fun(void);                                      \
                                                                            \
    __attribute__((constructor)) void testcase_##suitname##_##casename##_CONSTRUCT(void)    \
    {                                                                       \
        ut_register_testcase(#suitname, #casename                           \
                            , testcase_##suitname##_##casename##_fun);      \
    }                                                                       \
                                                                            \
    void testcase_##suitname##_##casename##_fun(void)                                       

