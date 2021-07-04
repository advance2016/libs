#ifndef _UT_MAIN_H_
#define _UT_MAIN_H_

#include <getopt.h>
#include <unistd.h>
#include "head_file.h"

#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/CUnit.h"
#include "CUnit/TestDB.h"

/*
struct option {
    const char *name;
    int has_arg;
    int *flag;
    int val;
};

1.name: 长选项的名称
2.has_arg: 参数情况

符号常量	数值	Meaning
no_argument	0	无参数
required_argument	1	有参数
optional_argument	2	参数可选
考虑到“可读性”，一般使用“符号常量”

3.int *flag: 如果flag为 NULL, getup_long() 返回val的值; 如果不是NULL, val的值
  赋给flag指针指向的内容，同时getopt_long()返回 0

4.int val: flag为NULL，val作为getopt_long()的返回值；如果flag不为NULL，val赋值
 给flag指针所指内容；

*/


static const struct option long_options[]=
{
   {"mode", required_argument, NULL, 'm'},
   {"show", no_argument      , NULL, 's'},
   {"run", no_argument      , NULL, 'r'},
   {"raw", no_argument      , NULL, 't'},
   {NULL, 0, NULL, 0}                       //最后一个元素应该全为0
};


typedef enum {
    MODE_NONE = 0,
    MODE_AUTOMATED,
    MODE_BASIC,
    MODE_CONSOLE,
    MODE_CURSES,
} run_mode_t;


typedef enum {
    RUN_OP_NONE = 0,
    RUN_OP_RUN_ALL,
    RUN_OP_SHOW_ALL,
    RUN_OP_RUN_SUITE,
    RUN_OP_RUN_SUITE_CASE,
    RUN_OP_RUN_RAW,
} run_op_t;

#define SIZE_128B 128

static run_mode_t s_run_mode = MODE_CONSOLE;
static run_op_t s_run_op = RUN_OP_RUN_ALL;
static char s_suitname[SIZE_128B] = {0};
static char s_casename[SIZE_128B] = {0};


int32_t parse_argv(int32_t argc, char * argv [])
{
    int32_t opt = 0;
    int32_t options_index = 0;
    char *tmp = NULL;
    int64_t len = 0;
    
    while (1)
    {
        opt = getopt_long(argc, argv, "m:sr:t", long_options, &options_index);
        if (opt == -1)
        {
            break;
        }

        switch (opt) {
            case 'm':
                assert (optarg != NULL);
                if (strcmp(optarg, "automated") == 0)
                {
                    s_run_mode = MODE_AUTOMATED;
                }
                else if (strcmp(optarg, "basic") == 0)
                {
                    s_run_mode = MODE_BASIC;
                }
                else if (strcmp(optarg, "console") == 0)
                {
                    s_run_mode = MODE_CONSOLE;
                }
                else if (strcmp(optarg, "curses") == 0)
                {
                    s_run_mode = MODE_CURSES;
                }
                break;
            case 's':
                s_run_op = RUN_OP_SHOW_ALL;
                break;
            case 't':
                s_run_op = RUN_OP_RUN_RAW;
                break;
            case 'r':
                tmp = strchr(optarg, '.');
                if (tmp == NULL)
                {
                    s_run_op = RUN_OP_RUN_SUITE;
                    if (strlen(optarg) >= sizeof(s_suitname))
                    {
                        printf("suitname too long %s", optarg);
                        exit(0);
                    }
                    strcpy(s_suitname, optarg);
                }
                else
                {
                    s_run_op = RUN_OP_RUN_SUITE_CASE;
                    
                    len = (int64_t)tmp - (int64_t)optarg;
                    assert(len > 0);

                    if (len >= sizeof(s_suitname))
                    {
                        printf("suitname too long %s", optarg);
                        exit(1);
                    }
                    
                    memcpy(s_suitname, optarg, len);

                    if (strlen(tmp + 1) >= sizeof(s_casename))
                    {
                        printf("casename too long %s", tmp + 1);
                        exit(1);
                    }

                    strncpy(s_casename, tmp + 1, sizeof(s_casename) - 1);
                }
                break;
            case '?':
                break;
            default:
                abort();
        }
    }


    return 0;
}


/*
switch (s_run_mode) {
    case MODE_AUTOMATED:
        // Automated Mode 
        //CU_set_output_filename("TestMax");
        //CU_list_tests_to_file();
        //CU_automated_run_tests();
        break;
    case MODE_BASIC:
         Basice Mode 
        //CU_basic_set_mode(CU_BRM_VERBOSE);
        //CU_basic_run_tests();
        break;
    case MODE_CONSOLE:
        Console Mode 
        CU_console_if_run_all_tests();
        break;
    case MODE_CURSES:
        Curses Mode 
        //CU_curses_run_tests();
        break;
    default:
        abort();
}
*/

void ut_running()
{
    switch (s_run_op) {
        case RUN_OP_RUN_ALL:
            CU_console_if_run_all_tests();
            break;
        case RUN_OP_SHOW_ALL:
            CU_console_if_show_all_tests();
            break;
        case RUN_OP_RUN_SUITE:
            CU_console_if_run_suite(s_suitname);
            break;
        case RUN_OP_RUN_SUITE_CASE:
            CU_console_if_run_suite_case(s_suitname, s_casename);
            break;
        case RUN_OP_RUN_RAW:
            CU_console_run_tests();
            break;
        default:
            abort();
    }
}

int main(int32_t argc, char * argv [])
{
    int32_t ret = -1;

    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    if (parse_argv(argc, argv) < 0)
    {
        return -EINVAL;
    }
    
    if (CU_initialize_registry()) 
    {
      printf("\nInitialization of Test Registry failed.");
      return -CU_get_error();
    }
    
    ret = ut_init();
    if (ret < 0)
    {
        goto out;
    }

    ut_running();

out:
    ut_destory();
    CU_cleanup_registry();

    return 0;
}

#endif

