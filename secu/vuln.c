#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    char buf[256];
    if (argc < 2) {
        printf("Usage: %s <input>\n", argv[0]);
        exit(1);
    }
    printf("Address of buf: %p\n", buf);
    strcpy(buf, argv[1]);
    printf("Input: %s\n", buf);
    return 0;
}