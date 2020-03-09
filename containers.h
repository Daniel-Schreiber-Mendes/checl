#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#define CHECL_DEBUG


#ifdef CHECL_DEBUG
	#define checl_assert(expr)\
		if (!(expr))\
		{\
			printf("Checl-Assertion: %s failed. Line: %u, File: %s\n", #expr, __LINE__, __FILE__);\
			exit(-1);\
		}

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
	#define free_debug(p) free(p)
	#define malloc_debug(size) malloc(size)
	#define calloc_debug(num, size) calloc(num, size)
	#define checl_assert(expr) (void)0
#endif



typedef struct
{
	void *data; 
	uint16_t capacity;
	uint16_t size; //number of elements currently present in the vector
	uint16_t elementSize;
}
Vector;


typedef struct
{
	void *data;
	uint16_t capacity;
	uint16_t size;
	uint16_t elementSize;
}
Stack;


typedef struct
{
	uint16_t capacity;
	uint16_t size;
	uint16_t elementSize;
	void **data;
}
HashMap;

//####################################################################### vector ####################################################
void	vector_construct(Vector *const vec, uint16_t const elementSize);
void 	vector_destruct(Vector const *const vec);
void    vector_reserve(Vector *const vec, uint16_t const newCapacity);



#define vector_element_push(vec, Type, element)\
	if ((vec)->size == (vec)->capacity)\
	{\
		(vec)->data = realloc((vec)->data, (vec)->elementSize * (vec)->capacity * 2);\
		(vec)->capacity *= 2;\
	}\
	((Type*)(vec)->data)[(vec)->size++] = element;


#define vector_at(vec, index)\
	({\
		(vec)->entitys[index];\
	})

#define vector_foreach(vec, Type, element)\
	Type element = ((Type*)(vec)->data)[0];\
	for (uint16_t i=0; i < (vec)->size; element = ((Type*)(vec)->data)[i + 1], ++i)


#define vector_element_erase(vec, Type, element)\
	{\
	vector_foreach(vec, Type, currentElement)\
		if (currentElement == element)\
		{\
			memmove((vec)->data + (vec)->elementSize * i,\
				    (vec)->data + (vec)->elementSize * (i + 1),\
					(vec)->elementSize * ((vec)->capacity - i - 1));\
			--(vec)->size;\
			break;\
		}\
	} //everything wrapped in curly braces to limit the scope of the variable declared in vector_forach	

/*
#define vector_element_erase_swap(vec, Type, index)\
	(
		//&(vec)->data =
	)*/


#define vector_element_pop(vec, Type)\
	{\
		Type const retVal = ((Type*)(vec)->data)[--(vec)size];\
		retVal;\
	}
	

//############################################################################################################hash stuff
//does compile time hashing of string

void hashMap_construct(HashMap *const m, uint16_t const capacity);
void hashMap_destruct(HashMap const *const m);
void hashMap_pointers_free(HashMap const *const m);

//key has to be a string
#define hashMap_element_insert(map_ptr, key, value)\
	checl_assert((map_ptr)->data[key] == NULL);\
	checl_assert(key < (map_ptr)->capacity);\
	(map_ptr)->data[key] = (value);

#define hashMap_element_get(map_ptr, Type, key)\
	({\
		checl_assert(key < (map_ptr)->capacity);\
		(Type*)(map_ptr)->data[key];\
	})

#define strrng(s, i) (i < (sizeof(s) / sizeof(char)))
#define hashMap_hash(map_ptr, key) (hash(#key) % (map_ptr)->capacity)

#define hash_char(s, i) (strrng(s, i) ? (uint16_t)(s[i] * s[i] * i | s[i] & i * s[i]) : (uint16_t)0)
#define hash(s) (hash_char(s, 0) + hash_char(s, 1) + hash_char(s, 2) + hash_char(s, 3) + hash_char(s, 4) + hash_char(s, 5) + hash_char(s, 6) + \
				hash_char(s, 7) + hash_char(s, 8) + hash_char(s, 9) + hash_char(s, 10) + hash_char(s, 11) + hash_char(s, 12) + hash_char(s, 13))


//##############################################################################################################stack

void	stack_construct(Stack *const stack, uint16_t const elementSize);
void 	stack_destruct(Stack const *const stack);
void    stack_reserve(Stack *const stack, uint16_t const newCapacity);
bool    stack_isEmpty(Stack const *const stack);


#define stack_element_push(stack, Type, element)\
	if ((stack)->size == (stack)->capacity)\
	{\
		(stack)->data = realloc((stack)->data, (stack)->elementSize * (stack)->capacity * 2);\
		(stack)->capacity *= 2;\
	}\
	((Type*)(stack)->data)[(stack)->size++] = element; //set element THEN increment size

#define stack_element_pop(stack, Type)\
	({\
		Type const retVal = ((Type*)(stack)->data)[--(stack)->size];\
		retVal;\
	})

#endif