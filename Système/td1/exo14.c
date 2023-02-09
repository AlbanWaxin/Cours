#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int main(int argc, char ** argv){
	struct passwd *pwd = getpwnam(argv[1]);
	printf("%s \n%s \n%d \n%d \n%s \n%s \n%s\n",pwd->pw_name,pwd->pw_passwd,pwd->pw_uid, pwd->pw_gid,pwd->pw_gecos,pwd->pw_dir,pwd->pw_shell); 
    
}
