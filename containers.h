#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>


typedef struct
{
	void *data; 
	uint16_t capacity;
	uint16_t size; //number of elements currently present in the vector
	size_t elementSize;
}
Vector;


typedef struct
{
	void *data;
	uint16_t capacity;
	uint16_t size;
	size_t elementSize;
}
Stack;


typedef struct
{
	uint16_t capacity;
	uint16_t size;
	size_t elementSize;
	void **data;
}
HashMap;

//####################################################################### vector ####################################################
void	vector_construct(Vector *const vec, size_t const elementSize);
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

void hashMap_destruct(HashMap const *const m);
void hashMap_pointers_free(HashMap const *const m);

//key has to be a string
#define hashMap_construct(map_ptr, cap)\
	(map_ptr)->capacity = cap * 10;\
	(map_ptr)->data = calloc((map_ptr)->capacity, sizeof(void*));

#define hashMap_element_insert(map_ptr, key, value)\
	assert((map_ptr)->data[hash(key) % (map_ptr)->capacity] == NULL);\
	(map_ptr)->data[hash(key) % (map_ptr)->capacity] = (value);

#define hashMap_element_get(map_ptr, type, key)\
	({\
		*((type*)(map_ptr)->data[hash(key) % (map_ptr)->capacity]);\
	})


#define strnlen(s) sizeof(s) / sizeof(char)
#define hash32(s) (strnlen(s) > 1 ?     s[31] * s[31] : 128) + s[31] * 64
#define hash16(s) (strnlen(s) > 1 ? hash32(s) * s[15] : 128) + s[15] * 32
#define hash8(s)  (strnlen(s) > 1 ? hash16(s) * s[7]  : 128) + s[7]  * 16
#define hash4(s)  (strnlen(s) > 1 ? hash8(s) * s[3]   : 128) + s[3]  * 8
#define hash2(s)  (strnlen(s) > 1 ? hash4(s) * s[1]   : 128) + s[1]  * 4
#define hash1(s)  (strnlen(s) > 1 ? hash2(s) * s[0]   : 128) + s[0]  * 2
#define hash(key) (hash1(#key))


//##############################################################################################################stack

void	stack_construct(Stack *const stack, size_t const elementSize);
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