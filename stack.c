#include "containers.h"


inline void stack_construct(Stack *const stack, size_t const elementSize)
{
	stack->data = malloc(elementSize);
	stack->capacity = 1;
	stack->size = 0;
	stack->elementSize = elementSize;
}


inline void stack_destruct(Stack const *const stack)
{
	free(stack->data); //stack is not responsible for freeing the actual data, just the array
}


inline void stack_reserve(Stack *const stack, uint16_t const newCapacity)
{
	stack->data = realloc(stack->data, stack->elementSize * newCapacity);
	stack->capacity = newCapacity;
}


inline bool stack_isEmpty(Stack const *const stack)
{
	return stack->size == 0;
}