#include "mini_lib.h"
#include <unistd.h>


#define READSIZE 2048
/*
    Fonction qui copie un fichier dans un autre
*/
int main(int argc, char *argv[])
{   
    if (argc > 3)
    {
        mini_printf("rentrer le bon nom d'argument\n");
        mini_exit();
    }
    int k = 0; 
    char *src = argv[1]; 
    char *dest = argv[2];
    MYFILE *srcfile = mini_fopen(src,'r'); // ouverture en lecture
    MYFILE *destfile = mini_fopen(dest,'a'); //ouverture en ecriture ouverture
    if (!srcfile || !destfile) //levee d'erreur
    {
        mini_perror("Error open:");
        return -1;
    }
    char *buffer = mini_calloc(sizeof(char),READSIZE);//Allocation memoire 
    if (buffer == NULL) //levee d'erreur
    {
        mini_perror("Error calloc:");
        mini_exit();
    }
    k = mini_fread(buffer,sizeof(char),READSIZE,srcfile); //lire READSIZE donnees
    if (k==-1)//levee d'erreur
    {
        mini_perror("Error read:");
        mini_exit();
    }
    if (mini_fwrite(buffer,sizeof(char),READSIZE,destfile) == -1)//ecriture
    {
        mini_perror("Error write"); //levee d'erreur
        mini_exit();
    }
    while (k == READSIZE)//bouclage jusqu'a la fin du fichier
    {   
        k = mini_fread(buffer,sizeof(char),READSIZE,srcfile);
        if (k==-1)
        {
            mini_perror("Error read:");
            mini_exit();
        }
        if (mini_fwrite(buffer,sizeof(char),READSIZE,destfile) == -1)
        {
            mini_perror("Error write");
            mini_exit();
        }
    }
    mini_exit();
    return 0;
}