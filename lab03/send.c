#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define SERVERPORT "8888"    // the port users will be connecting to
#define MAXBUFLEN 20
int main(int argc, char *argv[]) {
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    if (argc != 3) {
        fprintf(stderr,"usage: sender hostname message\n");
        exit(1);
    }
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    if ((rv = getaddrinfo(argv[1], SERVERPORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    // loop through all the results and make a socket
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("sender: socket");
            continue;
        }
        break;
    }
    if (p == NULL) {
        fprintf(stderr, "sender: failed to create socket\n");
        return 2;
    }
    printf("UDP Client Socket Created Successfully.\n");
    if ((numbytes = sendto(sockfd, argv[2], strlen(argv[2]), 0,
             p->ai_addr, p->ai_addrlen)) == -1) {
        perror("sender: sendto");
        exit(1);
    }
    freeaddrinfo(servinfo);
    printf("Client : %s\n",argv[2]);
    char buf[MAXBUFLEN];
    struct sockaddr_in cli;
    unsigned int len;
    numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr*)&cli, &len);
    if (numbytes == -1) {
        perror("recvfrom");
        exit(1);
    } else {
        printf("From Server : %s\n",buf);
    }
    close(sockfd);
    return 0;
}
