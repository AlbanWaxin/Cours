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
    char message[1024+1];
    int nb_char,m; 
    //Socket creation
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        stop("socket");
    }
    //Socket options
    struct linger so_linger;
        so_linger.l_onoff = 1;
        so_linger.l_linger = 30 ;
    setsockopt(sockfd,SOL_SOCKET,SO_LINGER,&so_linger,sizeof(so_linger));

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);    
    
    if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))!= 0){
        stop("bind");
    }

    if(listen(sockfd,5)==-1){
        stop("listen");
    }

    int cli_len = sizeof(client_addr);
    int clifd;
    if ((clifd =accept(sockfd,(struct sockaddr*)&client_addr,(socklen_t * restrict)&cli_len))<0){
            stop("accept");
        }
    for (int i = 0; i < 1000; i++)
    {
        
        bzero(message,sizeof(message));
        if ((nb_char = recv(clifd,message,sizeof(message),0)) < 0){
            stop("recv");
        }
        if(nb_char > 0){
            printf("%s \n",message);
        }
        if ((m = send(clifd,message,strlen(message),0))<0){
            stop("send");
        }
        
    }
    close(clifd);
    close(sockfd);
    return 0;    
}