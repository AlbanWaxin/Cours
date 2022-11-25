#include <unistd.h> //necessaire
#include "sys/errno.h" //implemente la fonction errno pour la levée d'erreur
#include "sys/syscall.h"
#include "sys/types.h"
#include "mini_lib.h" //notre librairie


//Structure qui représente un bloc de mémoire alloué, sa taille et l'adresse du prochain bloc
typedef struct malloc_element malloc_element; 
struct malloc_element
{
    void * block;
    int    statut;
    size_t size;
    malloc_element *next_malloc;
};

//Liste de structure, pointeur sur le premier bloc mémoire ajouté 
malloc_element *malloc_list = NULL;  

/*
  Fonction qui cherche dans la liste des blocs calloc si un bloc existant, libre et suffisament grand existe 
*/
static void  * find_block(int sizes,malloc_element **blockpre){ 
    malloc_element *current = malloc_list;  //initialisation de la liste de blocs à parcourir 
    while (current && !(current->size >= sizes && current->statut == 0)) /*On cherche en itérant sur la liste chainée tant que l'on ne trouve pas d'emplacement ou qu'on arrive au bout de la liste*/
    {
        *blockpre = current; 
        current = current->next_malloc;
    }
    return current;
}

/*
  Fonction qui alloue un bloc memoire par appels a sbrk
*/
static void * alloc_block(int size){/*Fonction supplémentaire pour éviter le duplicas de code pour les differents cas ou l'on doit allouer de l'espace (malloc_list vide ou aucun block disponible)*/
    malloc_element *element;
    element = sbrk(sizeof(malloc_element)); //deplacement du heap, allocation d'un espace mémoire pour la structure
    if ( element == (void *)-1)
    {
        //vérification de la réussite du sbrk
        mini_perror("Erreur%s survenue\n");
        return NULL;
    }

    char *buffer = sbrk(size); //allocation du bloc mémoire
    for (size_t i = 0; i < size; i++)
    {
        buffer[i] = '\0';
    } 
    element->block = buffer;
    element->size = size;
    element->next_malloc = NULL;
    element->statut = 1;
    return element;
}

/*
  Fonction qui alloue un espace mémoire pour un nombre et taille de donée donné sous la forme de structure malloc_element 
*/
void * mini_calloc(int size_element, int number_element){
    malloc_element *output; 
    if (!malloc_list)//premier appel calloc
    {
     output = alloc_block(size_element*number_element);
     malloc_list = output;
    }
    else    
    {   
        malloc_element *blockpre;
        output = find_block(size_element*number_element, &blockpre); 
        if (!output)
        {   
            output = alloc_block(size_element*number_element);
            blockpre->next_malloc = output;
            if (!output){ //Levée d'erreur
                mini_perror("Error allocation");
                return NULL;
            }
        }
        else{
            output->statut = 1; //Nouvel etat d'occupation du bloc
        }
    }
    return (output+1);
} 

/*
    Fonction qui libère les blocs mémoire en mettant leur statut a non utilise
*/
void mini_free(void * ptr){
    malloc_element *element = (malloc_element *)ptr -1;
    if (element->statut == 1)
    {
        element->statut = 0;
    }
}

/*
 Fonction de sortie globale
*/
void mini_exit(){ 
    mini_exit_s();
    mini_exit_io();
    malloc_element *element = malloc_list;
    while (element != NULL)
    {
        if (element->statut == 1){
            mini_free(element->block);
        }
        element = element->next_malloc;
    } 
    _exit(0);
}


