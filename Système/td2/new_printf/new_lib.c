#include "new_lib.h"
#include <unistd.h>
#include "sys/errno.h"
#include "sys/syscall.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int ind = -1;
char * buffer;

void *new_malloc(int size)
{
  void *pointer = sbrk(size);
  if (pointer == (void *)-1)
   {
      perror("Erreur%s survenue\n");
      return NULL;
   }
  return pointer;
}

void new_printf(char * msg)
{
  if (ind== -1)
  {
    buffer = new_malloc(BUF_SIZE,1);
    if(buffer  == NULL)
    {
      printf("Error");
      exit(EXIT_FAILURE);
    }
  }
  ind = 0;
  for(int i=0; i <= strlen(msg); i++)
  {
    if(msg[i] == '\n' || ind == BUF_SIZE || msg[i] == '\0')
    {
      if(write(STDOUT_FILENO,buffer,ind) == -1)
      {
        perror("Error printf:");
      }
      else if(msg[i] == '\n' || msg[i] == '\0')
      {
        write(STDOUT_FILENO,"\n",1);
        ind = 0;
      }
      else
      {
        ind = 0;
        buffer[ind] = msg[i];
        ind++;
      }

    }
    else
    {
      buffer[ind] = msg[i];
      ind++;
    }
  }
}

void new_exit()
{
  ind =0;
  _exit(0);
}