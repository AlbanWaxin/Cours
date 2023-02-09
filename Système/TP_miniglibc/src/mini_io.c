#include "mini_lib.h"
#include <unistd.h>
#include "sys/syscall.h"
#include "sys/types.h"
#include "sys/errno.h"
#include <sys/stat.h>
#include <fcntl.h>

#define IOBUFFER_SIZE 2048
typedef struct file_element file_element; //structure liste chainée de fichiers
struct file_element
{
    MYFILE * file;
    file_element *next_file;
};
file_element *file_list = NULL; //initialisation de la liste de fichiers

/*
    fonction qui ajoute un element a la liste chainee
*/
static void add_file(MYFILE *new_file){
    file_element *file_elt; 
    file_element *current_elt;
    file_elt = mini_calloc(sizeof(file_element),1);
    if (!file_elt) //levee d'erreur
    {
        mini_perror("Error calloc");
        mini_exit();
    }
    file_elt->file = new_file;
    file_elt->next_file = NULL;
    if (file_list == NULL) //premiere ouverture de fichier
    {    
        file_list = file_elt;
    }
    else
    {
        current_elt = file_list;//on se place au debut 
        while (current_elt->next_file != NULL) //parcours de la liste jusqu'au bout
        {
            current_elt = current_elt->next_file;
        }
        current_elt->next_file = file_elt;
    }        
}

static void remove_file(MYFILE *file){
    file_element *file_elt = file_list;
    file_element *prev_elt;
    while (file_elt->file != file) //recherche de l'element qui a pour fichier celui en parametre
    {
        prev_elt = file_elt;
        file_elt = file_elt->next_file;
    }
    prev_elt->next_file = file_elt->next_file;
    mini_free(file_elt);//liberation de la case
}

MYFILE *mini_fopen(char *file,char mode){
    MYFILE *myfile = mini_calloc(sizeof(MYFILE),1);
    if(myfile  == NULL) // Levée d'erreur
    {
      mini_perror("Error calloc:");
      mini_exit();
    }
    myfile->ind_read = -1;
    myfile->ind_write = -1;
    if (mode == 'r') //Lecture uniquement
    {
        myfile -> fd = open(file, O_CREAT | O_RDONLY,S_IRWXU);
    }
    if (mode == 'w') //Ecriture uniquement
    {
        myfile -> fd = open(file, O_CREAT | O_WRONLY,S_IRWXU);
    }
    if (mode == 'b') //Lecture et ecriture
    {
        myfile -> fd = open(file, O_CREAT | O_RDWR,S_IRWXU);
    }
    if (mode == 'a') //Ecriture et ajout
    {
        myfile -> fd = open(file, O_CREAT | O_WRONLY | O_APPEND,S_IRWXU);
    }
    if (mode == 't') //Tronc
    {
        myfile -> fd = open(file, O_CREAT | O_WRONLY | O_TRUNC,S_IRWXU);
    }
    if (myfile -> fd == -1)
    {
        mini_perror("Error open:");
    }
    add_file(myfile);
    return myfile;
}

/*
    Fonction qui reremplit un buffer de \0 pour eviter les artefactes
*/
static void remplir_buffer_0(char* buffer){
    for (size_t i = 0; i < IOBUFFER_SIZE; i++)
    {
        buffer[i] = '\0';
    }
    
}

