#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define COMMANDSIZE 2048

char** str_split(char* chaine,const char* delim,int vide){
    
    char** tab=NULL;                    //tableau de chaine, tableau resultat
    char *ptr;                     //pointeur sur une partie de
    int sizeStr;                   //taille de la chaine à recupérer
    int sizeTab=0;                 //taille du tableau de chaine
    char* largestring;             //chaine à traiter
    
    int sizeDelim=strlen(delim);   //taille du delimiteur

    largestring = chaine;          //comme ca on ne modifie pas le pointeur d'origine
                                   //(faut ke je verifie si c bien nécessaire)
    

    while( (ptr=strstr(largestring, delim))!=NULL ){
           sizeStr=ptr-largestring;
     
           //si la chaine trouvé n'est pas vide ou si on accepte les chaine vide                   
           if(vide==1 || sizeStr!=0){
               //on alloue une case en plus au tableau de chaines
               sizeTab++;
               tab= (char**) realloc(tab,sizeof(char*)*sizeTab);
                              
               //on alloue la chaine du tableau
               tab[sizeTab-1]=(char*) malloc( sizeof(char)*(sizeStr+1) );
               strncpy(tab[sizeTab-1],largestring,sizeStr);
               tab[sizeTab-1][sizeStr]='\0';
           }
           
           //on decale le pointeur largestring  pour continuer la boucle apres le premier elément traiter
           ptr=ptr+sizeDelim;
           largestring=ptr;
    }
    
    //si la chaine n'est pas vide, on recupere le dernier "morceau"
    if(strlen(largestring)!=0){
           sizeStr=strlen(largestring);
           sizeTab++;
           tab= (char**) realloc(tab,sizeof(char*)*sizeTab);
           tab[sizeTab-1]=(char*) malloc( sizeof(char)*(sizeStr+1) );
           strncpy(tab[sizeTab-1],largestring,sizeStr);
           tab[sizeTab-1][sizeStr]='\0';
    }
    else if(vide==1){ //si on fini sur un delimiteur et si on accepte les mots vides,on ajoute un mot vide
           sizeTab++;
           tab= (char**) realloc(tab,sizeof(char*)*sizeTab);
           tab[sizeTab-1]=(char*) malloc( sizeof(char)*1 );
           tab[sizeTab-1][0]='\0';
           
    }
    
    //on ajoute une case à null pour finir le tableau
    sizeTab++;
    tab= (char**) realloc(tab,sizeof(char*)*sizeTab);
    tab[sizeTab-1]=NULL;

    return tab;
}

static void command_exec(char* command_name,char** command){
    pid_t id_fils;
    int hold = 0;
    id_fils = fork();
    if (id_fils ==-1)
    {
        perror("Error fork:");
        return;
    }
    else if(id_fils==0){
        if(execve("./td7_lancement",command,NULL)){
            perror("Error exec");
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
    char *buffer = malloc(COMMANDSIZE);
    if (!buffer)
    {
        perror("Error calloc");
        return 1;
    }
    int fin = 0;
    while (fin != 1)
    {
        write(1, ">> ",3);
        if (scanf( "%[^\n]", buffer )<0)
        {
            fin =1;
        }
        char* word = malloc(COMMANDSIZE);
        char** tokens;
        stpcpy(word,buffer);
        tokens = str_split(word, " ",0);
        printf("%s\n",tokens[0]);
        if (strncmp(tokens[0],"head",strlen(tokens[0]))==0)
        {
            command_exec(tokens[0],tokens);
        }   
        else if (strncmp(tokens[0],"tail",strlen(tokens[0]))==0)
        {
            command_exec(tokens[0],tokens);
        }
        else if (strncmp(tokens[0],"grep",strlen(tokens[0]))==0)
        {
            command_exec(tokens[0],tokens);
        }
        else if (strncmp(tokens[0],"clean",strlen(tokens[0]))==0)
        {
            command_exec(tokens[0],tokens);
        }
        else if (strncmp(tokens[0],"touch",strlen(tokens[0]))==0)
        {
            command_exec(tokens[0],tokens);
        }
        else if (strncmp(tokens[0],"cat",strlen(tokens[0]))==0)
        {
            command_exec(tokens[0],tokens);
        }
        else if (strncmp(tokens[0],"echo",strlen(tokens[0]))==0)
        {
            command_exec(tokens[0],tokens);
        }
        else if (strncmp(tokens[0],"wc",strlen(tokens[0]))==0)
        {
            command_exec(tokens[0],tokens);
        }
        else if (strncmp(tokens[0],"ls",strlen(tokens[0]))==0)
        {
            command_exec(tokens[0],tokens);
        }
        else if (strncmp(tokens[0],"exit",strlen(tokens[0]))==0)
        {
            break;
        }
        else
        {
            printf("Not a command\n");
        }
        free(word);
        free(tokens);
    }
    return 0;
}
