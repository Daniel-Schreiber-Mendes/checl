#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


typedef struct
{
	void* data; 
	uint16_t capacity;
	uint16_t size; //number of elements currently present in the vector
	size_t elementSize;
}Vector;

//####################################################################### vector ####################################################
void	vector_construct(Vector *const vec, size_t const elementSize);
void 	vector_destruct(Vector const *const vec);
void    vector_element_pop(Vector *const vec, void *const element);
void* 	vector_data_get(Vector *const vec);
void    vector_reserve(Vector *const vec, uint16_t const newCapacity);


#define vector_element_push(vec, Type, element)\
	if ((vec)->size == (vec)->capacity)\
	{\
		(vec)->data = realloc((vec)->data, (vec)->elementSize * (vec)->capacity * 2);\
		(vec)->capacity *= 2;\
	}\
	((Type*)(vec)->data)[(vec)->size] = element;\
	++(vec)->size;


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
	

//############################################################################################################hash stuff
//does compile time hashing of string

#define   H1(s, i, x) (x * 65599u + (uint8_t)s[(i) < sizeof(s) ? sizeof(s) - 1 - (i) : sizeof(s)])
#define   H4(s, i, x) H1(s, i, H1(s, i + 1, H1(s, i + 2, H1(s, i + 3, x))))
#define  H16(s, i, x) H4(s, i, H4(s, i + 4, H4(s, i + 8, H4(s, i + 12, x))))
#define  H64(s, i, x) H16(s, i, H16(s, i + 16, H16(s, i + 32, H16(s, i + 48, x))))
#define H256(s, i, x) H64(s, i, H64(s, i + 64, H64(s, i + 128, H64(s, i + 192, x))))
#define hash(s)       ((uint32_t)(H256(s, 0, 0) ^ (H256(s, 0, 0) >> 16)))


//############################################################################################################array stuff

#define array_forach(array, Type, element)\


#endif