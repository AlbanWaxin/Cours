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


void stop(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
    char message[1025];
    char * buf = "PING";
    int nb_char; 
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        stop("socket");
    }
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;
    memset(&clientaddr,0,sizeof(clientaddr));
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(1234);
    int len = sizeof(clientaddr);
    while (1)
    {   
        int m;
        if ((m = sendto(sockfd,buf,strlen(buf),MSG_CONFIRM,(const struct sockaddr *)&clientaddr,(socklen_t)len))<0){
            stop("sendto");
        }
        bzero(message,sizeof(message));
        if ((nb_char = recvfrom(sockfd,message,sizeof(message),MSG_WAITALL,(struct sockaddr*)&clientaddr,(socklen_t *)&len)) < 0){
            stop("recvfrom");
        }
        if(nb_char > 0){
            printf("%s \n %s %d \n",message,inet_ntoa(clientaddr.sin_addr),clientaddr.sin_port);
        }
        sleep(1);
    }
    return 0;
}    