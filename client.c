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

#define BACKLOG (10)
#define PORT "9000"
#define MY_MAX_SIZE 500

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in server_addr;
    char s[INET6_ADDRSTRLEN];
    struct addrinfo hints, *res, *p;
    //char *buf = (char *) malloc (MY_MAX_SIZE);
    char buf[MY_MAX_SIZE];

    if (argc !=2) {
    perror("Usage: TCPClient <IP address of the server>");
    return(-1);
    }

    memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;	//any protocol: IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;	//TCP

    if(getaddrinfo(argv[1], PORT, &hints, &res) != 0)
	{
		perror("\ngetaddrinfo");
		return -1;
	}

    for(p = res; p != NULL; p = p->ai_next) 
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
                close(sockfd);
                perror("client: connect");
                continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return -1;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    if (recv(sockfd, buf, MY_MAX_SIZE-1, 0) == -1)
    {
        perror("recv");
        return -1;
    }

    puts(buf);

    freeaddrinfo(res);

}