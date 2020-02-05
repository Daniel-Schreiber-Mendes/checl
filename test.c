#include "containers.h"



int main()
{
	Stack s;
	stack_construct(&s, sizeof(int));

	stack_element_push(&s, int, 1);
	stack_element_push(&s, int, 2);
	stack_element_push(&s, int, 3);

	
	printf("%i\n", stack_element_pop(&s, int));

	stack_destruct(&s);


	for(int i=0; i < 100; ++i)
	{	
		Vector v;
		vector_construct(&v, sizeof(int));
		vector_destruct(&v);
	}
	return 0;
}