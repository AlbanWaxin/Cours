#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

extern char ** environ;

int main(int argc, char **argv){
	int i=1;
	while (i<argc){
		printf("%s\n", getenv(argv[i]));
		i++;	
	}
}
