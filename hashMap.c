#include "containers.h"


void hashMap_destruct(HashMap const *const m)
{
	free(m->data);
}