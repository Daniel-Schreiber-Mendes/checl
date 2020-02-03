

LFLAGS = -shared -o#flags for linking
CFLAGS = -Wall -Werror -fpic -c -std=c99#flags for compilation


make: vector.o 
	gcc $(LFLAGS) libchecl.so vector.o
	mv libchecl.so /usr/local/lib/
	cp *.h /usr/local/include/checl/

vector.o: vector.c
	gcc $(CFLAGS) vector.c







test: test.o
	gcc -o test test.o -lchecl
	./test

test.o: test.c
	gcc -c test.c