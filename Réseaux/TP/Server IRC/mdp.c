#include "headers/mdp.h"

logins* read_file(const char *file_name, int *n) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier %s\n", file_name);
        return NULL;
    }

    char line[256];

    // Allouer un tableau pour stocker les couples pseudo-mot de passe
    logins *logs = malloc(sizeof(logins));
    int log_count = 0;

    while (fgets(line, sizeof(line), file)) {
        logins log;
        if (sscanf(line, "%s %s", log.pseudo, log.password) == 2) {
            // Ajouter le couple pseudo-mot de passe au tableau
            logs = realloc(logs, sizeof(logins) * (log_count + 1));
            logs[log_count] = log;
            log_count++;
        }
    }
    fclose(file);
    *n = log_count;
    return logs;
}

void write_file(logins *logs, const char *file_name){
    FILE *file = fopen(file_name,"w");
    char* buf = malloc(strlen(file->pseudo)+strlen(file->password)+1);
    int size = sizeof(logs);
    for (int k = 0 , k< size ; k++){
        buf = strncpy(buf, logs[k]->pseudo,strlen(logs[k]->pseudo));
        buf = strncat(buf, " ",1);
        buf = strncat(buf, logs[k]->password,strlen(logs[k]->password));
        buf = strncat(buf, "\n",1);
        fwrite(buf,sizeof(char),strlen(buf),file);
    }
    free(buf);
    fclose(file);
}

void add_logins_to_tab(logins *logs, const char *pseudo,const char *password){
    logins *log = malloc(sizeof(logins));
    log->pseudo = strdup(pseudo);
    log->password = strdup(password);
    int size = sizeof(logs);
    int elt_size = sizeof(logins);
    logs = realloc(logs, size + elt_size);
    logs[size] = log;
    size += elt_size;
    

}