#ifndef LINKEDLIST
#define LINKEDLIST

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/user.h"

typedef struct linked_list_struct
{
    struct linked_list_struct *next;
    struct linked_list_struct *prev;
    User *user;
} linked_list;

int get_linked_list_size(linked_list *list_link);
linked_list *remove_all_users(linked_list *list_link);
linked_list *remove_user(linked_list *list_link, User *user);
User *find_user(linked_list *list_link, char *name);
User *find_user_by_socket(linked_list *list_link, int socket);
linked_list *add_user(linked_list *list_link, User *user);

#endif


