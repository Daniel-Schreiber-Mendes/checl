#include "containers.h"
#include <stdlib.h>


void hashMap_construct(HashMap *const m, uint16_t const cap)
{
	m->cap = cap * 20;
	m->data = checl_calloc(m->cap, sizeof m->data);
}


void hashMap_destruct(HashMap const *const m)
{
	checl_free(m->data);
}