#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv){
    int fd = open(argv[1], O_RDWR);
    pid_t id = fork();
    char* foo = "foo";
    char* bar = "bar";
    char* buf;
    memset(buf,0,1024);
    if(id < 0){
        
        perror("fork");
        return 1;
    }
    if(id == 0){
        lseek(fd, 3, SEEK_SET);
        write(fd, foo, sizeof(foo));
        sleep(2);
        lseek(fd, 3, SEEK_SET);
        bzero(buf,1024);
        read(fd, buf, sizeof(foo));
        printf("%s\n", buf);
        exit(2);
    }
    else {
        lseek(fd,3,SEEK_SET);
        write(fd,bar,sizeof(bar));
        sleep(1);
        lseek(fd, 3, SEEK_SET);
        bzero(buf,1024);
        read(fd, buf, sizeof(bar));
        printf("%s\n",buf);
        pid_t pidz =wait(&id);
        printf("%d est né\n",getpid());
        if (WIFEXITED(id))
            printf("%d mon fils %d normal,\n %d code de retour: %d\n",getpid(), pidz,getpid(), WEXITSTATUS(id));
        else
            
            printf("%d anormlement\n",getpid());
    }
    return 0;
}