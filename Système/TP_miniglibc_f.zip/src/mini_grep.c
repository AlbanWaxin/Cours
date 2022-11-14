#include "mini_lib.h"
#include <unistd.h>


#define BUFFERSIZE 2048


/*
    Fonction qui renvoie le nombre maximale de charactere dans une ligne d'un fichier
*/
static int get_max_char_line(char *filename){
    MYFILE *srcfile = mini_fopen(filename,'r');
    char ch[2];
    int counter = 0;
    int char_line = 0;
    int max_char_line =0;
    int read;
    while ( (read = mini_fread(ch,sizeof(char),1,srcfile)) != 0)
    {
        if (read == -1)
        {
            mini_perror("Error read:");
            return -1;
        }
        char_line++;
        if (ch[0] == '\n')
        {
            if (char_line > max_char_line)
            {
                max_char_line = char_line;
            }
            counter++;
            char_line=0;
        }
        
    }
    return  max_char_line;
}

/*
    Fonction nettoyage du buffer
*/
static void remplir_buffer_0(char* buffer, int size){
    for (size_t i = 0; i < size; i++)
    {
        buffer[i] = '\0';
    }
    
}

/*
    Fonction qui cherche dans une chaine si l'autre chaine apparait
*/
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

int main(int argc, char *argv[])
{
    if (argc > 3 || argc < 3)
    {
        mini_printf("Wrong number of arguments");
        mini_exit();
    }
    char *src = argv[2];
    MYFILE *srcfile = mini_fopen(src,'r');
    int max_line_length = get_max_char_line(argv[2]); //recupere la taille maximale
    char current_line[max_line_length]; //buffer des lignes
    remplir_buffer_0(current_line,max_line_length); //initialisation du buffer
    char ch[2];
    int read;
    int ind=0;
    while ((read = mini_fread(ch,sizeof(char),1,srcfile)) != 0)
    {
        if (read == -1)
        {
            mini_perror("Error read:");
            return -1;
        }
        if (ch[0] == '\n') //verifie si present a chaque fin de ligne
        {
            if (search_string(current_line,argv[1]) == 1) //si trouve alors print
            {
                mini_printf(current_line);
                mini_printf("\n");
            }
            ind = 0;
            remplir_buffer_0(current_line,max_line_length);
        }
        else
        {   
            current_line[ind] = ch[0];
            ind++;
        }   
    }
    mini_exit();
}