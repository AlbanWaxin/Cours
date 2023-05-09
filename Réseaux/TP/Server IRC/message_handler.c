#include "./headers/message_handler.h"

char* itoa(int num) {
    int len = snprintf(NULL, 0, "%d", num);
    char* str = malloc(len + 1);
    snprintf(str, len + 1, "%d", num);
    return str;
}

Sending_Message *create_sending_message(Client *author,char *message){
    Sending_Message *msg = (Sending_Message*)malloc(sizeof(Sending_Message));
    char * msg1 = (char*)malloc(strlen(message)+1);
    bzero(msg1,strlen(message)+1);
    strncpy(msg1,message,strlen(message));
    msg->author = author;
    msg->message = msg1;
    msg->time = "";
    msg->header_pseudo_sender = "";
    return msg;
}

void format_header_pseudo(Sending_Message *sending_message){
    int pseudo_size = strlen(sending_message->author->pseudo);
    char * buffer = (char*)malloc(pseudo_size+2);
    bzero(buffer,pseudo_size+2);
    strncpy(buffer, sending_message->author->pseudo,pseudo_size);
    strcat(buffer,": ");
    sending_message->header_pseudo_sender = buffer;
}

void set_time(Sending_Message *sending_message){
    return;
}



char *format_whole_message(Sending_Message *sending_message){
    int size_pseudo = strlen(sending_message->header_pseudo_sender);
    int size_time = strlen(sending_message->time);
    int size_msg = strlen(sending_message->message);
    char * buffer_pseudo;
    if (size_pseudo == 0)
    {
        size_pseudo = strlen("Server: ");
        buffer_pseudo = (char*)malloc(size_pseudo);
        bzero(buffer_pseudo,size_pseudo);
        strncpy(buffer_pseudo,"Server: ",size_pseudo);
    }
    else
    {
        buffer_pseudo = (char*)malloc(size_pseudo);
        bzero(buffer_pseudo,size_pseudo);
        strncpy(buffer_pseudo,sending_message->header_pseudo_sender,size_pseudo);
    }
    char * buffer = (char*)malloc(size_pseudo + size_time + size_msg);
    bzero(buffer,size_pseudo + size_time + size_msg);
    if (size_time != 0){
        strncpy(buffer,sending_message->time,size_time);
        strncat(buffer,buffer_pseudo,size_pseudo);
    }
    else
    {
        strncpy(buffer,buffer_pseudo,size_pseudo);
    }
    strncat(buffer,sending_message->message,size_msg);
    return buffer;
}

int send_message(char *message,int *size,int client){
    int size_to_send = *size;
    int size_sent=0;
    int c;
    while (size_sent - *size < 0){
        c = send(client, message + size_sent, size_to_send,0);
        if(c == -1){
            perror("my_send");
            break;
        }
        size_sent += c;
        size_to_send -= c;
    }
    *size = size_sent;
    if (c == -1) {return -1;}
    else {return 0;}
}

int send_all(char *message,LinkedClient *client_list,int master_socket,Client * sender){
    int size_message = strlen(message);
    LinkedClient *elt = client_list;
    int col = strlen(sender->color);
    while (elt!= NULL){
        if (elt->client->socket != master_socket && elt->client->socket != sender->socket){
            if (send_message(sender->color, &col, elt->client->socket) == -1){
                perror("send_message");
                return -1;
            }
            if (send_message(message, &size_message , elt->client->socket) == -1){
                perror("send_message");
                return -1;
            }
        }
        elt = elt->next;
    }
    return 0;
}

void send_file(int sock, char* file_name) {
    FILE* fd = fopen(file_name, "r");
    if(fd == NULL) {
        perror("fopen");
        return;
    }
    char* buffer = malloc(1024);
    int n;
    while((n = fread(buffer, 1, sizeof(buffer), fd)) > 0 ) {
        send(sock, buffer, n, 0);
    }
    fclose(fd);
}

void receive_file(int sock, char* file_name,int i) {
    FILE* fd = fopen(file_name, "w");
    if(fd == NULL) {
        perror("fopen");
        return;
    }
    int count=0;
    char* buffer = malloc(1024);
    int n;
    while((n = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, n, fd);
        count += n;
        if (count >= i)
        {
            break;
        }
    }
    fclose(fd);
}

