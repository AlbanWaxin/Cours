#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char ** argv){
	int ret=syscall(SYS_write, 3, "hello\n", 6);
	printf("%i\n", ret);
	perror("Erreur");
}
