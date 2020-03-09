#include "containers.h"
#include <stdlib.h>


void hashMap_construct(HashMap *const m, uint16_t const capacity)
{
	m->capacity = capacity * 15;
	m->data = checl_calloc(m->capacity, sizeof(void*));
}


void hashMap_destruct(HashMap const *const m)
{
	checl_free(m->data);
}