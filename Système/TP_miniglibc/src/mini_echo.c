#include "mini_lib.h"
#include <unistd.h>
#include "sys/syscall.h"
#include "sys/types.h"
#include "sys/errno.h"
#include <sys/stat.h>
#include <fcntl.h>

/*
    Fonction qui repete les parametre d'entree
*/
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        mini_printf("il faut des arguments");
        mini_exit();
    }
    for (int i = 1; i < argc; i++) 
    {
      mini_printf(argv[i]);
      mini_printf(" ");
    }
    mini_exit();
}