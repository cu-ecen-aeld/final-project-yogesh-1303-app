CC=$(CROSS_COMPILE)gcc

all: test_hello server client

test_hello: test_hello.c
	$(CC) -o test_hello test_hello.c

server: server.c
	$(CC) -o server server.c

client: client.c
	$(CC) -o client client.c

clean: 
	rm -f test_hello.o
	rm -f test_hello
	rm -f server.o
	rm -f server
	rm -f client.o
	rm -f client
