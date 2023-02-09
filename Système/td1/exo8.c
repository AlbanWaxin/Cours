#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char ** argv){
	syscall(SYS_write, STDOUT_FILENO, "hello\n", 6);
}