Receiving_Message *create_receive_message(Client *source, char* message){
    Receiving_Message *msg = (Receiving_Message*)malloc(sizeof(Receiving_Message));
    char * msg1 = (char*)malloc(strlen(message)+1);
    bzero(msg1,strlen(message)+1);
    strncpy(msg1,message,strlen(message));
    msg->source = source;
    msg->message = msg1;
    return msg;
}

int isCommand(Receiving_Message *receiving_message){
    return is_command(receiving_message->message);
}

int treat_receive_message(Receiving_Message *receive_message, int master_socket,LinkedClient *client_list,mdp_list **mdp_list){
    if (isCommand(receive_message))
    {
        treat_command(receive_message,client_list,mdp_list);
    }
    else
    {
        Sending_Message *message = create_sending_message(receive_message->source,receive_message->message);
        format_header_pseudo(message);
        set_time(message);
        send_all(format_whole_message(message),client_list,master_socket,receive_message->source);
    }
    return 0;
}

void treat_command(Receiving_Message *receive_message,LinkedClient * client_list,mdp_list ** mdp_list){
    int size_message = strlen(receive_message->message);
    char * message_copy = malloc(size_message+1);
    strcpy(message_copy,receive_message->message);
    char ** tab = str_split(message_copy," ",0);
    if (strncmp(uppercase(tab[0]),NICKNAME,size_message) == 0)
    {
        printf("NICK\n");
        char* pseudo_temp = tab[1];
        if (has_delimiter(pseudo_temp) == 0){
            printf("mdp\n");
            char** pseudos = str_split(pseudo_temp,"\n",0);
            char* pseudo = pseudos[0];
            char* mdp_temp = tab[2];
            char** mdps = str_split(mdp_temp,"\n",0);
            char* mdp = mdps[0];
            nick_command(pseudo,mdp,receive_message->source,client_list,mdp_list);
        }
        else{
            printf("nomdp\n");
            char** pseudos = str_split(pseudo_temp,"\n",0);
            char* pseudo = pseudos[0];
            nick_command(pseudo,"nomdp",receive_message->source,client_list,mdp_list);
        }
    }
    else if (strncmp(uppercase(tab[0]),REGISTER,size_message) == 0)
    {
        printf("REGISTER\n");
        if (has_delimiter(tab[1]) == 0){
            char* mdp_temp = tab[2];
            char** mdps = str_split(mdp_temp,"\n",0);
            char* mdp = mdps[0];
            register_command(tab[1],mdp,receive_message->source,mdp_list);  
        }
        else{
            return;
        }
                   
    }
    else if (strncmp(uppercase(tab[0]),UNREGISTER,size_message) == 0)
    {
        printf("UNREGISTER\n");
        if (has_delimiter(tab[1]) == 0){
            char* mdp_temp = tab[2];
            char** mdps = str_split(mdp_temp,"\n",0);
            char* mdp = mdps[0];
            unregister_command(tab[1],mdp,receive_message->source,mdp_list); 
        }
        else{
            return;
        }
    }
    else if (strncmp(uppercase(tab[0]),EXIT,size_message) == 0)
    {
        printf("EXIT\n");
        exit_command(receive_message->source,client_list);
        return;
    }
    else if (strncmp(uppercase(tab[0]),DATE,size_message) == 0)
    {
        printf("DATE\n");
        date_command(receive_message->source);
    }
    else if (strncmp(uppercase(tab[0]),MP,size_message) == 0)
    {
        printf("MP\n");
        char* pseudo = tab[1];
        mp_command(receive_message->source,client_list,pseudo,receive_message->message,strlen(tab[0]));
        return ;
    }
    else if (strncmp(uppercase(tab[0]),ALERTE,size_message) == 0)
    {
        printf("ALERTE\n");
        if (has_delimiter(tab[1]) != 0){
            printf("global\n");
            global_alerte_command(receive_message->source,client_list,receive_message->message,strlen(tab[0]));
        }
        else
        {
            printf("not global\n");
            char* pseudo = tab[1];
            alerte_command(receive_message->source,client_list,pseudo,receive_message->message,strlen(tab[0]));
        }
    }
    else if (strncmp(uppercase(tab[0]),SEND,size_message) == 0)
    {
        printf("SEND\n");
        if (has_delimiter(tab[0]) == 0)
        {
            if (has_delimiter(tab[1]) == 0)
            {
                char* pseudo = tab[1];
                char *fichier_temp = tab[2];
                char** fichiers = str_split(fichier_temp,"\n",0);
                char* fichier = fichiers[0];
                int i = atoi(tab[3]);
                send_command(receive_message->source,client_list,pseudo,fichier,i);
            }
        }
        

    }
    else if (strncmp(uppercase(tab[0]),RED,size_message) == 0)
    {
        printf("RED\n");
        receive_message->source->color = CRED;
    }
    else if (strncmp(uppercase(tab[0]),GREEN,size_message) == 0)
    {
        printf("GREEN\n");
        receive_message->source->color = CGREEN;
    }
    else if (strncmp(uppercase(tab[0]),YELLOW,size_message) == 0)
    {
        printf("YELLOW\n");
        receive_message->source->color = CYELLOW;
    }
    else if (strncmp(uppercase(tab[0]),BLUE,size_message) == 0)
    {
        printf("BLUE\n");
        receive_message->source->color = CBLUE;
    }
    else if (strncmp(uppercase(tab[0]),PURPLE,size_message) == 0)
    {
        printf("PURPLE\n");
        receive_message->source->color = CPURPLE;
    }
    else if (strncmp(uppercase(tab[0]),BLACK,size_message) == 0)
    {
        printf("BLACK\n");
        receive_message->source->color = CBLACK;
    }
    else if (strncmp(uppercase(tab[0]),WHITE,size_message) == 0)
    {
        printf("WHITE\n");
        receive_message->source->color = CWHITE;
    }
    else if (strncmp(uppercase(tab[0]),JOIN,size_message) == 0)
    {
        printf("JOIN\n");
    }
    else if (strncmp(uppercase(tab[0]),KICK,size_message) == 0)
    {
        printf("KICK\n");
    }
    else if (strncmp(uppercase(tab[0]),OP,size_message) == 0)
    {
        printf("OP\n");
    }
    else if (strncmp(uppercase(tab[0]),LOGIN,size_message) == 0)
    {
        char* pseudo_temp = tab[1];
        char** pseudos = str_split(pseudo_temp,"\n",0);
        char* pseudo = pseudos[0];
        login_command(pseudo,receive_message->source,mdp_list,client_list);
    }
    else{        
    }
}

