#include "mini_lib.h"
#include <unistd.h>
#include "sys/syscall.h"
#include "sys/types.h"
#include "sys/errno.h"
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{   
    char *file = argv[1];
    MYFILE *myfile = mini_fopen(file,'b');
    mini_fclose(myfile);
    return 0;
}