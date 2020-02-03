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

//####################################################################################################Macro Magic


#define BX_foreach(Join,What, ...) BX_foreach_(BX_argc(__VA_ARGS__), Join, What, __VA_ARGS__)

#define BX_foreach_(N, Join, What, ...) BX_paste(BX_cat(BX_foreach_, N)(Join, What, __VA_ARGS__))
#define BX_cat(X,Y)  BX_cat_(X,Y) //{{{
#define BX_cat_(X,Y) X##Y //}}}
#define BX_call_first(Fn,...) Fn ( __VA_ARGS__ )
#define BX_paste(...) __VA_ARGS__

#define BX_argc(...) BX_argc_(X,__VA_ARGS__) //{{{
#define BX_argc_(...) BX_argc__(,__VA_ARGS__,8,7,6,5,4,3,2,1,0,0)
#define BX_argc__(_,_0,_1,_2,_3,_4,_5,_6,_7,_8,Cnt,...) Cnt //}}}
#define BX_foreach_1(Join, What,  x) BX_call_first(What,  x)
#define BX_foreach_2(Join, What,  x,...)BX_call_first(What,x) Join BX_foreach_1(Join, What,  __VA_ARGS__)
#define BX_foreach_3(Join, What,  x,...)BX_call_first(What,x) Join BX_foreach_2(Join, What,  __VA_ARGS__)
#define BX_foreach_4(Join, What,  x,...)BX_call_first(What,x) Join BX_foreach_3(Join, What,  __VA_ARGS__)
#define BX_foreach_5(Join, What,  x,...)BX_call_first(What,x) Join BX_foreach_4(Join, What,  __VA_ARGS__)
#define BX_foreach_6(Join, What,  x,...)BX_call_first(What,x) Join BX_foreach_5(Join, What,  __VA_ARGS__)
#define BX_foreach_7(Join, What,  x,...)BX_call_first(What,x) Join BX_foreach_6(Join, What,  __VA_ARGS__)


#endif