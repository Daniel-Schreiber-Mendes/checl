#include "containers.h"


typedef struct
{
	int x[10];
}Type;


int main()
{
	Stack s;
	stack_construct(&s, sizeof(int), 1);
	stack_push(&s, int, 5);
	printf("%i\n", stack_pop(&s, int));
	return 0;
}