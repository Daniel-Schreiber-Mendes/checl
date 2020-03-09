

LFLAGS = -shared -o#flags for linking
CFLAGS = -Wall -Werror -g -fpic -c -std=c99#flags for compilation


make: 						  vector.o stack.o hashMap.o
	gcc $(LFLAGS) libchecl.so vector.o stack.o hashMap.o
	mv libchecl.so /usr/local/lib/
	cp *.h /usr/local/include/checl/

vector.o: vector.c
	gcc $(CFLAGS) vector.c

stack.o: stack.c
	gcc $(CFLAGS) stack.c

hashMap.c: hashMap.c
	gcc $(CFLAGS) hashMap.c



test: test.o
	gcc -o test test.o -lchecl
	./test

test.o: test.c
	gcc -c -std=c99 test.c