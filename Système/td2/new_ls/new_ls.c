#include "stdio.h"
#include <sys/types.h>
#include <pwd.h>
#include "grp.h"
#include <sys/stat.h>
#include <unistd.h>
#include "time.h"
#include "stdlib.h"
#include "dirent.h"
#include "string.h"



char * mode(mode_t st_mode){
	char *ret = calloc(10,sizeof(char));
  bzero(ret,10);
	switch (st_mode & S_IFMT) {
    		case S_IFBLK: ret[0] = 'b';          break;
    		case S_IFCHR: ret[0] = 'c';          break;
    		case S_IFDIR: ret[0] = 'd';          break;
    		case S_IFIFO: ret[0] = 'f';          break;
    		case S_IFLNK: ret[0] = 'l';          break;
    		case S_IFREG: ret[0] = '-';          break;
    		case S_IFSOCK: ret[0] = 's';         break;
    		default:       ret[0] = '-';         break;
    	}
  if (st_mode & S_IRUSR){
    ret[1] = 'r';
  }
  else
  {
    ret[1] = '-';
  }
  if (st_mode & S_IWUSR)
  {
    ret[2] = 'w';
  }
  else
  {
    ret[2] = '-';
  }
  if ((st_mode & S_IXUSR))
  {
    ret[3] = 'x';
  }
  else
  {
    ret[3] = '-';
  }
  if (st_mode & S_IRGRP)
  {
    ret[4] = 'r';
  }
  else
  {
    ret[4] = '-';
  }
  if (st_mode & S_IWGRP)
  {
    ret[5] = 'w';
  }
  else
  {
    ret[5] = '-';
  }
  if (st_mode & S_IXGRP)
  {
    ret[6] = 'x';
  }
  else
  {
    ret[6] = '-';
  }
	(st_mode & S_IROTH)? (ret[7] = 'r') : (ret[7] = '-');
  (st_mode & S_IWOTH)? (ret[8] = 'w') : (ret[8] = '-');
  (st_mode & S_IXOTH)? (ret[9] = 'x') : (ret[9] = '-');
	return ret;
}



void new_ls_fichier(const char *path, char * name) {
  struct stat st;
  if (stat(path, &st) != 0)
  {  
    perror("stat() error");
  }
  else 
  {
    printf("%s ", mode(st.st_mode));
    printf("%lu ", st.st_nlink);
    printf("%s ",getpwuid(st.st_uid)->pw_name);
    printf(" %s ", getgrgid(st.st_gid)->gr_name);
    printf("%ld ", st.st_size);
    char outstr[200];
    if ((strftime(outstr,sizeof(outstr),"%a %e %h %Y %H:%M:%S",localtime(&(st.st_mtime)))) == 0)
    {
    	perror("strftime() error");
    }
    else
    {
      printf("%s ",outstr);
    }
    printf("%s\n",name);
  }
}

void new_ls(){
	DIR *dossier;
  if ((dossier = opendir(".")) == NULL) {
    perror("couldn’t open '.'"); 
    return;
  }
	struct dirent *dirc;
  char * debut = calloc(258,sizeof(char));
  char * fin = calloc(258,sizeof(char));
	while ((dirc = readdir(dossier))){
    strcpy(debut,"./");
    strcpy(fin,dirc->d_name);
    strcat(debut,fin);  
		new_ls_fichier(debut,dirc->d_name);
	}
}


void rec_new_ls(char*dossier){
  struct stat statbuf;
  if (dossier == NULL) {
    perror("couldn’t open '.'"); 
    return;
  }
	struct dirent *dirc;
  char * debut = calloc(258,sizeof(char));
  char * fin = calloc(258,sizeof(char));
	while ((dirc = readdir(dossier))){
    if (dirc)
    {
      if(strcmp(".",dirc->d_name) == 0 || strcmp("..",dirc->d_name) == 0)
      {
        rec_new_ls();
      }
    }
    strcpy(debut,"./");
    strcpy(fin,dirc->d_name);
    strcat(debut,fin);  
		new_ls_fichier(debut,dirc->d_name);
	}
}

