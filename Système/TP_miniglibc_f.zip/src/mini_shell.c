#include "mini_lib.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define COMMANDSIZE 2048

char *command;

static int first_word(char* buffer){
    int ind = 0;
    while ( buffer[ind] != ' ' && buffer[ind] != '\0')
    {
        command[ind] = buffer[ind];
        ind++;   
    }
    return ind;   
}

int search_string(char* char1,char* char2){
    int ind1 =0;
    int ind2 =0;
    int index_start_word;
    while (char1[ind1] != '\0') 
    {
        while (char1[ind1] != char2[0]) //on verifie si on peut etre au debut d'un mot ou si en bouclant on arrive pas au bout
        {
            if (char1[ind1] == '\0')
            {
                return (-1);
            }
            ind1++;
        }
        index_start_word = ind1;
        while (char1[ind1] == char2[ind2] && char2[ind2] != '\0') //presence de la continuite du mot
        {
            if (char1[ind1] == '\0') //fin de fichier sans trouver
            {
                return (-1);
            }
            ind1++;
            ind2++;
        }
        if (char2[ind2] == '\0') //mot trouve
        {
            return 1;
        }
        ind1 = index_start_word + 1;
        ind2 = 0;
    }
    return -1;
}

/*
static void command_exec(char* command,char* arg){
    pid_t id_fils;
    int hold = 0;

    id_fils = fork();
    if (id_fils ==-1)
    {
        mini_perror("Error fork:");
        return -1;
    }
    else if(id_fils==0){
        if(execl(command,arg,NULL)==-1){
            mini_perror("Commande non executee");
        }
        return -1;
    }
    else{
        //on est dans le processus parent
        //on attend
        wait(&hold);
        return;
    } 
}
*/


int main(int argc, char *argv[])
{
    char *buffer = mini_calloc(sizeof(char),COMMANDSIZE);
    command = mini_calloc(sizeof(char),32);
    if (!buffer)
    {
        mini_perror("Error calloc");
        mini_exit();
    }
    int fin = 0;
    while (fin != 1)
    {
        write(1, ">> ",3);
        if (mini_scanf(buffer,COMMANDSIZE-1)<0)
        {
            fin =1;
        }

        /*int ind = */first_word(buffer);
        if (search_string(command,"mini_head")==1)
        {
            mini_printf("mini_head\n");
        }   
        else if (search_string(command,"mini_tail")==1)
        {
            mini_printf("mini_tail\n");
        }
        else if (search_string(command,"mini_grep")==1)
        {
            mini_printf("mini_grep\n");
        }
        else if (search_string(command,"mini_clean")==1)
        {
            mini_printf("mini_clean\n");
        }
        else if (search_string(command,"mini_cat")==1)
        {
            mini_printf("mini_cat\n");
            //command_exec("./mini_cat",buffer+ind+1);
        }
        else if (search_string(command,"mini_echo")==1)
        {
            mini_printf("mini_echo\n");
        }
        else if (search_string(command,"wc")==1)
        {
            mini_printf("wc\n");
        }
        else if (search_string(command,"exit")==1)
        {
            break;
        }
        else
        {
            mini_printf("Not a command\n");
        }
    }
    mini_exit();
    return 0;
}
