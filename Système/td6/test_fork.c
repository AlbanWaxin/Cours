#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char **argv){
    pid_t id = fork();
    if(id < 0){
        perror("fork");
        return 1;
    }
    if(id == 0){
        printf("fils : %d\n",getpid());
        //sleep(0.5); //ici pour orphelin
        sleep(2);
        printf("%d père de %d\n",getppid(),getpid());
        exit(2);
    }
    else {
        sleep(100);
        pid_t pidz =wait(&id);
        printf("%d est né\n",getpid());
        if (WIFEXITED(id))
            printf("%d mon fils %d normal,\n %d code de retour: %d\n",getpid(), pidz,getpid(), WEXITSTATUS(id));
        else
            printf("%d anormlement\n",getpid());
    }
    return 0;
}