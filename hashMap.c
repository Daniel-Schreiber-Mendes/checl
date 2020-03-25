#include "containers.h"
#include <stdlib.h>


void hashMap_construct(HashMap *const m, uint16_t const capacity)
{
	m->capacity = capacity * 20;
	m->data = checl_calloc(m->capacity, sizeof m->data);
}


void hashMap_destruct(HashMap const *const m)
{
	checl_free(m->data);
}