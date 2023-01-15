#ifndef USER
#define USER

typedef struct User_Object {
    char *pseudo;
    char *auth_name;
    char *password;
    int socket;
    int channel; //useless but useful if channels are implemented
}User;

char* get_user_pseudo(User *user);
void set_user_pseudo(char * new_user_pseudo, User *user);
char *get_user_auth_name(User *user);
void set_user_auth_name(char * new_user_auth_name,User *user);
int check_user_password(User *user,char* submitted_password);
User *create_user(char *name,char* password, char *auth_name, int socket);

//WIP
int move_to_channel(User *user,int channel);

#endif