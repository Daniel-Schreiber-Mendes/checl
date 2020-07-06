SRC = vector.c stack.c hashMap.c list.c sparseSet.c
OBJ = $(SRC:.c=.o)
LFLAGS = -shared -o
CFLAGS = -Wall -Werror -g -fpic -c -std=c99

make: $(OBJ)
	gcc $(LFLAGS) libchecl.so $(OBJ) -lchecl
	mv libchecl.so /usr/local/lib/
	cp *.h /usr/local/include/checl/

%.o: %.c
	gcc -c $(CFLAGS) $*.c

test: unit_test.o
	gcc -o unit_test unit_test.o -lchecl
	./test

unit_test.o: unit_test.c
	gcc -c -std=c99 unit_test.c