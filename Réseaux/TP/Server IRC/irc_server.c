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
    char name_buffer[NAME_BUFFER_SIZE +1];
    linked_list *list = NULL;
    User *user;

    //set of socket descriptors
    fd_set readfds;
     
    //init server socket
    server_socket = sock_generator(8888);
	
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
         
        //else its some IO operation on some other socket :)
        for (i = 0; i < max_clients; i++) 
        {
            sd = list_of_client[i];
            if (FD_ISSET( sd , &readfds)) 
            {
                user = find_user_by_socket(list,sd);
                //Check if it was for closing , and also read the incoming message
                if ((valread = read( sd , message_get, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                     
                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    list_of_client[i] = 0;
                }
                 
                //Echo back the message that came in
                else
                {
                    strncpy(message_get_copy_buffer,message_get,strlen(message_get));
                    strncpy(name_buffer,user->pseudo,sizeof(name_buffer));
                    message_send = compose_message(name_buffer,message_get_copy_buffer);
                    //set the string terminating NULL byte on the end of the data read
                    message_send[valread+strlen(name_buffer)+1] = '\n';
                    printf("%s\n",message_send);
                    //send(sd , buffer , strlen(buffer) , 0 );
                    send_all(message_send,list_of_client,max_clients,server_socket,sd);
                }
            }
        }
    }
     
    return 0;
}