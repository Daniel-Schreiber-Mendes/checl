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
	void* data; 
	uint16_t capacity;
	uint16_t size; //number of elements currently present in the vector
	size_t elementSize;
}Vector;


typedef struct
{
	void* data;
	uint16_t capacity;
	uint16_t size;
	size_t elementSize;
}Stack;

//####################################################################### vector ####################################################
void	vector_construct(Vector *const vec, size_t const elementSize);
void 	vector_destruct(Vector const *const vec);
void    vector_reserve(Vector *const vec, uint16_t const newCapacity);


#define vector_element_insert(vec, Type, index, element)\
	if (index >= (vec)->capacity)\
	{\
		(vec)->data = realloc((vec)->data, (vec)->elementSize * (index + 8));\
		(vec)->capacity = index + 8;\
	}\
	((Type*)(vec)->data)[index] = element;

#define vector_element_push(vec, Type, element)\
	if ((vec)->size == (vec)->capacity)\
	{\
		(vec)->data = realloc((vec)->data, (vec)->elementSize * (vec)->capacity * 2);\
		(vec)->capacity *= 2;\
	}\
	((Type*)(vec)->data)[(vec)->size++] = element;


#define vector_size_increment(vec)\
	if ((vec)->size++ == (vec)->capacity)\
	{\
		(vec)->data = realloc((vec)->data, (vec)->elementSize * (vec)->capacity * 2);\
		(vec)->capacity *= 2;\
	}\

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

#define vector_element_pop(vec, Type)\
	{\
		Type const retVal = ((Type*)(vec)->data)[--(vec)size];\
		retVal;\
	}
	

//############################################################################################################hash stuff
//does compile time hashing of string

#define   H1(s, i, x) (x * 65599u + (uint8_t)s[(i) < sizeof(s) ? sizeof(s) - 1 - (i) : sizeof(s)])
#define   H4(s, i, x) H1(s, i, H1(s, i + 1, H1(s, i + 2, H1(s, i + 3, x))))
#define  H16(s, i, x) H4(s, i, H4(s, i + 4, H4(s, i + 8, H4(s, i + 12, x))))
#define  H64(s, i, x) H16(s, i, H16(s, i + 16, H16(s, i + 32, H16(s, i + 48, x))))
#define H256(s, i, x) H64(s, i, H64(s, i + 64, H64(s, i + 128, H64(s, i + 192, x))))
#define hash(s)       ((uint32_t)(H256(s, 0, 0) ^ (H256(s, 0, 0) >> 16)))


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