int nick_command(char* pseudo,char * password,Client *client,LinkedClient *client_list,mdp_list **mdps_list){
    Sending_Message *sending_message;
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    mdp_list *elt;
    Client * pseudo_holder;
    if ( (pseudo_holder = get_client_through_pseudo(pseudo,client_list)) != NULL)
    {   
        if (pseudo_holder->registered == 1){
            message_send = fuse_strings(pseudo,":  est déjà pris\n");
            sending_message = create_sending_message(client,message_send);
            char *buffer = format_whole_message(sending_message);
            int len = strlen(buffer);
            send_message(buffer,&len,client->socket);
            return -1;
        }
        else{
            if (strncmp(password,"nomdp",max(strlen(password),strlen("nomdp"))) == 0){
                message_send = fuse_strings(pseudo,":  est déjà pris\n");
                sending_message = create_sending_message(client,message_send);
                char *buffer = format_whole_message(sending_message);
                int len = strlen(buffer);
                send_message(buffer,&len,client->socket);
                return -1;
            }
            {
                message_send = fuse_strings(pseudo,": vient d'etre utilise pour une connexion enregistrée\n");
                sending_message = create_sending_message(pseudo_holder,message_send);
                char *buffer = format_whole_message(sending_message);
                int len = strlen(buffer);
                send_message(buffer,&len,pseudo_holder->socket);
                exit_command(pseudo_holder,client_list);
                client->pseudo = pseudo;
                client->registered = 1;
                return 0;
            }
        }
        
    }
    else
    {
        if ((elt = find_mdp(*mdps_list,pseudo)) == NULL){
            client->pseudo = pseudo;
            message_send = fuse_strings(pseudo,":  est dorénavent votre pseudo\n");
            sending_message = create_sending_message(pseudo_holder,message_send);
            char *buffer = format_whole_message(sending_message);
            int len = strlen(buffer);
            send_message(buffer,&len,client->socket);
            return 0;
        }
        else
        {
            if (strncmp(password,elt->login->password,max(strlen(password),strlen(elt->login->password)))==0){
                client->pseudo = pseudo;
                client->registered = 1;
                message_send = fuse_strings(pseudo,":  est dorénavent votre pseudo\n");
                sending_message = create_sending_message(pseudo_holder,message_send);
                char *buffer = format_whole_message(sending_message);
                int len = strlen(buffer);
                send_message(buffer,&len,client->socket);
                return 0;
            }
            else {
                message_send = "Wrong Password\n";
                sending_message = create_sending_message(pseudo_holder,message_send);
                char *buffer = format_whole_message(sending_message);
                int len = strlen(buffer);
                send_message(buffer,&len,client->socket);
                return -1;
            }
        }
    }
    return -1;
}

