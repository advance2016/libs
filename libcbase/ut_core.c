#include "ut_core.h"
#include "list.h"
#include "mempool.h"

static LIST_HEAD(s_list_suit);

typedef struct {
    struct list_head list;
    CU_TestInfo cti;
} case_info_t;


typedef struct {
    struct list_head list;
    CU_SuiteInfo csi;
    struct list_head list_case;
} suit_info_t;

static suit_info_t *ut_find_suit(const char *suitname)
{
    suit_info_t *pos = NULL;
    suit_info_t *si = NULL;

    list_for_each_entry(pos, &s_list_suit, list)
    {
        if (strcmp(suitname, pos->csi.pName) == 0)
        {
            return pos;
        }
    }

    si = (suit_info_t *)MEM_MALLOC0(sizeof(suit_info_t));
    if (si == NULL)
    {
        printf("malloc suit_info_t fail: %s", strerror(errno));
        return NULL;
    }

    si->csi.pName = suitname;
    INIT_LIST_HEAD(&si->list_case);
    
    list_add(&si->list, &s_list_suit);

    return si;
}

void ut_register_setup(const char *suitname, CU_InitializeFunc fun_init)
{
    suit_info_t *si = NULL;

    si = ut_find_suit(suitname);
    if (si == NULL)
    {
        return;
    }

    si->csi.pInitFunc = fun_init;
}

void ut_register_teardown(const char *suitname, CU_CleanupFunc fun_clean)
{
    suit_info_t *si = NULL;

    si = ut_find_suit(suitname);
    if (si == NULL)
    {
        return;
    }

    si->csi.pCleanupFunc = fun_clean;
}


void ut_register_testcase(const char *suitname, const char *casename
                                , CU_TestFunc fun_test)
{
    suit_info_t *si = NULL;
    case_info_t *ci = NULL;

    si = ut_find_suit(suitname);
    if (si == NULL)
    {
        return;
    }

    ci = (case_info_t *)MEM_MALLOC0(sizeof(suit_info_t));
    if (ci == NULL)
    {
        printf("malloc case_info_t fail: %s", strerror(errno));
        return;
    }

    ci->cti.pName = casename;
    ci->cti.pTestFunc = fun_test;

    list_add(&ci->list, &si->list_case);
}


int32_t ut_init()
{
    suit_info_t *pos = NULL;
    CU_pSuite psuit = NULL;
    case_info_t *ci = NULL;
    CU_pTest ptest = NULL;

    list_for_each_entry(pos, &s_list_suit, list)
    {
        psuit = CU_add_suite(pos->csi.pName, pos->csi.pInitFunc
                            , pos->csi.pCleanupFunc);
        if (psuit == NULL)
        {
            return -1;
        }

        list_for_each_entry(ci, &pos->list_case, list)
        {
            ptest = CU_add_test(psuit, ci->cti.pName, ci->cti.pTestFunc);
            if (ptest == NULL)
            {
                return -1;
            }
        }
    }

    return 0;
}


void ut_destory()
{
    suit_info_t *pos = NULL;
    suit_info_t *pos_tmp = NULL;
    case_info_t *ci = NULL;
    case_info_t *ci_tmp = NULL;


    list_for_each_entry_safe(pos, pos_tmp, &s_list_suit, list)
    {
        list_for_each_entry_safe(ci, ci_tmp, &pos->list_case, list)
        {
            list_del(&ci->list);
            MEM_FREE(ci);
        }

        list_del(&pos->list);
        MEM_FREE(pos);
    }
}
