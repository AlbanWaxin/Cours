#include <string.h>
#include "headers/traitement_text.h"

char * compose_message(char * name, char * message){
    int size_name  = strlen(name);
    int size_message = strlen(message);
    int size = size_name + size_message + 2;
    char * buffer = (char *)malloc(size);
    strcpy(buffer, name);
    strcat(buffer, ": ");
    strcat(buffer, message);
    return buffer;
}