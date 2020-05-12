#include "containers.h"


typedef struct
{
	int x[10];
}Type;


int main()
{
	{
		Vector v;
		vector_construct(&v, sizeof(int));

		vector_push_back(&v, int, 1);
		vector_push_back(&v, int, 2);
		vector_push_back(&v, int, 3);
		vector_push_back(&v, int, 4);
		vector_push_back(&v, int, 5);

		vector_erase(&v, int, 1);
		vector_erase(&v, int, 4);

		vector_pforeach(&v, int*, i)
		{
			
		}

		int x = 3;
		checl_assert(vector_find(&v, &x) == 2);

		vector_destruct(&v);
	}

	{
		HashMap m;
		map_construct(&m, 10);


		map_destruct(&m);
	}


	return 0;
}