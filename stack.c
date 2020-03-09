#include "containers.h"
#include <stdlib.h>


void stack_construct(Stack *const stack, uint16_t const elementSize)
{
	stack->data = checl_malloc(elementSize);
	stack->capacity = 1;
	stack->size = 0;
	stack->elementSize = elementSize;
}


void stack_destruct(Stack const *const stack)
{
	checl_free(stack->data); //stack is not responsible for freeing the actual data, just the array
}


void stack_reserve(Stack *const stack, uint16_t const newCapacity)
{
	stack->data = realloc(stack->data, stack->elementSize * newCapacity);
	stack->capacity = newCapacity;
}


bool stack_isEmpty(Stack const *const stack)
{
	return stack->size == 0;
}