#include "containers.h"


void vector_construct(Vector *const vec, size_t const elementSize)
{
	vec->data = malloc(elementSize);
	vec->capacity = 1;
	vec->size = 0;
	vec->elementSize = elementSize;
}


void vector_destruct(Vector const *const vec)
{
	free(vec->data); //vec is not responsible for freeing the actual data, just the array
}


void vector_element_pop(Vector *const vec, void *const element)
{
	memcpy(element, vec->data + vec->size * vec->elementSize, vec->elementSize);
	--vec->size;
}


void* vector_data_get(Vector *const vec)
{
	return vec->data;
}


void vector_reserve(Vector *const vec, uint16_t const newCapacity)
{
	vec->data = realloc(vec->data, vec->elementSize * newCapacity);
	vec->capacity = newCapacity;
}