
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#ifndef MEMPOLL_H
#define MEMPOLL_H
#define MP_POOL_ALIGNMENT 16
#define MP_ALIGNMENT sizeof(unsigned long)

#define mp_align_ptr(p, a) (u_char *)(((u_int)p + (a-1)) & ~(a-1))
void mp_ngx_alloc(size_t size);

typedef struct mp_pool_large_s mp_pool_large_t;
struct mp_pool_large_s {
	mp_pool_large_t next;
	void *alloc;
}

typedef struct mp_pool_s mp_pool_t;
typedef struct mp_pool_data_s {
	u_char *last;
	u_char *end;
	mp_pool_t *next;
}mp_pool_data_t;

struct mp_pool_s {
	mp_pool_data_t d;
	size_t max;
	mp_pool_t *current;
	mp_pool_large_t *large;
};

#endif
