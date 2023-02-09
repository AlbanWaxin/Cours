#ifndef MDP
#define MDP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* pseudo;
    char* password;
} logins;

logins *create_login(char* pseudo,char* password);

typedef struct mdp_linked_list
{
    struct mdp_linked_list *next;
    logins *login;
} mdp_list;

int get_mdp_list_size(mdp_list *list);
mdp_list *remove_all_mdps(mdp_list *list);
mdp_list *add_mdp(mdp_list *list, logins* mdp);
mdp_list *find_mdp(mdp_list *list, char *pseudo);
void print_mdps(mdp_list *list);
#endif