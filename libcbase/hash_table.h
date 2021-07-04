#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include "head_file.h"
#include "list.h"

//这是一个hash函数指针，对用户来说应该需要使用一个合适的hash函数
//第一个参数unsigned int指的是桶的大小 第二个参数是key值
typedef int32_t (*hash_func_t)(int32_t buckets, void *data);
typedef int32_t (*cmp_func_t)(void *key1, void *key2);


//必须在前面声明typedef
typedef struct
{
	void            *key;							//查找依据
	void            *data;							//数据块，一般是结构体
	struct hlist_node next;
} hash_node_t;


typedef struct 
{
	int32_t     	buckets;						//桶的个数（大小）
	hash_func_t 	hash_func;						//hash函数指针
	cmp_func_t		cmp_func;						//hash函数指针
	struct hlist_head * hash_head; //hash表中存放的链表地址
} hash_table_t;



hash_table_t * htable_new(int32_t buckets, hash_func_t hfunc, cmp_func_t cfunc);

void htable_destory(hash_table_t * tb);

void *htable_lookup(hash_table_t * tb, void * key);

int32_t htable_add(hash_table_t * tb, void *key, void *data);

void *htable_del(hash_table_t * tb, void *key);

#endif

