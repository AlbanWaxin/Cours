#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Error: Invalid number of arguments");
    }
    else{
        char *prog = argv[1];
        execvp(prog,argv +1);
        perror("execve");
        return 1;
    }
}