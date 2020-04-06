#include "containers.h"


typedef struct
{
	int x[10];
}Type;


int main()
{
	Vector v;

	vector_construct(&v, sizeof(int));
	vector_push_back(&v, int, 1);
	vector_push_back(&v, int, 2);
	vector_push_back(&v, int, 3);
	vector_push_back(&v, int, 4);


	vector_erase(&v, int, 3);

	vector_foreach(&v, int, i)
	{
		printf("%i\n", i);
	}

	vector_destruct(&v);
	return 0;
}