void exit_command(Client *client,LinkedClient * client_list){
    int sd = client->socket;
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    const char * buf = "/QUIT";
    strncpy(message_send,buf,strlen(buf));
    int len = strlen(message_send);
    send_message(message_send,&len,client->socket);
    client->socket = -1;
    client->pseudo = "";
    close(sd);
    return;
}

void send_command(Client *client,LinkedClient * client_list,char * pseudo,char *fichier,int i){
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    printf("%d\n",i);
    receive_file(client->socket,"buffer_send.txt",i);
    printf("receive fini\n");
    Client * dest = get_client_through_pseudo(pseudo,client_list);
    if (dest != NULL) {
    const char * buf = "/FILE ";
    strncpy(message_send,buf,strlen(buf));
    strncat(message_send,fichier,strlen(fichier));
    int copy_len = strlen("copy");
    strncat(message_send,"copy",copy_len);
    char* it;
    it = itoa(i);
    int mini_i = strlen(" ");
    strncat(message_send," ",mini_i);
    strncat(message_send,it,strlen(it));
    strncat(message_send," ",mini_i);
    strncat(message_send,"\n",mini_i);
    int len = strlen(message_send);
    send_message(message_send,&len,dest->socket);
    sleep(0.5);
    send_file(dest->socket,"buffer_send.txt");
    }
}

void mp_command(Client *client,LinkedClient * client_list,char* pseudo,char * message,int k){
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    Client *dest = get_client_through_pseudo(pseudo,client_list);
    message_send = fuse_strings("private message from: ",client->pseudo);
    message_send = fuse_strings(message_send, ": ");
    int size = k + strlen(pseudo) + 2;
    message_send = fuse_strings(message_send, message + size);
    int len = strlen(message_send);
    send_message(message_send,&len,dest->socket);
}

void login_command(char * pseudo,Client *client,mdp_list ** mdp_list,LinkedClient *client_list){
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    bzero(message_send,BUFFER_SIZE+1);
    Sending_Message *sending_message;
    Client * pseudo_holder;
    print_client(client_list);
    if ((pseudo_holder = get_client_through_pseudo(pseudo,client_list)) != NULL)
    {
        const char *buf = "pseudo déjà connecté";
        strncpy(message_send,buf,strlen(buf));
        sending_message = create_sending_message(client,message_send);
        char *buffer = format_whole_message(sending_message);
        int len = strlen(buffer);
        send_message(buffer,&len,client->socket);

    }
    else
    {   
        printf("pseudo non utilise\n");
        const char * buf = "loginaccepted";
        strncpy(message_send,buf,strlen(buf));
        int len = strlen(message_send);
        client->pseudo = pseudo;
        send_message(message_send,&len,client->socket);
    }    
}

void register_command(char * pseudo,char * password,Client *client,mdp_list ** mdp_list){

    logins *login;
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    bzero(message_send,BUFFER_SIZE+1);
    Sending_Message *sending_message;
    if (find_mdp(*mdp_list,pseudo) == NULL)
    {
        const char * buf = "Logins have been registered, use /nick pseudo password to switch to it\n";
        login = create_login(pseudo,password);
        print_mdps(*mdp_list);
        *(mdp_list) = add_mdp(*mdp_list,login);
        print_mdps(*mdp_list);
        modify_file(*mdp_list);
        strncpy(message_send,buf,strlen(buf));
        sending_message = create_sending_message(client,message_send);
        char *buffer = format_whole_message(sending_message);
        int len = strlen(buffer);
        send_message(buffer,&len,client->socket);
    }
    else
    {
        const char * buf = "Logins already registered, unregister it if you want to switch password\n";
        strncpy(message_send,buf,strlen(buf));
        sending_message = create_sending_message(client,message_send);
        char *buffer = format_whole_message(sending_message);
        int len = strlen(buffer);
        send_message(buffer,&len,client->socket);
    }
}

