#include "containers.h"



int main()
{
	HashMap m;
	int *p = malloc(sizeof(int));
	*p = 10;

	hashMap_construct(&m, 200);

	hashMap_element_insert(&m, key1, p);
	hashMap_element_insert(&m, key2, p);

	printf("%i\n", hashMap_element_get(&m, int, key1));
	printf("%i\n", hashMap_element_get(&m, int, key2));

	hashMap_destruct(&m);
	return 0;
}