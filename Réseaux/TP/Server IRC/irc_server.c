#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> 
#include "headers/linked_list.h"
#include "headers/traitement_text.h"
 
#define TRUE   1
#define FALSE  0
#define PORT 8888
#define BUFFER_SIZE 1024
#define NAME_BUFFER_SIZE 21

char *NICKNAME = "/NICKNAME";
char *REGISTER = "/REGISTER";
char *UNREGISTER = "/UNREGISTER";
char *EXIT = "/EXIT\n";
char *DATE = "/DATE\n";
char *MP = "/MP";
char *ALERTE = "/ALERTE";
char *ALERTUSER = "/ALERTUSER";
char *SEND = "/SEND";
char *RED = "/RED";
char *GREEN = "/GREEN";
char *YELLOW = "/YELLOW";
char *BLUE = "/BLUE";
char *ORANGE = "/ORANGE";
char *PURPLE = "/PURPLE";
char *PINK = "/PINK";
char *JOIN = "/JOIN";
char *KICK = "/KICK";
char *OP = "/OP";
char *LOGIN = "/LOGIN";
char *PASSWORD = "/PASSWORD";



int sock_generator(int port){
    int opt = TRUE;
    struct sockaddr_in address;
    int fd_socket;
    fd_socket = socket(AF_INET, SOCK_STREAM,0);
    if(fd_socket == -1){
        perror("socket");
        return -1;
    }
    if( setsockopt(fd_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    if(bind(fd_socket, (struct sockaddr *)&address, sizeof(address)) == -1){
        perror("bind");
        return -1;
    }
    return fd_socket;
}

int send_message(char *message,int *size,int client){
    int size_to_send = *size;
    int size_sent=0;
    int c;
    while (size_sent - *size < 0){
        c = send(client, message + size_sent, size_to_send,0);
        if(c == -1){
            perror("my_send");
            break;
        }
        size_sent += c;
        size_to_send -= c;
    }
    *size = size_sent;
    if (c == -1) {return -1;}
    else {return 0;}
}

int send_all(char *message,int *clients_sockets,int max_client,int master_socket,int sender){
    int size = sizeof(clients_sockets);
    int size_message = strlen(message);
    int client;
    for (int i = 0; i < size; i++){
        client  = clients_sockets[i];
        if (client != master_socket && client != 0 && client != sender){
            if (send_message(message, &size_message , client) == -1){
                perror("send_message");
                return -1;
            }
        }
    }
    return 0;
}

void treat_command(char * message,User * user,linked_list * list, int *list_of_client,int i){
    int size_message = strlen(message);
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    if (is_command(message) == 1)
    {
        char * message_copy = malloc(strlen(message)+1);
        strcpy(message_copy,message);
        char ** tab = str_split(message_copy," ",0);
        printf("%s\n",tab[0]);
        if (strncmp(tab[0],NICKNAME,size_message) == 0)
        {
            char* pseudo_temp = tab[1];
            int size_pseudo = strlen(pseudo_temp);
            char** pseudos = str_split(pseudo_temp,"\n",0);
            char* pseudo = pseudos[0];
            size_pseudo = strlen(pseudo);
            int user_pseudo_size = strlen(user->pseudo);
            int comparateur = max(user_pseudo_size,size_pseudo);
            if (strncmp(pseudo,user->pseudo,comparateur) == 0)
            {
                message_send = fuse_strings(pseudo,":  est identique à votre pseudo actuel\n");
                int len = strlen(message_send);
                send_message(message_send,&len,user->socket);
            }
            else if ( find_user(list,pseudo) != NULL)
            {
                message_send = fuse_strings(pseudo,":  est déjà pris\n");
                int len = strlen(message_send);
                send_message(message_send,&len,user->socket);
            }
            else
            {
                user->pseudo = pseudo;
                message_send = fuse_strings(pseudo,":  est dorénavent votre pseudo\n");
                int len = strlen(message_send);
                send_message(message_send,&len,user->socket);
            }
            return;
        }
        else if (strncmp(tab[0],REGISTER,size_message) == 0)
        {
            printf("REGISTER\n");
            
        }
        else if (strncmp(tab[0],UNREGISTER,size_message) == 0)
        {
            printf("UNREGISTER\n");
        }
        else if (strncmp(tab[0],EXIT,size_message) == 0)
        {
            int sd = list_of_client[i];
            message_send = strncpy(message_send,"/QUIT",strlen("/QUIT"));
            int len = strlen(message_send);
            send_message(message_send,&len,user->socket);
            printf("EXIT\n");
            list_of_client[i] = 0;
            user->socket = -1;
            user->pseudo = "";
            close(sd);
            return;
        }
        else if (strncmp(tab[0],DATE,size_message) == 0)
        {
            printf("DATE\n");
        }
        else if (strncmp(tab[0],MP,size_message) == 0)
        {
            printf("MP\n");
            char* pseudo = tab[1];
            User *target_user = find_user(list,pseudo);
            int size = strlen(tab[0]) + strlen(pseudo) + 2;
            message_send = fuse_strings(user->pseudo, "->");
            message_send = fuse_strings(message_send, pseudo);
            message_send = fuse_strings(message_send, ": ");
            message_send = fuse_strings(message_send, message + size);
            int len = strlen(message_send);
            send_message(message_send,&len,target_user->socket);
            return ;
        }
        else if (strncmp(tab[0],ALERTE,size_message) == 0)
        {
            printf("ALERTE\n");
        }
        else if (strncmp(tab[0],ALERTUSER,size_message) == 0)
        {
            printf("ALERTUSER\n");
        }
        else if (strncmp(tab[0],SEND,size_message) == 0)
        {
            printf("SEND\n");
        }
        else if (strncmp(tab[0],RED,size_message) == 0)
        {
            printf("RED\n");
        }
        else if (strncmp(tab[0],GREEN,size_message) == 0)
        {
            printf("GREEN\n");
        }
        else if (strncmp(tab[0],YELLOW,size_message) == 0)
        {
            printf("YELLOW\n");
        }
        else if (strncmp(tab[0],BLUE,size_message) == 0)
        {
            printf("BLUE\n");
        }
        else if (strncmp(tab[0],ORANGE,size_message) == 0)
        {
            printf("ORANGE\n");
        }
        else if (strncmp(tab[0],PURPLE,size_message) == 0)
        {
            printf("PURPLE\n");
        }
        else if (strncmp(tab[0],PINK,size_message) == 0)
        {
            printf("PINK\n");
        }
        else if (strncmp(tab[0],JOIN,size_message) == 0)
        {
            printf("JOIN\n");
        }
        else if (strncmp(tab[0],KICK,size_message) == 0)
        {
            printf("KICK\n");
        }
        else if (strncmp(tab[0],OP,size_message) == 0)
        {
            printf("OP\n");
        }
        else if (strncmp(tab[0],LOGIN,size_message) == 0)
        {
            bzero(message_send,BUFFER_SIZE+1);
            strncpy(message_send,"loginacceptednomdp",strlen("loginacceptednomdp"));
            int len = strlen(message_send);
            char* pseudo_temp = tab[1];
            int size_pseudo = strlen(pseudo_temp);
            char** pseudos = str_split(pseudo_temp,"\n",0);
            char* pseudo = pseudos[0];
            user->pseudo = pseudo;
            send_message(message_send,&len,user->socket);
        }
        else if (strncmp(tab[0],PASSWORD,size_message) == 0)
        {
            printf("Password\n");
        }
    }
    else
    {
        
    }
}


int main(int argc , char *argv[])
{
    int server_socket;
    int addrlen , new_client_socket,activity, i , valread , sd;
	int max_clients = 20 ,list_of_client[20];
    int max_sd;
    struct sockaddr_in address;
    char *message = "Welcome\n";//Welcome message 
    char message_get[BUFFER_SIZE +1];
    char message_get_copy_buffer[BUFFER_SIZE +1];
    char *message_send;
    char *message_send_all;
    message_send = malloc(BUFFER_SIZE +1);
    char name_buffer[NAME_BUFFER_SIZE +1];
    linked_list *list = NULL;
    User *user;

    //set of socket descriptors
    fd_set readfds;
     
    //init server socket
    server_socket = sock_generator(8000);
	
    //try to specify maximum of 3 pending connections for the master socket
    if (listen(server_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
     
    //accept the incoming connection
    addrlen = sizeof(address);
    for (int i = 0; i <max_clients;i++){
        list_of_client[i] = 0;
    }
    puts("Waiting for connections ...");
    
	while(TRUE) 
    {
        //clear the socket set
        FD_ZERO(&readfds);
 
        //add master socket to set
        FD_SET(server_socket, &readfds);
        max_sd = server_socket;
		
        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++) 
        {
            //socket descriptor
			sd = list_of_client[i];
            
			//if valid socket descriptor then add to read list
			if(sd > 0)
				FD_SET( sd , &readfds);
            
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
				max_sd = sd;
        }
 
        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
   
        if ((activity < 0) && (errno!=EINTR)) 
        {
            printf("select error");
        }
         
        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(server_socket, &readfds)) 
        {
            if ((new_client_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
         
            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_client_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
       
            //send new connection greeting message
            if( send(new_client_socket, message, strlen(message), 0) != strlen(message) ) 
            {
                perror("send");
            }
             
            puts("Welcome message sent successfully");
             
            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) 
            {
                //if position is empty
				if( list_of_client[i] == 0 )
                {
                    list_of_client[i] = new_client_socket;
                    printf("Adding to list of sockets as %d\n" , i);
					User *user_creation = create_user("temporary_name","temporary hostname","temporary password",new_client_socket);
                    if(user_creation != NULL)
                    {
                        list = add_user(list,user_creation);
                    }
					break;
                }
            }
        }
        for (i = 0; i < max_clients; i++) 
        {
            sd = list_of_client[i];
            if (FD_ISSET( sd , &readfds)) 
            {
                printf("rentre\n");
                user = find_user_by_socket(list,sd);
                bzero(message_get,BUFFER_SIZE);
                if ((valread = read( sd , message_get, 1024)) == 0)
                {
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                    close( sd );
                    list_of_client[i] = 0;
                }
                else
                {
                    bzero(message_get_copy_buffer,BUFFER_SIZE);
                    strncpy(message_get_copy_buffer,message_get,strlen(message_get));
                    if (is_command(message_get_copy_buffer) == 1){
                        printf("Command_treat\n");
                        treat_command(message_get_copy_buffer,user,list,list_of_client,i);
                    }
                    else
                    {
                        strncpy(name_buffer,user->pseudo,sizeof(name_buffer));
                        bzero(message_send,BUFFER_SIZE);
                        printf("ici1\n");
                        message_send_all = compose_message(name_buffer,message_get_copy_buffer);
                        printf("ici2\n");
                        message_send_all[strlen(message_send_all)+1] = '\0';
                        send_all(message_send_all,list_of_client,max_clients,server_socket,sd);
                    }
                }
            }
        }
    }
     
    return 0;
}