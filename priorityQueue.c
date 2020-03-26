#include "containers.h"


void priorityQueue_construct(PriorityQueue *const pc)
{
	pq->data = malloc(pq->data, pq->elementSize * 8);
	pq->prioritys = malloc(pq->data, sizeof *pq->prioritys * (pq->capacity = 8));
	pq->size = 0;
}


void priorityQueue_destruct(PriorityQueue *const pq)
{
	checl_free(pq->data);
	checl_free(pq->prioritys);
}


void priorityQueue_reserve(PriorityQueue *const pq, uint16_t const new_cap)
{
	pq->data = realloc(pq->data, pq->elementSize * new_cap);
	pq->prioritys = realloc(pq->data, sizeof *pq->prioritys * new_cap);
}

