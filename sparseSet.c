#include "containers.h"


void sparseSet_construct(SparseSet *const s, uint16_t const elementSize, uint32_t const elementCount)
{
	*s = (SparseSet){
		.sparse = checl_malloc(elementSize * elementCount),
		.sparseCapacity = elementCount,

		.dense = checl_malloc(elementSize * elementCount),
		.denseCapacity = elementCount,
		.denseSize = 0
	};
}


void sparseSet_destruct(SparseSet const *const s)
{
	checl_free(s->sparse);
	checl_free(s->dense);
}


void dsparseSet_construct(DSparseSet *const s, uint16_t const elementSize, uint16_t const dataSize, uint32_t const elementCount)
{
	*s = (DSparseSet){
		.sparse = checl_malloc(elementSize * elementCount),
		.sparseCapacity = elementCount,

		.data = checl_malloc(elementCount * dataSize),
		.dense = checl_malloc(elementSize * elementCount),
		.denseCapacity = elementCount,
		.denseSize = 0
	};
}


void dsparseSet_destruct(DSparseSet const *const s)
{
	checl_free(s->sparse);
	checl_free(s->dense);
	checl_free(s->data);
}