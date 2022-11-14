#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFF_SIZE 1

void mycp(const char *source,char *destination)
{
	int fluxsrc,fluxdest;
	int comp = 0;
	char buffer[BUFF_SIZE];
	fluxsrc = open(source,O_RDONLY);
	fluxdest = open(destination, O_WRONLY | O_CREAT | O_TRUNC,
S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH |
S_IWOTH);	
	while ((comp = read(fluxsrc,buffer,BUFF_SIZE)))

	{
		if(write(fluxdest,buffer,comp) == -1){
			perror("Erreur%s survenue\n");
		}
	}
	close(fluxsrc);
	close(fluxdest);
}

int main(int argc,char *argv[])
{
	mycp(argv[1],argv[2]);
	exit(0);
}
