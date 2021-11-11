CC=$(CROSS_COMPILE)gcc

all: test_hello server

test_hello: test_hello.c
	$(CC) -o test_hello test_hello.c

server: server.c
	$(CC) -o server server.c

clean: 
	rm -f test_hello.o
	rm -f test_hello
	rm -f server.o
	rm -f server
