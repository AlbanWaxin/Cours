#include "stdio.h"
#include <sys/types.h>
#include <pwd.h>
#include "grp.h"
#include <sys/stat.h>
#include <unistd.h>
#include "time.h"
#include "stdlib.h"
#include "dirent.h"



char mode(mode_t st_mode){
	char ret[10];
	switch (sb.st_mode & S_IFMT) {
    		case S_IFBLK: ret[0] = 'b';          break;
    		case S_IFCHR: ret[0] = 'c';          break;
    		case S_IFDIR: ret[0] = 'd';          break;
    		case S_IFIFO: ret[0] = 'f';          break;
    		case S_IFLNK: ret[0] = 'l';          break;
    		case S_IFREG: ret[0] = 'r';          break;
    		case S_IFSOCK: ret[0] = 's';         break;
    		default:       ret[0] = '-';         break;
    	}
	(st_mode & S_IRUSR)? ret[1] = 'r' : ret[1] = '-';
	(st_mode & S_IWUSR)? ret[2] = 'w' : ret[2] = '-';
	(st_mode & S_IXUSR)? ret[3] = 'x' : ret[3] = '-';
	(st_mode & S_IRGRP)? ret[4] = 'r' : ret[4] = '-';
        (st_mode & S_IWGRP)? ret[5] = 'w' : ret[5] = '-';
        (st_mode & S_IXGRP)? ret[6] = 'x' : ret[6] = '-';
	(st_mode & S_IROTH)? ret[7] = 'r' : ret[7] = '-';
        (st_mode & S_IWOTH)? ret[8] = 'w' : ret[8] = '-';
        (st_mode & S_IXOTH)? ret[9] = 'x' : ret[9] = '-';
	return ret;

}



void new_ls_fichier(const char *path, char name) {
  struct stat st;
  if (stat(path, &st) != 0)
  {  
    perror("stat() error");
  }
  else 
  {
    printf("%s ", mode(st.st_mode));
    printf("%d ", st.st_nlink);
    printf("%s ",getpwuid(st.st_uid)->pw_name);
    printf(" %s ", getgrgid(st.st_gid)->gr_name);
    printf("%d ", st.st_size);
    char outstr[200];
    if (strftime(outstr,sizeof(outstr),"%a %e %h %Y %H:%M:%S",localtime(&(st->st_mtime)) == 0));
    {
    	perror("strftime() error");
    }
    else
    {
        printf("%s",strftime(outstr,sizeof(outstr),"%a %e %h %Y %H:%M:%S",localtime(&(st->st_mtime)))
    }
    printf("%s\n",name);
  }
}

void new_ls(){
	DIR *dossier;
	struct dirent dirc;
	while (dirc = readdir(dossier)){
		if (!strcmp(dirc -> d_name
	}

}
