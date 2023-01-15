#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netdb.h>
#include <strings.h>
#include  <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <time.h>
#include "string.h"

#define MESSAGE_SIZE 1025

void stop(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
    char* message_input;
    message_input = malloc(MESSAGE_SIZE);
    char* message_output;
    message_output = malloc(MESSAGE_SIZE);
    int nb_char,send_message_input; 
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        stop("socket");
    }
    struct sockaddr_in clientaddr;
    memset(&clientaddr,0,sizeof(clientaddr));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientaddr.sin_port = htons(8888);
    int len = sizeof(clientaddr);
    int n;
    if((n = connect(sockfd,(struct sockaddr*)&clientaddr,len))<0){
        stop("connect");
    }
    pid_t id = fork();
    if(id < 0){
        perror("fork");
        return 1;
    }
    if(id == 0){ //fils
        for(;;){
            sleep(1);
            bzero(message_input, sizeof(message_input));
            if (read(STDIN_FILENO,message_input,sizeof(message_input))<0)
            {
                perror("scanf");
            }
            if ((send_message_input = send(sockfd, message_input, strlen(message_input),0))<0){
                perror("send_client");
            }
        }
        exit(2);
    }
    else {//pere
        for(;;){
            bzero(message_output,sizeof(message_output));
            if ((nb_char = recv(sockfd,message_output,sizeof(message_output),0)) < 0){
               stop("recv");
            }
            if(nb_char > 0){
                printf("%s",message_output);
            }
        }
    }
    close(sockfd);
    return 0;    
}