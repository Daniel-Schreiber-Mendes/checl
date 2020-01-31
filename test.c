#include "containers.h"



int main()
{
	Vector v;
	vector_construct(&v, sizeof(int));

	vector_element_push(&v, int, 1);
	vector_element_push(&v, int, 2);
	vector_element_push(&v, int, 3);

	vector_element_erase(&v, int, 3);
	vector_element_erase(&v, int, 1);
	
	vector_foreach(&v, int, element)
	{
		printf("%i\n", element);
	}

	vector_destruct(&v);
	return 0;
}