#include <string.h>
#include "headers/traitement_text.h"

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

char * fuse_strings(char* part1,char* part2){
    int size1 = strlen(part1);
    int size2 = strlen(part2);
    char* fused = (char*) malloc(size1+size2+1);
    strncpy(fused,part1,size1);
    strcat(fused,part2);
    return fused;
}

char * compose_message(char * name, char * message){
    int size_name  = strlen(name);
    int size_message = strlen(message);
    int size = size_name + size_message + 2;
    char * buffer = malloc(size);
    bzero(buffer,size);
    strcpy(buffer, name);
    strcat(buffer, ": ");
    strcat(buffer, message);
    return buffer;
}

int is_command(char * message){
    char command_handler = '/';
    char first =  message[0];
    if (command_handler == first){
        return 1;
    }
    else{
        return 0;
    }
}

int max(int a, int b){
    return a>b?a:b;
}

