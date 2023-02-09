#include "mini_lib.h"
#include <unistd.h>


#define READSIZE 2048
/*
    Programme qui lis le contenu d'un fichier dans la sortie standard
*/
int main(int argc, char *argv[])
{   
    if (argc > 2)
    {
        mini_printf("rentrer le bon nom d'argument\n");
        mini_exit();
    }
    int k = 0;
    char *src = argv[1];
    MYFILE *srcfile = mini_fopen(src,'r');
    char *buffer = mini_calloc(sizeof(char),READSIZE);
    if (buffer == NULL)
    {
        mini_perror("Error calloc:");
        mini_exit();
    }
    k = mini_fread(buffer,sizeof(char),READSIZE,srcfile);
    if (k==-1)
    {
        mini_perror("Error read:");
        mini_exit();
    }
    mini_printf(buffer);
    while (k == READSIZE)
    {   
        k = mini_fread(buffer,sizeof(char),READSIZE,srcfile);
        if (k==-1)
        {
            mini_perror("Error read:");
            mini_exit();
        }
        mini_printf(buffer);
    }
    mini_exit();
    return 0;
}