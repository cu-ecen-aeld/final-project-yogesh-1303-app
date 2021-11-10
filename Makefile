CC=$(CROSS_COMPILE)gcc

all: test_hello

test_hello: test_hello.c
	$(CC) -o test_hello test_hello.c


clean: 
	rm -f test_hello.o
	rm -f test_hello
