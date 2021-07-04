#ifndef _MEMPOOL_H_
#define _MEMPOOL_H_

#define MEM_MALLOC(_size) malloc(_size)
#define MEM_MALLOC0(_size) calloc(1, _size)

#define MEM_CALLOC(_nmemb, _size) calloc(_nmemb, _size)


#define MEM_FREE(_ptr)                                          \
    do                                                          \
    {                                                           \
        if (_ptr)                                               \
        {                                                       \
            free(_ptr);                                         \
            _ptr = NULL;                                        \
        }                                                       \
    } while(0)
    



#endif
