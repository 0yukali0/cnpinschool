#include<stdio.h> 
#include<sys/types.h> 
#include<netinet/in.h>
#include<sys/socket.h> 
#include<time.h>
#include<string.h> 
#include<unistd.h> 
#include<stdlib.h>
#define PORT 7844
#define MAXLINE 2000

int main(int argc,char *argv[]){
char buf[MAXLINE+1];
int sockfd,len,a;
struct sockaddr_in servaddr,cliaddr;

if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
    printf("Error creating socket\n"); 
    exit(0);
}
printf("UDP Server Socket Created Successfully.\n"); 
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(PORT); 
servaddr.sin_addr.s_addr=htonl(INADDR_ANY); 

if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0){
    perror("Error binding socket."); 
    exit(0);
}
printf("UDP Server Socket Binded.\n"); 

len=sizeof(cliaddr); 
do {
    strcpy(buf," "); 
    if(read(sockfd,buf,MAXLINE)<0){
        perror("ERROR"); 
        exit(0);
    }
    printf("From Client : %s",buf); 

    //send step
    time_t now = time(NULL);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    if(write(sockfd,buf,MAXLINE)<0){
        perror("NOTHING SENT"); 
        exit(0);
    }
    printf("Server : ");

    fgets(buf,sizeof(buf),stdin);
    if(write(sockfd,buf,MAXLINE)<0){
        perror("NOTHING SENT"); 
        exit(0);
    }
} 
while(strcmp(buf," ")!=0); 
close(sockfd); 
return 0;
}
