#include "mini_lib.h"
#include <unistd.h>
#include "sys/syscall.h"
#include "sys/types.h"
#include "sys/errno.h"
#include <sys/stat.h>
#include <fcntl.h>

/*
  Fonction auxiliaire qui retourne la chaine de caractère dans l'entre sens car la fonciton principale rempli à l'envers
*/
static void decimal_itoa_aux(char result[]){
  char buffer;
  int i,j;
  for (i = 0,j = mini_strlen(result)-1; i < j; j--)
  {
    buffer = result[i]; //Commandes d'echanges
    result[i] = result[j];
    result[j] = buffer;
  }
}

/*
  Fonction principale qui convertit un entier en chaine de caractère
*/
void decimal_itoa(int integer,char result[]){
  int c = 0;
  int even;
  if ((even = integer) <0)
  {
    integer = -integer;
  }
  result[0] = integer % 10 + '0';
  c++;
  while((integer /= 10) > 0)
  {
    result[c++] = integer % 10 + '0' ;
  }
  if (even < 0)
  {
    result[c++] = '-';
  }
  result[c] = '\0';
  decimal_itoa_aux(result);
}


int main(int argc, char *argv[]){
    if (argc > 2)
    {
        mini_printf("Wrong argument count");
        mini_exit();
    }
    char *src = argv[1];
    MYFILE *srcfile = mini_fopen(src,'r');
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
        if (ch[0] == '\n' || ch[0] == ' ')
        {
            counter++;
        }
    }
    char result[32];
    decimal_itoa(counter,(char *)result);
    mini_printf(result);
    mini_exit();
    return 0 ;
}