#include "headers/linked_list.h"

int get_linked_list_size(linked_list *list_link){
    int size = 0;
    linked_list *elt = list_link;
    while (elt) {
        size++;
        elt = elt->next;
    }
    return size;
}

linked_list *remove_all_users(linked_list *list_link){
    linked_list *elt = list_link;
    linked_list *next_elt = NULL;
    while (elt) {
        next_elt = elt->next;
        free(elt->user);
        elt->prev = NULL;
        elt->next = NULL;
        elt = next_elt;
    }
    return list_link;
}

linked_list *find_user_list(linked_list *list,User *user){
    linked_list *elt = list;
    while (elt) {
        if (elt->user == user) {
            return elt;
        }
    }
    return NULL;
}

linked_list *remove_user(linked_list *list_link,User *user){
    linked_list *elt = find_user_list(list_link,user);
    if (!elt){
        return NULL;
    }
    else if (elt == list_link){
        list_link->prev = NULL;
        list_link = elt->next;
        free(elt->user);
        free(elt);
        return list_link;
        
    }
    linked_list *next_elt = elt->next;
    linked_list *prev_elt = elt->prev;
    free(elt->user);
    elt->prev = NULL;
    elt->next = NULL;
    if (next_elt){
        next_elt->prev = prev_elt;
    }
    if (prev_elt){
        prev_elt->next = next_elt;
    }
    free(elt);
    return list_link;
}

User *find_user(linked_list *list_link,char *name){
    linked_list *elt = list_link;
    while (elt != NULL) {
        if (strcmp(elt->user->pseudo, name) == 0) {
            return elt->user;
        }
        elt = elt->next;
    }
    return NULL;
}

User *find_user_by_socket(linked_list *list_link,int socket){
    linked_list *elt = list_link;
    while (elt != NULL) {
        if (elt->user->socket == socket) {
            return elt->user;
        }
        if (elt->next == NULL){
            break;
        }
        else{
            elt = elt->next;
        }
    }
    return NULL;
}

linked_list *add_user(linked_list *list_link,User *user){
    linked_list *elt = malloc(sizeof(struct linked_list_struct));
    elt->user = user;
    elt->next = NULL;
    elt->prev = NULL;
    if (list_link == NULL) {
        list_link = elt;
        list_link->prev = NULL;
        list_link->next = NULL;
        return list_link;
    }
    elt->next = list_link;
    elt->next->prev = elt;
    return elt;
}

