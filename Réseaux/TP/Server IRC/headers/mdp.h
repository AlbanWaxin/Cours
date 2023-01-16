#ifndef MDP
#define MDP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char pseudo[256];
    char password[256];
} logins;

int read_file(const char *file_name);
void write_file(logins *logs,const char *file_name);
