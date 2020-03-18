#include "containers.h"
#include <stdlib.h>


void vector_construct(Vector *const vec, uint16_t const elementSize)
{
	vec->data = checl_malloc(elementSize);
	vec->capacity = 1;
	vec->size = 0;
	vec->elementSize = elementSize;
}


void vector_destruct(Vector const *const vec)
{
	checl_assert(vec->data);
	checl_free(vec->data);
}


void vector_reserve(Vector *const vec, uint16_t const newCapacity)
{
	vec->data = realloc(vec->data, vec->elementSize * newCapacity);
	vec->capacity = newCapacity;
}


void vector_clear(Vector *const vec)
{
	vec->size = 0;
}