#include "mini_lib.h"
#include <unistd.h>

#define READSIZE 2048
/*
    fonction qui vide un fichier
*/
int main(int argc, char *argv[]){
    if (argc != 2)
    {
        mini_printf("Wrong argument number\n");
        mini_exit();
    }
    if(mini_fopen(argv[1],'t') == NULL) // ouverture en mode tronquée
    {
        mini_perror("Error open:");
    }
    mini_exit();
    return 0;
}