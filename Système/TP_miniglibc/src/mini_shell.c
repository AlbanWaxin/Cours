#include "mini_lib.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define COMMANDSIZE 2048
#define MAX_WORD_COUNT 1024
#define MAX_WORD_LENGTH 512

void from_sentence_to_word(char* sentence, char** words_tab, int* nb_word) {
    int i, j, k;
    i = j = k = 0;
    while (sentence[i] != '\0') {
        if (sentence[i] == ' ' || sentence[i] == '\n') {
            words_tab[j][k] = '\0';
            j++;
            k = 0;
        } else {
            words_tab[j][k] = sentence[i];
            k++;
        }
        i++;
    }
    words_tab[j][k] = '\0';
    *nb_word = j+1;
}

int countWords(const char* sentence) {
    int count = 0;
    int inWord = 0;
    for (int i = 0; sentence[i]; i++) {
        if (sentence[i] == ' ' || sentence[i] == '\n') {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            count++;
        }
    }
    return count;
}

static void remplir_buffer_0(char* buffer, int size){
    for (size_t i = 0; i < size; i++)
    {
        buffer[i] = '\0';
    }
}

void transform_to_command(char* command_to_transform) {
    int len = 0;
    while (command_to_transform[len] != '\0') {
        len++;
    }
    char* transformed = (char*) mini_calloc(sizeof(char),len + 3);
    transformed[0] = '.';
    transformed[1] = '/';
    for (int i = 0; i < len; i++) {
        transformed[i + 2] = command_to_transform[i];
    }
    transformed[len + 2] = '\0';
    remplir_buffer_0(command_to_transform, MAX_WORD_LENGTH);
    for (int j= 0; j < len+2; j++) {
        command_to_transform[j] = transformed[j];
    }    
    mini_free(transformed);
    return;
}



void clear_tab(char** word_tab){
    int i;
    char * word;
    for (i = 0; i < MAX_WORD_COUNT; i++) {
        word = word_tab[i];
        if (word!= NULL) {
            remplir_buffer_0(word,MAX_WORD_LENGTH);
        }
    }
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

static void remove_return_line(char* arg){
    int ind = 0;
    while ( arg[ind] != '\n' && arg[ind] != '\0')
    {
        ind++;   
    }
    if (arg[ind] == '\n'){
        arg[ind] = '\0';
    }
    else
    {
        return;
    }
    return;
}

static void command_exec(char* command,char** args){
    pid_t id_fils;
    int hold = 0;
    //mini_printf(arg);
    id_fils = fork();
    if (id_fils ==-1)
    {
        mini_perror("Error fork:");
        return;
    }
    else if(id_fils==0){
        if(execv(command,args)==-1){
            mini_perror("Error exec");
        }
        return;
    }
    else{
        wait(&hold);
        return;
    } 
}



int main(int argc, char *argv[])
{
    char* command = mini_calloc(sizeof(char),MAX_WORD_LENGTH);
    char *buffer = mini_calloc(sizeof(char),COMMANDSIZE);
    char word_tab[MAX_WORD_LENGTH+1][MAX_WORD_COUNT];
    int count;
    
    if (!buffer)
    {
        mini_perror("Error calloc");
        mini_exit();
    }
    int fin = 0;
    while (fin != 1)
    {
        write(1, ">> ",3);
        remplir_buffer_0(buffer,COMMANDSIZE);
        if (mini_scanf(buffer,COMMANDSIZE-1)<0)
        {
            fin =1;
        }
        clear_tab(word_tab);
        from_sentence_to_word(buffer,word_tab,&count);
        command = word_tab[0];
        if (search_string(command,"mini_head")==1)
        {
            mini_printf("mini_head\n");
        }   
        else if (search_string(command,"mini_tail")==1)
        {
            int ind2 = 0;
            mini_printf("mini_tail\n");
            remplir_buffer_0(command,32);
            ind += first_word(buffer+ind+1);
            remplir_buffer_0(command,32);
            ind += first_word(buffer+ind+2);
            ind2 = ind;
            remplir_buffer_0(command,32);
            ind += first_word(buffer+ind+3);

            command_exec("mini_tail","./mini_tail -n",(buffer+ind2+2),command);
        }
        else if (search_string(command,"mini_grep")==1)
        {
            //mini_printf("mini_grep\n");
            remove_return_line(buffer+ind+1);
            remplir_buffer_0(command,32);
            ind += first_word(buffer+ind+1);
            command_exec("mini_grep","./mini_grep",command,(buffer+ind+2));
        }
        else if (search_string(command,"mini_clean")==1)
        {
            //mini_printf("mini_clean\n");
            remove_return_line(buffer+ind+1);
            command_exec("mini_clean","./mini_clean",(buffer+ind+1),NULL);
        }
        else if (search_string(command,"mini_touch")==1)
        {
            //mini_printf("mini_touch\n");
            remove_return_line(buffer+ind+1);
            command_exec("mini_touch","./mini_touch",(buffer+ind+1),NULL);
        }
        else if (search_string(command,"mini_cat")==1)
        {
            //mini_printf("mini_cat\n");
            //execl("mini_cat","./mini_cat","../README.txt",NULL);
            remove_return_line(buffer+ind+1);
            command_exec("mini_cat","./mini_cat",(buffer+ind+1),NULL);
        }
        else if (search_string(command,"mini_echo")==1)
        {
            //mini_printf("mini_echo\n");
            remove_return_line(buffer+ind+1);
            command_exec("mini_echo","./mini_echo",(buffer+ind+1),NULL);
        }
        else if (search_string(command,"wc")==1)
        {
            //mini_printf("wc\n");
            remove_return_line(buffer+ind+1);
            command_exec("wc","./wc",(buffer+ind+1),NULL);
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
