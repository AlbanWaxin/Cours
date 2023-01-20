#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "headers/user.h"

char* get_user_pseudo(User *user){
    if(user == NULL){
        return NULL;
    }
    return user->pseudo;
}

void set_user_pseudo(char* new_user_pseudo,User *user){
    if(new_user_pseudo == NULL){
        return;
    }
    else {
        user -> pseudo = new_user_pseudo;
        return;
    }
}

char* get_user_auth_name(User *user){
    if(user == NULL){
        return NULL;
    }
    else {
        return user->auth_name;
    }
}

void set_user_auth_name(char* new_user_auth_name,User *user){
    if(new_user_auth_name == NULL){
        return;
    }
    else {
        user -> auth_name = new_user_auth_name;
        return;
    }
}

int check_user_password(User *user,char *submitted_password){
    if (!submitted_password){
        return -1;
    }
    else {
        return strcmp(user->password,submitted_password) == 0;
    }
}

int move_to_channel(User *user,int channel){
    return -1;
}

User *create_user(char *name,char* password, char *auth_name, int socket){
    User *user = (User *)malloc(sizeof(User));
    user->pseudo = malloc(strlen(name) + 1);
    user->auth_name = malloc(strlen(auth_name) + 1);
    user->password = malloc(strlen(password) + 1);
    strcpy(user->auth_name,auth_name);
    strcpy(user->pseudo,name);
    strcpy(user->password,password);
    user->socket = socket;
    user->channel = -1;
    return user;
}