#include "containers.h"
#include <stdlib.h>


void stack_construct(Stack *const s, uint16_t const elementSize, uint16_t const cap)
{
	s->data = checl_malloc((s->elementSize = elementSize) * (s->cap = cap));
	s->size = 0;
}


void stack_destruct(Stack const *const s)
{
	checl_free(s->data); //stack is not responsible for freeing the actual data, just the array
}


void stack_reserve(Stack *const s, uint16_t const new_cap)
{
	s->data = realloc(s->data, s->elementSize * new_cap);
	s->cap = new_cap;
}


bool stack_empty(Stack const *const s)
{
	return s->size == 0;
}