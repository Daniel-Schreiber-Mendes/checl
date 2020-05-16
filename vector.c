#include "containers.h"
#include <stdlib.h>


void vector_construct(Vector *const vec, uint16_t const elementSize)
{
	vec->data = checl_malloc(elementSize);
	vec->cap = 1;
	vec->size = 0;
	vec->elementSize = elementSize;
}


void vector_destruct(Vector const *const vec)
{
	checl_assert(vec->data);
	checl_free(vec->data);
}


void vector_reserve(Vector *const vec, uint16_t const new_cap)
{
	vec->data = realloc(vec->data, vec->elementSize * new_cap);
	vec->cap = new_cap;
}


void vector_clear(Vector *const vec)
{
	vec->size = 0;
}


int vector_find(Vector const *const vec, void const *const data)
{
	void *element = vec->data;
	for (uint16_t i=0; i < vec->size; element = vec->data + ++i * vec->elementSize)
	{
		if (!memcmp(element, data, vec->elementSize))
		{
			return i; //index of the item so one can access the vector there
		}
	}
	return -1; //if item couldnt be found
}

int vector_subset_find(Vector const *vec, void const *const data, uint16_t const size, uint16_t const offset)
{
	void *element = vec->data;
	for (uint16_t i=0; i < vec->size; element = vec->data + ++i * vec->elementSize)
	{
		if (!memcmp(element + offset, data, size))
		{
			return i; //index of the item so one can access the vector there
		}
	}
	return -1; //if item couldnt be found
}