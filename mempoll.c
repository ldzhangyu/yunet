#include"mempoll.h"

void * mp_alloc(size_t size)
{
	void *p = NULL;
	
	 p = malloc(size);

	 if(NULL == p) {
		 printf("malloc fail\n");
	 }
	 return p;
}

void * mp_memalign(size_t align, size_t size) 
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
	p->d.last = (u_char *)p + sizeof(mp_pool_t);
	p->d.end = (u_char *)p + size;
	p->d.next = NULL;

	p->max = size - sizeof(mp_pool_t);
	p->current = p;
	p->large = NULL;

	return p;
}


u_char * mp_palloc_block(mp_pool_t *pool, size_t size) 
{
	u_char *m;
	size_t psize;
	mp_pool_t *new;

	psize = (size_t)(pool->d.end - (u_char *)pool);
	if(NULL == (m = mp_memalign(MP_POOL_ALIGNMENT, psize))) {
		return NULL;
	}
	new = (mp_pool_t *)m;
	new->d.end = m + psize;
	new->d.next = NULL;

	m += sizeof(mp_pool_t);
	m = mp_align_ptr(m, MP_ALIGNMENT);
	new->d.last = (u_char *)((size_t)m + size);

	pool->d.next = new;
	return m;
}

u_char * mp_palloc_large(mp_pool_t *pool, size_t size) 
{
	mp_pool_large_t *large;
	void *p = NULL;

	p = mp_alloc(size);
	if(NULL == p) {
		return NULL;
	}

	for(large = poll->large; large != NULL; large = large->next) {
		if (large->alloc == NULL) {
			large->alloc = p;
			return p;
		}
	}
	large = mp_palloc(pool, sizeof(large));
	if(large == NULL) {
		free(p);
		return NULL;
	}

}

u_char * mp_palloc(mp_pool_t *pool, size_t size) 
{
	u_char *m = NULL;
	mp_pool_t * p = pool; 

	if(size < pool->max) {

		// align
		p = p->current;
		do {
			m = mp_align_ptr(p->d.last, MP_ALIGNMENT);
			if(size <= (size_t)(pool->d.end - m)) {
				pool->d.last = m + size;
				return m;
			}
			p = p->d.next;
		}
		while(p != NULL);
			
		// alloc new pool
		return mp_palloc_block(poll, size);
	}
	// use a larger pool
	return mp_palloc_large(poll, size);
}


void mp_ngx_alloc(size_t size)
{

	printf("%s\n", __FUNCTION__);
}
