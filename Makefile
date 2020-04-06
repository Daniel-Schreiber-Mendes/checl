

LFLAGS = -shared -o#flags for linking
CFLAGS = -Wall -Werror -g -fpic -c -std=c99 -O1#flags for compilation
OBJFILES = vector.o stack.o hashMap.o list.o


make: 						  $(OBJFILES)
	gcc $(LFLAGS) libchecl.so $(OBJFILES)
	mv libchecl.so /usr/local/lib/
	cp *.h /usr/local/include/checl/

vector.o: vector.c
	gcc $(CFLAGS) vector.c

stack.o: stack.c
	gcc $(CFLAGS) stack.c

hashMap.c: hashMap.c
	gcc $(CFLAGS) hashMap.c

list.c: list.c
	gcc $(CFLAGS) list.c



test: test.o
	gcc -o test test.o -lchecl
	./test

test.o: test.c
	gcc -c -std=c99 test.c