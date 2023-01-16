#ifndef TRAITEMENT
#define TRAITEMENT

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char ** str_split(char * chaine,const char* delim,int vide);
char * fuse_strings(char * part1,char * part2);
char * compose_message(char * name, char * message);
int is_command(char * meassage);
int max(int a,int b);
#endif