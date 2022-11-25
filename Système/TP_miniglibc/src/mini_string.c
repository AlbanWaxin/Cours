#include "mini_lib.h"
#include <unistd.h>
#include "sys/errno.h"
#include "sys/syscall.h"

#define BUF_SIZE 1024 
char *buffer;
static int ind =-1;

/*
  Fonction qui affiche dans la sortie standard de la console le message passé en parametre par écriture bufferisée
*/
void mini_printf(char * msg)
{
  if (ind== -1) //Premier appel
  {
    buffer = mini_calloc(1,BUF_SIZE); //Allocation de l'espace du buffer
    if(buffer  == NULL) // Levée d'erreur
    {
      mini_perror("Error calloc:");
      mini_exit();
    }
  }
  ind = 0;
  for(int i=0; i <= mini_strlen(msg); i++)
  {
    if(msg[i] == '\n' || ind == BUF_SIZE || msg[i] == '\0') //écriture nouvelle ligne, fin de ligne|taille buffer atteinte|fin du mesage
    {
      if(write(STDOUT_FILENO,buffer,ind) == -1) //Levée d'erreur
      {
        mini_perror("Error printf:");
        mini_exit();
      }
      else if(msg[i] == '\n') //Fin de ligne ou de message
      {
        write(STDOUT_FILENO,"\n",1);
        ind = 0;
      }
      else //Vidage du buffer
      {
        ind = 0;
        buffer[ind] = msg[i];
        ind++;
      }
    }
    else //Ecriture du buffer par parcours
    {
      buffer[ind] = msg[i];
      ind++;
    }
  }
}

/*
  Fonction qui renvoie le nombre de caractère lu depuis une entrée console
*/
int mini_scanf(char *buffer, int size_buffer){
    int result = read(1,buffer, size_buffer); //lit une entrée de la taille du buffer sur le terminal
    char *temp = mini_calloc(sizeof(char),1); //allocation d'espace de stockage de l'entrée
    if(temp  == NULL) // Levée d'erreur
    {
      mini_perror("Error calloc:");
      mini_exit();
    }
    if (result == size_buffer){ //lorsque l'entree depasse la taille du buffer on lit jusque la fin pour finir proprement mais on ne compte pas tout caractere supplementaire
      if (read(1,temp,1) ==-1)
      {
        mini_perror("Error read");
        mini_exit();
      }
      while (temp[0] != '\n')
      {
        if (read(1,temp,1) ==-1)
        {
          mini_perror("Error read");
          mini_exit();
        }
      }
    }
    
    return result;
}

/*
  Fonction qui renvoie la taille d'une chaine de caractère
*/
int mini_strlen(char* msg){
    int i=0;
    while (msg[i] != '\0'){// on parcours caractere par caractere
        i++;
    }
    return i;
}

/*
  Fonction qui recopie la chaine source dans la chaine destination et retourne le nombre de carractere copies
*/
int mini_strcpy(char *source, char *destination){
    int i=0;
    while(source[i]!='\0'){
        destination[i]=source[i]; 
        i++;
    }
    return i;
}

/*
  Fonction qui compare les deux chaines renvoie 1 si différents 0 sinon
*/
int mini_strcmp(char *s, char *d){
  int i=0;
  if (mini_strlen(s)!=mini_strlen(d)) //Une taille différente implique une chaine differente
  {
    return 1;
  }
  while (s[i]!='\0') //Parcours jusque la fin de la chaine de caractere
  {
    if (s[i]!= d[i]) //Detection de difference
    {
      return 1;
    }
    i++;
  }
  return 0;
}

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
static void decimal_itoa(int integer,char result[]){
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


/*
  Fonction qui lors d'une erreur renvoie un message suivi d'un code d'erreur
*/
void mini_perror(char * message){
  int errorcode = errno; //Recupere le code d'erreur
  char * result = mini_calloc(sizeof(char),32); //Attribue de l'espace à la chaine de caractère qui contiendra le code erreur en char
  decimal_itoa(errorcode,result); //conversion de errorcode en char
  mini_printf(message); //affichage du message
  mini_printf(result); //affichage de errorcode en char
}

/*
  Fonction de sortie
*/
void mini_exit_s()
{
  char * mini_buffer = mini_calloc(sizeof(char),2);
  mini_buffer[0] = '\n';
  write(STDOUT_FILENO,buffer,ind);//ecrire le reste du buffer avant de sortir
  write(STDOUT_FILENO,mini_buffer,1);//retour a la ligne forcé
  ind=0;
}