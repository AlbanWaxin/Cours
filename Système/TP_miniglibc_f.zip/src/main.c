#include "mini_lib.h"
//#include "stdio.h"
#define TEMP_BUFF_SIZE 1500 

int main (int argc, char ** argv){//zone de test des fonctions, les fonctions revoyant un int sont teste par des printf en commentaire
    
    //test d'allocation memoire
    void *zone1=mini_calloc(sizeof(int),5);
    void *zone2=mini_calloc(sizeof(int),5);
    void *zone3=mini_calloc(sizeof(int),4);
    mini_free(zone2);
    void *zone4=mini_calloc(sizeof(int),8);
    mini_free(zone1);
    mini_free(zone3);
    mini_free(zone4);


    char *str="Test d'écriture sur une seule ligne sans retour à la ligne.";
    mini_printf(str);
    mini_printf("\n");// force le retour a la ligne
    mini_printf("test");


    //printf("%d\n",mini_scanf(str,10)); //test de la sortie du scanf   


    MYFILE *myfile = mini_fopen("../README.txt",'r');
    char* buffer_read = mini_calloc(sizeof(char),TEMP_BUFF_SIZE + 1);
    mini_fread(buffer_read,sizeof(char), TEMP_BUFF_SIZE, myfile);
    mini_printf(buffer_read);
    MYFILE *second_file = mini_fopen("./autre.txt",'a');
    //int k;
    /*k = */mini_fwrite("salut c'est moi qui décide comment on fait",sizeof(char),45,second_file);
    //printf("%d\n",k);
    /*k = */mini_fflush(second_file);

    MYFILE *third_file = mini_fopen("./putget.txt",'b');
    mini_fputc(third_file,'l');
    MYFILE *fourth_file = mini_fopen("./putget.txt", 'r');
    char *mini_buffer = mini_calloc(sizeof(char),2);
    *(mini_buffer) = mini_fgetc(fourth_file);
    mini_printf(mini_buffer);
    mini_exit();
    
}