#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct struct_eleve struct_eleve; //structure liste chainée de fichiers
struct struct_eleve
{
    char nom[8] ;
    int note;
};

void enter_one_note(struct_eleve *eleve,FILE * file)
{
    char *buffer_name;
    buffer_name = malloc(9*sizeof(char));
    strncpy(buffer_name,eleve->nom,8);
    fwrite(buffer_name,sizeof(char),8,file);
    fwrite(eleve->nom,sizeof(int),2,file);
    fwrite("\n",sizeof(char),1,file);
}

void enter_note(char *notes[],int nombres){
    int i;
    FILE * fd;
    if ((fd = fopen("note.dat","a+")) == NULL){
        perror("Error open");
        _exit(1);
    }
    for (i=0; i < nombres-1;i++){
        struct_eleve *eleve;
        eleve = malloc(sizeof(struct_eleve));
        strncpy(eleve->nom,notes[i],8);
        eleve->note = strtol(notes[i+1],NULL,10);
        enter_one_note(eleve,fd);
    }
}

int main(int argc, char *argv[])
{   
    int nb = argc -1; 
    enter_note(argv, nb);
    return 0;
}
