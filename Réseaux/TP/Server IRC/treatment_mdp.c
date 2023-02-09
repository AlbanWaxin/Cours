#include "./headers/treatment_mdp.h"

#define FICHIER "./definitivement_pas_des_mdp.txt"


mdp_list *initiate_list_through_file(mdp_list *list){
    FILE *file = fopen(FICHIER, "r");
    if(file == NULL){
        perror("Error opening file");
        exit(1);
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        logins *log;
        char * pseudo = malloc(21);
        bzero(pseudo,21);
        char * password = malloc(21);
        bzero(password,21);
        if (sscanf(line, "%s %s", pseudo,password) == 2) {
            log = create_login(pseudo, password);
            list = add_mdp(list,log);
        }
        free(pseudo);
        free(password);
    }
    return list;
}

void modify_file(mdp_list *list){
    printf("modify\n");
    FILE *file = fopen(FICHIER, "w");
    if(file == NULL){
        perror("Error opening file");
        exit(1);
    }
    mdp_list *elt = list;
    while(elt!= NULL){
        if(strcmp(elt->login->pseudo,"") != 0){
            fprintf(file,"%s %s\n",elt->login->pseudo,elt->login->password);
        }
        elt = elt->next;
    }
    fclose(file);
    return;
}
