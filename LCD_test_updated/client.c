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
#include <stdint.h>
#include <arpa/inet.h>
#include <time.h>
#include "wiringPi.h"
#include "lcd.h"


#define D4  (21) 
#define D5  (22)
#define D6  (23)
#define D7  (24)

#define EN  (7)
#define RS  (25)

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
    //struct sockaddr_in server_addr;
    char s[INET6_ADDRSTRLEN];
    struct addrinfo hints, *res, *p;
    //char *buf = (char *) malloc (MY_MAX_SIZE);
     char buf[20];
     
     char card[] = "\xb2\x93\x6a\x1b";//{0xb2, 0x93, 0x6a, 0x1b};


  
    int lcd;
  	wiringPiSetup();
	  pinMode(D4, OUTPUT);
  	pinMode(D5, OUTPUT);
	  pinMode(D6, OUTPUT);
	  pinMode(D7, OUTPUT);
  	pinMode(EN, OUTPUT);
  	pinMode(RS, OUTPUT);

  	lcd = lcdInit(2, 16, 4, RS, EN, D4, D5, D6, D7, 0, 0, 0, 0);
   	lcdClear(lcd);
	  lcdPosition(lcd, 0, 0);
 
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

    if (recv(sockfd, &buf, 50, 0) == -1)
    {
        perror("recv");
        return -1;
    }
    
    int t;
    //buf[4] = '\n';
    for (uint8_t i = 0; i < 4; i++) {
                printf("%02x ", buf[i]);
                if(buf[i] == card[i])
                  t = 1;
                else
                  t=0;
            }
    
    if (t==1)
     lcdPuts(lcd, "Card Valid");

    freeaddrinfo(res);

}