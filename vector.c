#include "containers.h"


inline void vector_construct(Vector *const vec, size_t const elementSize)
{
	vec->data = malloc(elementSize);
	vec->capacity = 1;
	vec->size = 0;
	vec->elementSize = elementSize;
}


void vector_destruct(Vector const *const vec)
{
	assert(vec->data);
	free(vec->data);
}


inline void vector_reserve(Vector *const vec, uint16_t const newCapacity)
{
	vec->data = realloc(vec->data, vec->elementSize * newCapacity);
	vec->capacity = newCapacity;
}