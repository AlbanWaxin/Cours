#ifndef NEW_LS_H
#define NEW_LS_H

#include"sys/types.h"
char * mode(mode_t st_mode);
void new_ls_fichier(const char *path, char name);
void new_ls();

#endif