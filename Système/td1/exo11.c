#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char ** argv){
	int ret=syscall(SYS_write, 3, "hello\n", 6);
	printf("%i\n", ret);
	printf("Erreur : %s\n",strerror(errno));
}