/*
    Fonction qui lit l'entree venant d'un document (lecture bufferisee on lit a taille fixe et on reecrit ce qui a reelemenet ete lu) et l'ecrit dans un buffer et renvoie le nombre de lettres lues 
*/
int mini_fread(void *buffer, int size_element, int number_element, MYFILE *file) {
    if (file->ind_read == -1) 
    { //Premier appel
        file->ind_read = 0; 
        file->buffer_read = mini_calloc(IOBUFFER_SIZE, 1); //Allocation memoire du buffer de lecture du fichier 
        read(file->fd, file->buffer_read, IOBUFFER_SIZE); //Lecture bufferisee
    }
    int j = 0;
    while (j < number_element) { 
        if (file->ind_read == IOBUFFER_SIZE)
        {
            remplir_buffer_0((char *) file->buffer_read);
            if (read(file->fd, file->buffer_read, IOBUFFER_SIZE)==0) 
            {  
                return j;
            }
            file->ind_read = 0;
        }
        if (((char *) file->buffer_read)[file->ind_read] == '\0')
        {
            ((char *) buffer)[j] = '\0';
            return j;
        }
        ((char *) buffer)[j] = ((char *) file->buffer_read)[file->ind_read];
        file->ind_read += 1;
        j+= 1;
    }
    return j;
}

/*
    fonction qui écrits le contenu d'un buffer dans le fichier passé en argument_
*/
int mini_fwrite(void *buffer, int size_element, int number_element, MYFILE *file) {  
    int k = 0;//stockage des sorties 
    int result =0;
    if (file->ind_write == -1) 
    {
        file->ind_write = 0;
        file->buffer_write = mini_calloc(IOBUFFER_SIZE, 1);
    }
    int counter = 0; // nombre de charactère ecrits
    while (counter < number_element) 
    {
        if (file->ind_write == IOBUFFER_SIZE) // ecriture quand le buffer de write est vide
        {
            k = write(file->fd,file->buffer_write,IOBUFFER_SIZE); 
            result += k;
            file->ind_write = 0;
            if (k==0) 
            {  
                return result;
            }
            if (k==-1)
            {
                mini_perror("Error write:");
                return -1;
            }
        }
        if (((char *) buffer)[counter] == '\0')//ecrire la fin du fichier
        {
            ((char *) file->buffer_write)[file->ind_write] = '\0';
            return result;
        }
        ((char *) file->buffer_write)[file->ind_write] = ((char *) buffer)[counter]; //inscrire les valeur (cast en char peut peut etre pose probleme dans certains cas)
        file->ind_write++;
        counter++;     

    };
    return result;
}
/*
    Fonction qui ecrit ce qui reste dans le buffer write dans le fichier
*/
int mini_fflush(MYFILE *file){
    int k=0;
    k =write(file->fd,file->buffer_write,file->ind_write);
    file->ind_write = 0; //on replace l'index a 0
    if (k==-1)//levee d'erreur
    {
        mini_perror("Error write:");
        return -1;
    }
    return k; 
}

/*
    Fonction qui ferme un fichier et libere l'espace qui lui correspond
*/
int mini_fclose(MYFILE *file){
    if (file->ind_write != -1)
    {
        mini_fflush(file);
    }
    if (close(file->fd) == -1)
    {
        mini_perror("Error close:");
        return -1;
    }
    mini_free(file);
    remove_file(file);
    return 0;    
}

/*
    Fonction qui lit un seul caractère
*/
int mini_fgetc(MYFILE* file){
    char mini_buffer;
    if (mini_fread(&mini_buffer,sizeof(char),1,file) == -1)
    {
        mini_perror("Error read:");
        return -1;
    }
    return mini_buffer;
}

/*
    Fonction qui ecrit un seul charactrere
*/
int mini_fputc(MYFILE *file,char c){
    char *mini_buffer = mini_calloc(sizeof(char),2);
    if (!mini_buffer)
    {
        mini_perror("Error calloc:");
        return -1;
    }
    mini_buffer[0]= c;
    mini_buffer[1]= '\0';
    if (mini_fwrite(mini_buffer,sizeof(char),2,file)==-1)
    {
        mini_perror("Error write:");
        return -1;
    }
    mini_fflush(file);
    return 0;
}

/*
    Fonction de sortie qui ferme tous les fichiers ouverts
*/
void mini_exit_io(){
    file_element *file_elt = file_list;
    file_element *next_elt;
    while ((file_elt) != NULL)
    {
        next_elt = file_elt->next_file;
        mini_fclose(file_elt->file);
        file_elt = next_elt;
    }   
}