#include "containers.h"


typedef struct
{
	int x[10];
}Type;


int main()
{
	HashMap m;
	Type *p = malloc(sizeof(Type));
	p->x[0]= 10;

	hashMap_construct(&m, 6);

	hashMap_element_insert(&m, hashMap_hash(&m, key1), p);
	hashMap_element_insert(&m, hashMap_hash(&m, key2), p);

	hashMap_destruct(&m);
	free(p);
	return 0;
}