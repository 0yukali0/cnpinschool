#include<stdio.h> 
#include<sys/types.h> 
#include<netinet/in.h>
#include<sys/socket.h> 
#include<time.h>
#include<string.h> 
#include<unistd.h> 
#include<stdlib.h>
#define PORT 7844

int main(int argc,char *argv[]){
char buf[2000];
int sockfd,len,a;
struct sockaddr_in servaddr,cliaddr;

if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
    printf("Error creating socket\n"); 
    exit(0);
}
printf("UDP Server Socket Created Successfully.\n"); 
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(argv[1]); 
servaddr.sin_addr.s_addr=htonl(INADDR_ANY); 

if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
    perror("Error binding socket."); 
    exit(0);
}
printf("UDP Server Socket Binded.\n"); 

len=sizeof(cliaddr);
bool 
do {
    strcpy(buf," "); 
    if((a=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cliaddr,&len))<0){
        perror("ERROR"); 
        exit(0);
    }
    printf("From Client : %s",buf); 

    //send step
    time_t now = time(NULL);
    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", localtime(&now));
    if((sendto(sockfd,buf,a,0,(struct sockaddr *)&cliaddr,len))<0){
        perror("NOTHING SENT"); 
        exit(0);
    }
    printf("Server : ");

    fgets(buf,sizeof(buf),stdin);
    if((sendto(sockfd,buf,a,0,(struct sockaddr *)&cliaddr,len))<0){
        perror("NOTHING SENT"); 
        exit(0);
    }
} 
while(strcmp(buf," ")!=0); 
close(sockfd); 
return 0;
}