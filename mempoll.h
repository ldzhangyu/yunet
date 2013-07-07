
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#ifndef MEMPOLL_H
#define MEMPOLL_H
#define MP_POOL_ALIGNMENT 16
void mp_ngx_alloc(size_t size);

typedef struct mp_pool_s mp_pool_t;


struct mp_pool_s {
	u_char *last;
	u_char *end;
	mp_pool_t *next;
	
	size_t max;
	mp_pool_t *current;
};
#endif
