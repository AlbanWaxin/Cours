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
#include "headers/ntprequest.h"

#define MESSAGE_SIZE 1024

void stop(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void myasctime( const struct tm * pTime ) {

    static const char dayNames[7][3] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };

    static const char monthNames[12][3] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    printf("[%.3s %.3s%3d %.2d:%.2d:%.2d %d]",
        dayNames[pTime->tm_wday], monthNames[pTime->tm_mon], pTime->tm_mday, 
        pTime->tm_hour, pTime->tm_min, pTime->tm_sec,
        1900 + pTime->tm_year );
    
    return;
}

char* itoa(int num) {
    int len = snprintf(NULL, 0, "%d", num);
    char* str = malloc(len + 1);
    snprintf(str, len + 1, "%d", num);
    return str;
}

void print_date(){
    time_t now = time(NULL);
    struct tm* now_tm = localtime(&now);
    myasctime(now_tm);
}

int get_size(char* filename){
    FILE* f = fopen(filename, "r");
    if(f == NULL){
        perror("Error opening file");
        return -1;
    }
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fclose(f);
    return size;
}

void send_file(int sock, char* file_name) {
    FILE* fd = fopen(file_name, "r");
    if(fd == NULL) {
        perror("fopen");
        return;
    }

    char* buffer = malloc(1024);
    int n;
    while((n = fread(buffer, 1, sizeof(buffer), fd)) > 0) {
        send(sock, buffer, n, 0);
    }
    fclose(fd);
}

void receive_file(int sock, char* file_name,int i) {
    FILE* fd = fopen(file_name, "w");
    if(fd == NULL) {
        perror("fopen");
        return;
    }
    int count=0;
    char* buffer = malloc(1024);
    int n;
    while((n = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, n, fd);
        count += n;
        if (count >= i)
        {
            break;
        }
    }
    printf("sortie\n");
    fclose(fd);
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
    char* message_input_copy_copy;
    char* pseudo = malloc(MESSAGE_SIZE+1);
    message_input = malloc(MESSAGE_SIZE+1);
    message_output = malloc(MESSAGE_SIZE+1);
    message_input_copy = malloc(MESSAGE_SIZE+1);
    message_input_copy_copy = malloc(MESSAGE_SIZE+1);
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
            if(strncmp(tab[0],"loginaccepted", max(strlen("loginaccepted"),strlen(tab[0])))==0){
                connected = 1;
                break;
            }
        }
    }
    free(message_input_copy);
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
            bzero(message_input_copy_copy,MESSAGE_SIZE+1);
            strncpy(message_input_copy_copy,message_input,strlen(message_input));
            tab =  str_split(message_input_copy_copy," ",0);
            if (strncmp(uppercase(tab[0]),"/SEND",max(strlen("/SEND"),strlen(tab[0])))==0){
            if (has_delimiter(tab[0]) == 0){
                    if (has_delimiter(tab[1]) == 0)
                    {
                        char * fichier_temp = tab[2];
                        char ** fichiers = str_split(fichier_temp,"\n",0);
                        char* i;
                        i = itoa(get_size(fichiers[0]));
                        int mini_i = strlen(" ");
                        strncat(message_input," ",mini_i);
                        strncat(message_input,i,strlen(i));
                    }
            }
            }
            if ((send_message_input = send(sockfd, message_input, strlen(message_input)+2,0))<0){
                perror("send_client");
            }
            if (strncmp(uppercase(tab[0]),"/SEND",max(strlen("/SEND"),strlen(tab[0])))==0){
                if (has_delimiter(tab[0]) == 0)
                {
                    if (has_delimiter(tab[1]) == 0)
                    {
                        char * fichier_temp = tab[2];
                        char ** fichiers = str_split(fichier_temp,"\n",0);
                        send_file(sockfd,fichiers[0]);
                    }
                }
            }
        }
        exit(2);
    }
    else {//pere
        int date_printed = 0;
        char * verif_buffer = malloc(MESSAGE_SIZE);
        for(;;){
            if (quit == 1){
                printf("sortie pere\n");
                exit(0);
            }
            bzero(message_output,MESSAGE_SIZE);
            if ((nb_char = recv(sockfd,message_output,sizeof(message_output),0)) < 0){
               stop("recv");
            }
            if (strrchr(message_output,'\n') == NULL){
                strncat(verif_buffer,message_output,nb_char);
            }
            else {
                strncat(verif_buffer,message_output,nb_char);
                bzero(message_output_copy,MESSAGE_SIZE);
                strncpy(message_output_copy,verif_buffer,strlen(verif_buffer));
                bzero(verif_buffer,MESSAGE_SIZE);
                tab =  str_split(message_output_copy," ",0);
                if (strcmp("/QUIT",tab[0])==0){
                    printf("QUIT\n");
                    quit = 1;
                }
                else if(strncmp(tab[0],"/FILE",max(strlen(tab[0]),strlen("/FILE")))==0)
                {
                    if (has_delimiter(tab[0]) == 0)
                    {
                        char * fichier = tab[1];

                        receive_file(sockfd,fichier,atoi(tab[2]));
                    }    
                }
            }
            if(nb_char > 0){
                //make_ntp_request(); ne fonctionne pas car ne recoit jamais de réponse,sans que je comprenne pourquoi
                if (date_printed == 0){
                    print_date();
                    date_printed = 1;
                }
                printf("%s",message_output);
                if (has_delimiter(message_output) != 0){
                    date_printed = 0;
                    printf("\033[0m");
                }
                
            }
        }
    }
    close(sockfd);
    return 0;    
}