void unregister_command(char*pseudo,char* password,Client *client,mdp_list **mdps_list){
    logins *login;
    mdp_list *elt;
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    bzero(message_send,BUFFER_SIZE+1);
    Sending_Message *sending_message;
    printf("ENCORE TOI\n");
    if (find_mdp(*mdps_list,pseudo) == NULL){
        printf("Not found\n");
        const char * buf = "No such logins registered\n";
        strncpy(message_send,buf,strlen(buf));
        sending_message = create_sending_message(client,message_send);
        char *buffer = format_whole_message(sending_message);
        int len = strlen(buffer);
        send_message(buffer,&len,client->socket);
    }
    else 
    {
        elt = find_mdp(*mdps_list,pseudo);
        login = elt->login;
        const char * buf;
        if (strncmp(login->password,password,strlen(password)) == 0){
            buf = "Logins have been unregistered\n";
            login->pseudo="";
            login->password="";
            modify_file(*mdps_list);
            printf("modify?\n");
        }
        else
        {
            buf = "Wrong password\n";
        }
        strncpy(message_send,buf,strlen(buf));
        sending_message = create_sending_message(client,message_send);
        char *buffer = format_whole_message(sending_message);
        int len = strlen(buffer);
        send_message(buffer,&len,client->socket);
    }

}

void date_command(Client *client){
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    bzero(message_send,BUFFER_SIZE+1);
    time_t now = time(NULL);
    struct tm* pTime = localtime(&now);
    static const char dayNames[7][3] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };

    static const char monthNames[12][3] = {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };

    static char result[26];     // L'unique zone de mémoire dans laquelle travailler.

    sprintf( result, "%.3s %.3s%3d %.2d:%.2d:%.2d %d\n",
        dayNames[pTime->tm_wday], monthNames[pTime->tm_mon], pTime->tm_mday, 
        pTime->tm_hour, pTime->tm_min, pTime->tm_sec,
        1900 + pTime->tm_year );
    strncpy(message_send,result,strlen(result));
    Sending_Message * sending_message;
    sending_message = create_sending_message(client,message_send);
    char *buffer = format_whole_message(sending_message);
    int len = strlen(buffer);
    send_message(buffer,&len,client->socket);
}

void alerte_command(Client *client,LinkedClient * client_list,char* pseudo,char * message,int k){
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    Client *dest = get_client_through_pseudo(pseudo,client_list);
    if (dest != NULL){
    message_send = fuse_strings("ALERTE FROM: ",client->pseudo);
    message_send = fuse_strings(message_send, ": ");
    int size = k + strlen(pseudo) + 2;
    message_send = fuse_strings(message_send, message + size);
    int len = strlen(message_send);
    int lena = strlen("\a");
    int red = strlen("\033[1;31m");
    send_message("\033[1;31m",&red,dest->socket);
    send_message("\a",&lena,dest->socket);
    send_message(message_send,&len,dest->socket);
    }
}

void global_alerte_command(Client *client,LinkedClient * client_list,char * message,int k){
    LinkedClient *dest = client_list;
    char *message_send;
    message_send = malloc(BUFFER_SIZE +1);
    message_send = fuse_strings("ALERTE FROM: ",client->pseudo);
    message_send = fuse_strings(message_send, ": ");
    int size = k + 1;
    message_send = fuse_strings(message_send, message + size);
    int len = strlen(message_send);
    int lena = strlen("\a");
    int red = strlen("\033[1;31m");
    while (dest != NULL)
    {
        if (client->socket != dest->client->socket){
            send_message("\033[1;31m",&red,dest->client->socket);
            send_message("\a",&lena,dest->client->socket);
            send_message(message_send,&len,dest->client->socket);
        }
        dest = dest->next;
    }
}