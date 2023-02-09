#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void compare(char * path1,char * path2){
    FILE *fd1;
    FILE *fd2;
    if ((fd1 = fopen(path1,"r")) == NULL){
        perror("Error open");
        _exit(1);
    }
    if ((fd2 = fopen(path2,"r")) == NULL){
        perror("Error open");
        _exit(1);
    }
    int bit1;
    int bit2;
    while (((bit1 = fgetc(fd1)) != EOF) && ((bit2 = fgetc(fd2)) != EOF))
    {
        if (bit1 != bit2){
            printf("NOK\n");
            _exit(0);
        }
    }
    if (bit1 == EOF && fgetc(fd2) == EOF)
    {
        printf("OK\n");
        _exit(0);
    }
}




int main(int argc, char *argv[])
{
    if (argc != 3 && argv[0]){
        printf("error argument\n");
        return -1;
    }
    compare(argv[1],argv[2]);
    return 0;
}
