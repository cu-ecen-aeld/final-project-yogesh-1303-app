#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DAEMON

#define BACKLOG (10)
#define PORT "9000"
#define MY_MAX_SIZE 500

struct addrinfo *p;
int socketfd;
int new_fd;
int fd;



void handler()
{
	printf("\ncaught signal, exiting");
	close(fd);
	close(socketfd);
	close(new_fd);	
	freeaddrinfo(p);
	remove("/var/tmp/aesdsocketdata.txt");

}

int main(int argc, char *argv[])
{
	
	struct addrinfo hints;
	struct addrinfo *res;
	//clear the structure instance
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;	//any protocol: IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;	//TCP
	hints.ai_flags = AI_PASSIVE;    //assign address

	// signal(SIGINT, handler);
	// signal(SIGTERM, handler);

	char buf[MY_MAX_SIZE] = "Hello, client";

	//starting the connection with the client using the series of functions
	if(getaddrinfo(NULL, PORT, &hints, &res) != 0)
	{
		perror("\ngetaddrinfo");
		return -1;
	}	

	//converting the IP address into string
	char ipstr[30];
	for(p = res; p != NULL; p = res->ai_next)
	{
		void *addr;
		struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
    	addr = &(ipv4->sin_addr);
		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
	}

	//calling the socket function
	//int socketfd;

	if((socketfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
	{
		perror("\nsocket");
		return -1;
	}

	//bind to a connection
	if(bind(socketfd, res->ai_addr, res->ai_addrlen) != 0)
	{
		perror("\nbind");
		return -1;
	}

	//listen to a connection request from a client
	if(listen(socketfd, BACKLOG) == -1)
	{
		perror("\nlisten");
		return -1;	
	}

	freeaddrinfo(res);

	//accept the connection with the client
	struct sockaddr_storage client_addr;	
	socklen_t addr_size = sizeof(client_addr);
	//int new_fd;

	//char *buf = (char *) malloc(MY_MAX_SIZE);
	while(1)
	{
		if((new_fd = accept(socketfd, (struct sockaddr *)&client_addr, &addr_size)) == -1 )
		{
			perror("\naccept");
			return -1;	
		}
		else
		{
			printf("Connected with the IP: ");
			puts(ipstr);
		} 
		
		if (send(new_fd, buf, MY_MAX_SIZE, 0) == -1)
		{
			perror("send");
			return -1;
		}
	}
	// close(fd);
	// close(socketfd);
	// close(new_fd);	
	// freeaddrinfo(p);
	
	return 0;
}
