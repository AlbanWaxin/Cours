#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    if(argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
    }
    return 0;
}