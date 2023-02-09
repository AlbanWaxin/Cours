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
#include "headers/client_handler.h"
#include "headers/message_handler.h"
#include "headers/mdp.h"
#include "headers/treatment_mdp.h"

#define TRUE   1
#define FALSE  0
#define PORT 8888
#define BUFFER_SIZE 1024

char *WELCOME = "Welcome\n";




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

int main(int argc , char *argv[])
{
    int server_socket;
    int addrlen , new_client_socket,activity, i , valread , sd;

    int max_sd;
    struct sockaddr_in address;
    LinkedClient *client_list = NULL;
    mdp_list *mdp_list;
    mdp_list = initiate_list_through_file(mdp_list);
    char *receive_message = malloc(BUFFER_SIZE+1);
    fd_set readfds;
    server_socket = sock_generator(8000);
	
    if (listen(server_socket, 3) < 0) //let 3 connection come in
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    addrlen = sizeof(address);
	while(TRUE) 
    {
        //clear the socket set
        FD_ZERO(&readfds);
        FD_SET(server_socket, &readfds);
        max_sd = server_socket;
		
        //add child sockets to set
        LinkedClient * elt1 = client_list;
        while (elt1 != NULL){
            int sd = elt1->client->socket;
            FD_SET( sd , &readfds);
            if(sd > max_sd){ // change the max when the number of clients increase
				max_sd = sd;
            }
            elt1 = elt1->next;
        }
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL); // get anything new
        if ((activity < 0) && (errno!=EINTR)) 
        {
            printf("select error");
        }
         
        //check where the action happened    
        if (FD_ISSET(server_socket, &readfds)) //server side
        {
            if ((new_client_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_client_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
            if( send(new_client_socket, WELCOME, strlen(WELCOME), 0) != strlen(WELCOME) ) 
            {
                perror("send");
            }
             
            puts("Welcome message sent successfully");
            Client * client = create_client("STILL_LOGIN",new_client_socket);
            if(client != NULL)
            {
                client_list = new_linked_client(client,client_list);
            }
        }
        LinkedClient * elt = client_list;
        while (elt != NULL){
            if(FD_ISSET(elt->client->socket, &readfds))
            {
                printf("Event from client: %s, socket:%d \n",elt->client->pseudo,elt->client->socket);
                bzero(receive_message,BUFFER_SIZE+1);
                if ((valread = read(elt->client->socket, receive_message,BUFFER_SIZE)) == 0)
                {
                    getpeername(elt->client->socket , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
                    close(elt->client->socket);
                    elt->client->socket = -1;
                    elt->client->pseudo ="";
                }
                else 
                {   
                    Receiving_Message * message = create_receive_message(elt->client,receive_message);
                    treat_receive_message(message,server_socket,client_list,&mdp_list);
                }
            }
            elt = elt->next;
        }
    }
     
    return 0;
}