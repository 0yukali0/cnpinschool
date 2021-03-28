#include<stdio.h>
#include<sys/types.h> 
#include<netinet/in.h> 
#include<sys/socket.h> 
#include<arpa/inet.h>
#include<string.h> 
#include<unistd.h> 
#include<stdlib.h>
#define PORT 7844
#define MAXLINE 2000
int main(int argc,char *argv[]) {
int sockfd,len,port;
struct sockaddr_in serv,cliaddr;

char buff[MAXLINE+1]; 
if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0){
    perror("ERROR creating socket");
    exit(0);
}
printf("UDP Client Socket Created Successfully.\n"); 

memset(&serv,0,sizeof(serv)); 
serv.sin_family=AF_INET; 
port = atoi(argv[2]);
serv.sin_port=htons(port);
if (inet_pton(AF_INET, argv[1], &serv.sin_addr) <= 0) {
	printf("%s fail.",argv[1]);
	exit(0);
}
serv.sin_addr.s_addr=inet_addr(argv[1]);
if(connect(sockfd, (struct sockaddr*)&serv, sizeof(serv))<0) {
    printf("connect error\n");
    exit(0);
}
do{
    printf("Client : ");
    fgets(buff,sizeof(buff),stdin);
    
    write(sockfd, buff, strlen(buff));
    strcpy(buff," ");
    int n;
    n = read(sockfd,buff,MAXLINE);
    buff[n]=0;
    fputs("From Server : ",stdout); 
    fputs(buff,stdout);
    fputs("\n",stdout); 
}while(strcmp(buff," ")!=0);
close(sockfd);
return 0;
}
