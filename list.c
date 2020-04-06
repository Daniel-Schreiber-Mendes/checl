#include "containers.h"


void list_construct(List *const l)
{
	l->next = NULL;
}


void list_destruct(List *const l)
{
	if (l->next)
	{
		list_destruct(l->next);
		checl_free(l->next);
	}
}


void list_push_back(List *const l, void *data)
{
	if (l->next)
	{
		list_push_back(l->next, data);
	}
	else
	{
		l->next = checl_calloc(sizeof(List), 1);
		l->next->data = data;
	}
}


void list_back(List *const l, void* data)
{
	if (l->next)
	{
		return list_back(l->next, data);
	}
	else
	{
		l->data = data;
	}
}


void* _list_get(List *const l, uint16_t const i)
{
	return i == 0 ? l->data : _list_get(l->next, i - 1);
}