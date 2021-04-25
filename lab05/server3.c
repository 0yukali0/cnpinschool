#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define MAXLINE  256
#define SECOND 1000

void echo_every_sec(int sockfd);
void sig_chld(int signo);

int main(int argc, char **argv)
{
    if (argc < 2) {
       fprintf(stderr,"usage %s port\n", argv[0]);
       exit(0);
    }
    int portno = atoi(argv[1]);
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(portno);
    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd, 5);
    if (signal(SIGCHLD, sig_chld) == SIG_ERR){
        fprintf(stderr, "can't catch SIGCHLD \n");
        exit(0);
    }
    for ( ; ; ){
        clilen = sizeof(cliaddr);
        if ( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0){
            if (errno == EINTR) 
                continue; // back to for()
            else{
                fprintf(stderr, "accept error\n");
                exit(0);
            }
        }

        if ((childpid = fork()) == 0){ // child
	    printf("child go\n");
            close(listenfd); // close listening socket
            echo_every_sec(connfd);// process the request
	    close(connfd);
            exit(0);
        }
        close(connfd); // parent closes connected socket
    }
    return 0;
}

void echo_every_sec(int sockfd)
{
    printf("echo start\n");
    int n, ismore = 0;
    double diff_time = 0;
    time_t last_time,this_time;
    struct tm* time_info;
    char buf[MAXLINE];

    while (1) {
    printf("make\n");
    time(&last_time);
    time_info = localtime(&last_time);
    strftime(buf, MAXLINE, "%H:%M:%S", time_info);
    printf("messge:%s\n",buf);
    n = write(sockfd, buf, strlen(buf));
    printf("n:%d\n",n);
    if (n<0) perror("write socket error");
    printf("sleep\n");
    sleep(100);
    printf("wake up\n");
    }
}

void sig_chld(int signo)
{
    pid_t pid;
    int stat;
    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);// printf() isn't suitable for use here
    return;
}
