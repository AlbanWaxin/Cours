#include "./headers/mdp.h"

logins *create_login(char *pseudo,char* password){
    logins *log = (logins *)malloc(sizeof(logins));
    log->pseudo = malloc(strlen(pseudo) + 1);
    log->password = malloc(strlen(password) + 1);
    strcpy(log->pseudo,pseudo);
    strcpy(log->password,password);
    return log;
}

int get_mdp_list_size(mdp_list *list){
    int size = 0;
    mdp_list *elt = list;
    while (elt) {
        size++;
        elt = elt->next;
    }
    return size;
}

mdp_list *add_mdp(mdp_list *list, logins * mdp){
    mdp_list *elt = malloc(sizeof(mdp_list));
    elt->login = mdp;
    elt->next = NULL;
    if (list == NULL) {
        list = elt;
        return list;
    }
    elt->next = list;
    return elt;
}

mdp_list *find_mdp(mdp_list *list, char *pseudo){
    mdp_list *elt = list;
    while (elt != NULL) {
        if (strncmp(elt->login->pseudo, pseudo,strlen(pseudo)) == 0) {

            return elt;
        }
        elt = elt->next;
    }
    return NULL;
}

void print_mdps(mdp_list *list){
    mdp_list *elt = list;
    while (elt!= NULL) {
        printf("%s,",elt->login->pseudo);
        elt = elt->next;
    }
    printf("\n");
    return;
}


