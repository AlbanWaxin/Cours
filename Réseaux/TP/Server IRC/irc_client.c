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
#include "headers/traitement_text.h"

#define MESSAGE_SIZE 1024

void stop(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
    if (argc < 3) {
        printf("Mauvais nombre d'argument\n");
        return 1;
    }
    char* message_input;
    char* message_output;
    char* message_output_copy;
    char* message_input_copy;
    char* pseudo = malloc(MESSAGE_SIZE+1);
    message_input = malloc(MESSAGE_SIZE+1);
    message_output = malloc(MESSAGE_SIZE+1);
    message_input_copy = malloc(MESSAGE_SIZE+1);
    message_output_copy = malloc(MESSAGE_SIZE +1);
    char ** tab;
    int nb_char,send_message_input; 
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        stop("socket");
    }
    struct sockaddr_in clientaddr;
    memset(&clientaddr,0,sizeof(clientaddr));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr(argv[2]);
    clientaddr.sin_port = htons(atoi(argv[1]));
    int len = sizeof(clientaddr);
    int n;
    if((n = connect(sockfd,(struct sockaddr*)&clientaddr,len))<0){
        stop("connect");
    }
    bzero(message_output,MESSAGE_SIZE);
    if ((nb_char = recv(sockfd,message_output,sizeof(message_output),0)) < 0){
       stop("recv");
    }
    if(nb_char > 0){
        printf("%s",message_output);
    }
    //Section login
    int connected = 0;
    int step = 0;
    while (connected != 1){
        step = 0;
        if (step ==0){
            bzero(message_input,MESSAGE_SIZE+1);
            bzero(message_input,MESSAGE_SIZE+1);
            printf("Enter Login:\n");
            if (read(STDIN_FILENO,message_input,MESSAGE_SIZE)<0)
            {
                perror("scanf");
            }
            strncpy(pseudo,message_input,strlen(message_input));
            message_input_copy = fuse_strings("/LOGIN ",message_input);
            if ((send_message_input = send(sockfd, message_input_copy, MESSAGE_SIZE,0))<0){
                perror("send_client");
            }
            bzero(message_output,MESSAGE_SIZE);
            if ((nb_char = recv(sockfd,message_output,MESSAGE_SIZE,0)) < 0){
                stop("recv");
            }
            bzero(message_output_copy,MESSAGE_SIZE+1);
            strncpy(message_output_copy,message_output,MESSAGE_SIZE);
            tab =  str_split(message_output_copy," ",0);
            printf("%s\n",tab[0]);
            if(strncmp(tab[0],"loginacceptednomdp", strlen("loginacceptednomdp"))==0){
                connected = 1;
                break;
            }
            else if(strncmp(tab[0],"loginaccepted", strlen("loginaccepted"))==0){
                step = 1;
            }
        }
        if (step ==1){
            bzero(message_input,MESSAGE_SIZE+1);
            bzero(message_input,MESSAGE_SIZE+1);
            printf("Enter Password:\n");
            if (read(STDIN_FILENO,message_input,MESSAGE_SIZE)<0)
            {
                perror("scanf");
            }
            message_input_copy = fuse_strings("/PASSWORD ",pseudo);
            message_input_copy = fuse_strings(message_input_copy,message_input);
            if ((send_message_input = send(sockfd, message_input_copy,MESSAGE_SIZE,0))<0){
                perror("send_client");
            }
            bzero(message_output,MESSAGE_SIZE);
            if ((nb_char = recv(sockfd,message_output,MESSAGE_SIZE,0)) < 0){
                stop("recv");
            }
            bzero(message_output_copy,MESSAGE_SIZE+1);
            strncpy(message_output_copy,message_output,strlen(message_output));
            tab =  str_split(message_output_copy," ",0);
            if(strncmp(tab[0],"mdpaccepted", strlen("mdpaccepted"))==0){
                connected = 1;
            }
        }
    }
    int quit = 0;
    pid_t id = fork();
    if(id < 0){
        perror("fork");
        return 1;
    }
    if(id == 0){ //fils
        for(;;){
            sleep(1);
            bzero(message_input,MESSAGE_SIZE+1);
            if (quit == 1){
                printf("sortie fils\n");
                exit(2);
            }
            if (read(STDIN_FILENO,message_input,MESSAGE_SIZE)<0)
            {
                perror("scanf");
            }
            
            if ((send_message_input = send(sockfd, message_input, strlen(message_input)+2,0))<0){
                perror("send_client");
            }

        }
        exit(2);
    }
    else {//pere
        for(;;){
            if (quit == 1){
                printf("sortie pere\n");
                exit(0);
            }
            bzero(message_output,MESSAGE_SIZE);
            if ((nb_char = recv(sockfd,message_output,sizeof(message_output),0)) < 0){
               stop("recv");
            }
            if(nb_char > 0){
                printf("%s\n",message_output);
                bzero(message_output_copy,MESSAGE_SIZE);
                strncpy(message_output_copy,message_output,strlen(message_output));
                tab =  str_split(message_output_copy," ",0);
                printf("%s\n",tab[0]);
                if (strcmp("/QUIT",tab[0])==0){
                    printf("QUIT\n");
                    quit = 1;
                }
            }
        }
    }
    close(sockfd);
    return 0;    
}