#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#define CHECL_MEMLOG
#define CHECL_ASSERT

#ifdef CHECL_MEMLOG

	#define checl_malloc(size)\
	({\
		void* retVal = malloc((size));\
		printf("\033[0;34m");\
		printf("Checl-Allocation:   bytes: %.4u | line: %.3i | file: %s\n", (uint16_t)size, __LINE__, __FILE__ );\
		printf("\033[0m");\
		retVal;\
	})


	#define checl_calloc(num, size)\
	({\
		void* retVal = calloc((num), (size));\
		printf("\033[0;34m");\
		printf("Checl-Allocation:   bytes: %.4u | line: %.3i | file: %s\n", (uint16_t)size, __LINE__, __FILE__ );\
		printf("\033[0m");\
		retVal;\
	})

	//changes font color to green, print message, reset font color
	#define checl_free(p)\
	({\
		free((p));\
		printf("\033[0;32m");\
		printf("Checl-Deallocation:               line: %.3i | file: %s\n", __LINE__, __FILE__);\
		printf("\033[0m");\
	})
#else
	#define checl_free(p) free(p)
	#define checl_malloc(size) malloc(size)
	#define checl_calloc(num, size) calloc(num, size)
#endif

#ifdef CHECL_ASSERT
	#define checl_assert(expr)\
		if (!(expr))\
		{\
			printf("Checl-Assertion: %s failed. Line: %u, File: %s\n", #expr, __LINE__, __FILE__);\
			exit(-1);\
		}
#else
	#define checl_assert(expr) (void)0
#endif


typedef struct
{
	void *data; 
	uint16_t cap;
	uint16_t size; //number of elements currently present in the vector
	uint16_t elementSize;
}
Vector;


typedef struct
{
	void *data;
	uint16_t cap;
	uint16_t size;
	uint16_t elementSize;
}
Stack;


typedef uint16_t HashKey;
typedef struct
{
	HashKey cap;
	void **data;
}
HashMap;


typedef struct List List;
struct List
{
	List *next;
	void *data;
};


typedef struct
{
	void *sparse;
	uint32_t sparseCapacity;

	void *dense;
	uint32_t denseCapacity;
	uint32_t denseSize;
}
SparseSet;


//####################################################################### vector ####################################################
void vector_construct(Vector *vec, uint16_t elementSize);
void vector_destruct(Vector const *vec);
void vector_reserve(Vector *vec, uint16_t new_cap);
void vector_clear(Vector *vec);
int  vector_find(Vector const *vec, void const *data);
int  vector_subset_find(Vector const *vec, void const *data, uint16_t size, uint16_t offset);


#define vector_push_back(vec, Type, element)\
	if ((vec)->size == (vec)->cap)\
		(vec)->data = realloc((vec)->data, (vec)->elementSize * ((vec)->cap *= 2));\
	((Type*)(vec)->data)[(vec)->size++] = element;


#define vector_at(vec, Type, index) (((Type*)(vec)->data)[index])

#define vector_vforeach(vec, Type, alias)\
	Type alias = ((Type*)(vec)->data)[0];\
	for (uint16_t i=0; i < (vec)->size; alias = ((Type*)(vec)->data)[++i])

#define vector_pforeach(vec, Type, alias)\
	Type alias = &((Type)(vec)->data)[0];\
	for (uint16_t alias##i=0; alias##i < (vec)->size; alias = &((Type)(vec)->data)[alias##i + 1], ++alias##i)

#define vector_back_get(vec, Type) ({ (vec)->size > 0 ? &((Type*)(vec)->data)[(vec)->size - 1] : NULL; })

#define vector_erase(vec, Type, index)\
	{\
		checl_assert(index >= 0);\
		if ((vec)->size > 1)\
			memmove(&((Type*)(vec)->data)[index], &((Type*)(vec)->data)[index + 1], ((vec)->size-- - (index - 1)) * (vec)->elementSize);\
		else\
			(vec)->size = 0;\
	}

#define vector_unordered_erase(vec, Type, index)\
	{\
		checl_assert(index >= 0);\
		checl_assert(index < (vec)->size);\
		if (--(vec)->size > 0)\
			((Type*)(vec)->data)[index] = ((Type*)(vec)->data)[(vec)->size];\
	}

#define vector_pop_back(vec, Type)\
	{\
		Type const retVal = ((Type*)(vec)->data)[--(vec)size];\
		retVal;\
	}
	

//############################################################################################################hash stuff
//does compile time hashing of string

void    hashMap_construct(HashMap *m, uint16_t cap);
void    hashMap_destruct(HashMap const *m);
void    hashMap_pointers_free(HashMap const *m);

//key has to be a string
#define hashMap_insert(map_ptr, key, value)\
	checl_assert((map_ptr)->data[key] == NULL);\
	checl_assert(key < (map_ptr)->cap);\
	(map_ptr)->data[key] = (value);

#define hashMap_get(map_ptr, Type, key)\
	({\
		checl_assert(key < (map_ptr)->cap);\
		(Type*)(map_ptr)->data[key];\
	})

//iterates over all elements that are not NULL
#define hashMap_foreach(map_ptr, Type, alias, expr)\
	({\
		Type alias;\
		uint16_t alias##i=0;\
		while (alias##i < (map_ptr)->cap)\
		{\
			if (((Type*)(map_ptr)->data)[alias##i]) { alias = ((Type*)(map_ptr)->data)[alias##i++]; }\
			else { ++alias##i; continue; }\
			(expr);\
		}\
	})

#define hashMap_erase(map, key) (map)->data[key] = 0;


//if index is in range of string length
#define hashMap_hash(map_ptr, key) (hash(#key) % (map_ptr)->cap)
#define hash(s) (hash_char(s, 0) + hash_char(s, 1) + hash_char(s, 2) + hash_char(s, 3)  + hash_char(s, 4)  + hash_char(s, 5)  + hash_char(s, 6) + hash_char(s, 7) + hash_char(s, 8) + hash_char(s, 9) + hash_char(s, 10) + hash_char(s, 11) + hash_char(s, 12) + hash_char(s, 13))
#define hash_char(s, i) (i < sizeof(s) ? (uint16_t)(s[i] * i | s[i] & i * s[i] | i) : 0)


//##############################################################################################################stack

void	stack_construct(Stack *s, uint16_t elementSize, uint16_t cap);
void 	stack_destruct(Stack const *s);
void    stack_reserve(Stack *s, uint16_t new_cap);
bool    stack_empty(Stack const *s);


#define stack_push(stack, Type, element)\
	if ((stack)->size == (stack)->cap)\
	{\
		(stack)->data = realloc((stack)->data, (stack)->elementSize * ((stack)->cap *= 2));\
	}\
	((Type*)(stack)->data)[(stack)->size++] = element;


//accesses top element and then removes it
#define stack_pop(stack, Type)\
	({\
		Type const retVal = ((Type*)(stack)->data)[--(stack)->size];\
		retVal;\
	})

//accesses top element
#define stack_top(stack, Type)\
	({\
		Type const retVal = ((Type*)(stack)->data)[(stack)->size - 1];\
		retVal;\
	})


//##############################################################################################################list

//currently can only store pointers

void  list_construct(List *l);
void  list_destruct(List *l);
void  list_push_back(List *l, void *data);
void  list_back(List *l, void* data);
void* _list_get(List *l, uint16_t i);

#define list_get(l_ptr, i, Type) ((Type)_list_get(l_ptr, i))


//#########################################################################################################sparseSet


void sparseSet_construct();
void sparseSet_destruct();

#define sparseSet_insert()\
#define sparseSet_


#endif