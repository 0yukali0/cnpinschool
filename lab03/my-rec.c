#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define MYPORT "8888"
#define MAXBUFLEN 100

void *get_in_addr(struct sockaddr *sa) {
    //IPv4 
    if(sa->sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa)->sin_addr);
    //IPv6
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void) {
    int sockfd, rv, numbytes;
    char buf[MAXBUFLEN], s[INET6_ADDRSTRLEN];
    socklen_t addr_len;
    struct addrinfo hints, *servinfo, *p;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;
    struct sockaddr_storage their_addr;

    if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for (p = servinfo; p != NULL; p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        //avoid conflict listening or binding port
        if (sockfd == -1) {
            //port is used, try next port.
            perror("listener: socket");
            continue;
        }
        if (bind(sockfd,p->ai_addr,p->ai_addrlen) == -1) {
            //bind fail and clean metadata to avoid conflict.
            close(sockfd);
            perror("listener: bind");
            continue;
        }
        //create a socket success,break.
        break;
    }
    if (p == NULL) {
        fprintf(stderr,"receiver: failed to bind socket");
        return 2;
    }
    freeaddrinfo(servinfo);
    printf("UDP Server Socket Created Successfully.\n");
    printf("UDP Server Socket Binded.\n");
    addr_len = sizeof(their_addr);
    //recv step
    numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr*)&their_addr, &addr_len);
    if (numbytes == -1) {
        perror("recvfrom");
        exit(1);
    }
    buf[numbytes] = '\0';
    printf("From Client : \"%s\"\n",buf);

    //send step
    char buff[20];
    time_t now = time(NULL);
    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", localtime(&now));
    numbytes = sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr*)&their_addr, addr_len);
    if (numbytes == -1) {
        perror("sender: sendto");
        exit(1);
    }
    close(sockfd);
    return 0;
}
