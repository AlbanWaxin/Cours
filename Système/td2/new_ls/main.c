#include <unistd.h>
#include "stdio.h"
#include "new_ls.h"
#include "string.h"

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        return 0;
    }
    if (strcmp(argv[1],"-l") == 0){
        new_ls();
    }
    return 0;
}
