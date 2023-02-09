#include "./headers/client_handler.h"

Client *create_client(char* pseudo,int socket){
    Client *client = malloc(sizeof(Client));
    client->pseudo = malloc(strlen(pseudo)+1);
    strcpy(client->pseudo,pseudo);
    client->socket = socket;
    client->registered = -1;
    client->channel = -1;
    client->color = "\033[0m";
    return client;
}

int move_to_channel(Client *client,int channel){
    return -1;
}

LinkedClient *new_linked_client(Client * client,LinkedClient * client_list)
{
    LinkedClient *new_client = malloc(sizeof(LinkedClient));
    new_client->client = client;
    new_client->next = client_list;
    return new_client;
}

LinkedClient *remove_linked_client(LinkedClient * client_list,Client * client){
    if(client_list == NULL){
        return NULL;
    }
    if(client_list->client == client){
        LinkedClient *temp = client_list;
        client_list = client_list->next;
        free(temp);
        return client_list;
    }
    else
    {
        LinkedClient *temp = client_list;
        while(temp->next!= NULL){
            LinkedClient *temp2 = temp->next;
            if(temp2->client == client){
                temp->next = temp2->next;
                free(temp2);
                return client_list;
            }
            temp = temp->next;
        }
    }
    return client_list;
}

Client *get_client_through_socket(int sock,LinkedClient * client_list){
    if(client_list == NULL){
        return NULL;
    }
    if(client_list->client->socket == sock){
        return client_list->client;
    }
    LinkedClient *temp = client_list;
    while(temp->next!= NULL){
        LinkedClient *temp2 = temp->next;
        if(temp2->client->socket == sock){
            return temp2->client;
        }
        temp = temp->next;
    }
    return NULL;
}

Client *get_client_through_pseudo(char * pseudo,LinkedClient * client_list){
    int pseudo_size = strlen(pseudo);
    LinkedClient *temp = client_list;
    while(temp != NULL){
        if(strncmp(temp->client->pseudo,pseudo,pseudo_size)==0){
            return temp->client;
        }
        temp = temp->next;
    }
    return NULL;
}

void print_client(LinkedClient *list){
    LinkedClient *elt = list;
    while (elt!= NULL) {
        printf("%s,",elt->client->pseudo);
        elt = elt->next;
    }
    printf("\n");
    return;
}
