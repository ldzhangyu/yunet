#include"mempoll.h"

void *mp_memalign(size_t align, size_t size) 
{
	int err;
	void *p;
	err = posix_memalign(&p, align, size);
	if(err){
		printf("posix_memalign fail %u %u\n", align, size);
		p = NULL;
	}

	return p;
}

mp_pool_t * mp_create_pool(size_t size)
{
	mp_pool_t *p = NULL;

	p = mp_memalign(MP_POOL_ALIGNMENT, size);
	if(NULL == p){
		return NULL;
	}
	p->last = (u_char *)p + sizeof(mp_pool_t);
	p->last = (u_char *)p + size;
	p->next = NULL;

	p->max = size - sizeof(mp_pool_t);
	p->current = p;

	return p;
}


void mp_ngx_alloc(size_t size)
{

	printf("%s\n", __FUNCTION__);
}
