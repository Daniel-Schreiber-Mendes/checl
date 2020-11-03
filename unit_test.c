#include "containers.h"


int main()
{

	{
		DSparseSet set;
		dsparseSet_construct(&set, sizeof(uint16_t), sizeof(char), 20);

		dsparseSet_insert(&set, uint16_t, 0);
		dsparseSet_insert(&set, uint16_t, 2);
		dsparseSet_insert(&set, uint16_t, 6);
		dsparseSet_insert(&set, uint16_t, 30);

		dsparseSet_get(&set, uint16_t, char, 0) = 'a';
		dsparseSet_get(&set, uint16_t, char, 2) = 'b';
		dsparseSet_get(&set, uint16_t, char, 6) = 'c';
		dsparseSet_get(&set, uint16_t, char, 30) = 'd';

		printf("%c\n", dsparseSet_get(&set, uint16_t, char, 0));
		printf("%c\n", dsparseSet_get(&set, uint16_t, char, 2));
		printf("%c\n", dsparseSet_get(&set, uint16_t, char, 6));
		printf("%c\n", dsparseSet_get(&set, uint16_t, char, 30));

		dsparseSet_destruct(&set);
	}
	return 0;
}