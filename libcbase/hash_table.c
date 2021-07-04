#include "hash_table.h"




void htable_destory(hash_table_t *tb)
{
    int32_t i = 0;
    hash_node_t *pos = NULL;
    struct hlist_node *tmp = NULL;

    for (i = 0; i < tb->buckets; ++i)
    {
        hlist_for_each_entry_safe(pos, tmp, &tb->hash_head[i], next)
        {
            hlist_del(&pos->next);
            free(pos);
        }
    }

    free(tb->hash_head);
    tb->hash_head = NULL;

}

hash_table_t *htable_new(int32_t buckets, hash_func_t hfunc, cmp_func_t cfunc)
{
    hash_table_t *tb = NULL;
    int32_t i = 0;

    tb = (hash_table_t *)calloc(1, sizeof(hash_table_t));
    if (tb == NULL)
    {
        return NULL;
    }

    tb->buckets = buckets;
    tb->hash_func = hfunc;
    tb->cmp_func = cfunc;

    tb->hash_head = (struct hlist_head *)malloc(buckets * sizeof(struct hlist_head));
    for (i = 0; i < buckets; ++i)
    {
        INIT_HLIST_HEAD(&tb->hash_head[i]);
    }
    
    return tb;
}


hash_node_t *_htable_lookup(hash_table_t *tb, void *key)
{
    int32_t val = -1;
    hash_node_t *pos = NULL;
    struct hlist_node *tmp = NULL;
    
    val = tb->hash_func(tb->buckets, key);

    hlist_for_each_entry_safe(pos, tmp, &tb->hash_head[val], next)
    {
        if (tb->cmp_func(pos->key, key) == 0)
        {
            return pos;
        }
    }

    return NULL;

}

void *htable_lookup(hash_table_t *tb, void *key)
{
    hash_node_t *tmp = NULL;

    tmp = _htable_lookup(tb, key);
    if (tmp == NULL)
    {
        return tmp;
    }

    return tmp->data;
}


int32_t htable_add(hash_table_t * tb, void *key, void *data)
{
    hash_node_t *node = NULL;
    int32_t val = -1;

    //首先需要查找看此数据项是否存在，如果存在则表明重复了，需要返回
    if (htable_lookup(tb, data) != NULL)
    {
        return -EINVAL;
    }
    
    //创建节点，申请内存
    node = (hash_node_t*)calloc(1, sizeof(hash_node_t));

    node->key = key;
    node->data = data;

    val = tb->hash_func(tb->buckets, data);

    hlist_add_head(&node->next, &tb->hash_head[val]);

    return 0;
}

void *htable_del(hash_table_t * tb, void *key)
{
    hash_node_t *tmp = NULL;

    tmp = _htable_lookup(tb, key);
    if (tmp == NULL)
    {
        return NULL;
    }

    hlist_del(&tmp->next);

    return tmp->data;
}

