#ifndef MHANDLER
#define MHANDLER

#include "../headers/client_handler.h"
#include "../headers/traitement_text.h"
#include "../headers/command_handler.h"
#include "../headers/mdp.h"
#include "../headers/treatment_mdp.h"
#include <sys/types.h>
#include <sys/socket.h>
#include "unistd.h"
#include "string.h"
#include "time.h"

#define CBLACK "\033[0;30m"
#define CRED "\033[0;31m"
#define CGREEN "\033[0;32m"
#define CYELLOW "\033[0;33m"
#define CBLUE "\033[0;34m"
#define CPURPLE "\033[0;35m"
#define CWHITE "\033[0;37m"

#define BUFFER_SIZE 1024

typedef struct _Sending_Message_ {
    Client *author;
    char *time;
    char *header_pseudo_sender;
    char *message;
}Sending_Message;

Sending_Message *create_sending_message(Client *author,char* message);
void format_header_pseudo(Sending_Message *sending_message);
void set_time(Sending_Message *sending_message);
char * format_whole_message(Sending_Message *sending_message);
int send_message(char* message,int *size, int socket);
int send_all(char* message,LinkedClient *client_list,int master_socket, Client * sender);
void send_file(int sock, char* file_name);
void receive_file(int sock, char* file_name,int i);

typedef struct _Receiving_Message_ {
    Client *source;
    char *message;
} Receiving_Message;

Receiving_Message *create_receive_message(Client *source, char * message);
int isCommand(Receiving_Message *receiving_message);
int treat_receive_message(Receiving_Message *receive_message,int master_socket,LinkedClient *client_list,mdp_list **mdp_list);
void treat_command(Receiving_Message *receive_message,LinkedClient * client_list,mdp_list ** mdp_list);


int nick_command(char* pseudo,char*password,Client *client,LinkedClient *client_list,mdp_list **mdp_list);
void exit_command(Client *client,LinkedClient * client_list);
void mp_command(Client *client,LinkedClient * client_list,char* pseudo,char * message,int k);
void login_command(char * pseudo,Client *client,mdp_list **mdp_list,LinkedClient *client_list);
void register_command(char * pseudo,char * password,Client *client,mdp_list **mdp_list);
void unregister_command(char*pseudo,char* password,Client *client,mdp_list **mdp_list);
void date_command(Client *client);
void alerte_command(Client *client,LinkedClient * client_list,char* pseudo,char * message,int k);
void global_alerte_command(Client *client,LinkedClient * client_list,char * message,int k);
void send_command(Client *client,LinkedClient * client_list,char * pseudo,char *fichier,int i);
#endif