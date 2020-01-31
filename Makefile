

make: vector.o 
	gcc -shared -o libchecl.so vector.o
	mv libchecl.so /usr/local/lib/
	cp *.h /usr/local/include/checl/

test: test.o
	gcc -o test test.o -lchecl
	./test

test.o: test.c
	gcc -c test.c

vector.o: vector.c
	gcc -c -Wall -Werror -fpic vector.c