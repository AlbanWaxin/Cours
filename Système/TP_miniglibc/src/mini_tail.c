#include "mini_lib.h"
#include <unistd.h>



#define BUFFERSIZE 2048
/*
    Fonction qui converti un char en int
*/
static int mini_atoi(char *integerchar){
    int integer = 0;
    int i;
    for (i = 0; integerchar[i] != '\0'; ++i)
    {
        integer *= 10 ;
        integer += integerchar[i] - '0';
    }
    return integer;
}

/*
    fonction qui compte le nombre de ligne du fichier
*/
static int nb_ligne(char *filename){
    MYFILE *srcfile = mini_fopen(filename,'r');
    char ch[2];
    int counter = 0;
    int read;
    while ( (read = mini_fread(ch,sizeof(char),1,srcfile)) != 0)
    {
        if (read == -1)
        {
            mini_perror("Error read:");
            return -1;
        }
        if (ch[0] == '\n')
        {
            counter++;
        }
    }
    return  counter;
}

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        mini_printf("il faut des arguments");
        mini_exit();
    }
    char *src = argv[3];
    MYFILE *srcfile = mini_fopen(src,'r');
    int n = mini_atoi(argv[2]); 
    int ligne_total = nb_ligne(argv[3]);
    char ch[2];
    int counter = 0;
    int read;
    while ( (read = mini_fread(ch,sizeof(char),1,srcfile)) != 0  && counter !=ligne_total-n-1)//lit les n-N premiere ligne sans print
    {
        if (read == -1)
        {
            mini_perror("Error read:");
            return -1;
        }
        if (ch[0] == '\n')
        {
            counter++;
        }
    }
    while ( (read = mini_fread(ch,sizeof(char),1,srcfile)) != 0  && counter !=ligne_total)//lit les dernieres lignes et les prints
    {
        if (read == -1)
        {
            mini_perror("Error read:");
            return -1;
        }
        if (ch[0] == '\n')
        {
            counter++;
        }
        mini_printf(ch);
    }
    mini_exit();
}
