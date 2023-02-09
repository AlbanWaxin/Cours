#ifndef CLHANDLER
#define CLHANDLER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct _Client_ {
    char *pseudo;
    int socket;
    int registered;
    int channel; //useless but useful if channels are implemented
    char *color;
}Client;

Client *create_client(char *pseudo, int socket);
int move_to_channel(Client * client, int channel);


typedef struct _LinkedClient_ {
    Client *client;
    struct _LinkedClient_ *next;
}LinkedClient;

LinkedClient *new_linked_client(Client * client,LinkedClient * client_list);
LinkedClient *remove_linked_client(LinkedClient * client_list, Client * client);

Client *get_client_through_socket(int sock,LinkedClient * client_list);
Client *get_client_through_pseudo(char* pseudo,LinkedClient * client_list);
void print_client(LinkedClient *list);
#endif