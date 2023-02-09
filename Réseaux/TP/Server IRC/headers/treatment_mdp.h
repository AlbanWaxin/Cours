#ifndef STARTING
#define STARTING

#include <stdio.h>
#include "../headers/mdp.h"
#include <unistd.h>

mdp_list *initiate_list_through_file(mdp_list *list);
void modify_file(mdp_list *list);

#endif