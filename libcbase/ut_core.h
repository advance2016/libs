#ifndef _UT_CORE_H_
#define _UT_CORE_H_

#include "head_file.h"

#include "CUnit/Basic.h"


void ut_register_setup(const char *suitname, CU_InitializeFunc fun_init);

void ut_register_teardown(const char *suitname, CU_CleanupFunc fun_clean);

void ut_register_testcase(const char *suitname, const char *casename
                                , CU_TestFunc fun_test);

int32_t ut_init();
void ut_destory();

#endif
