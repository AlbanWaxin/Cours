#ifndef _MINI_LIB
#define _MINI_LIB
typedef struct MYFILE MYFILE;
struct MYFILE
{
    int fd;
    void * buffer_read;
    void * buffer_write;
    int ind_read;
    int ind_write;    
};
extern void * mini_calloc(int size_element, int number_element);
extern void mini_free(void * ptr);
extern void mini_exit();


extern void mini_printf(char * str);
extern int mini_scanf(char *buffer,int size_buffer);
extern int mini_strlen(char * msg);
extern int mini_strcpy(char *s, char *d);
extern int mini_strcmp(char *s, char *d);
extern void mini_perror(char * message);
extern void mini_exit_s();


extern MYFILE *mini_fopen(char *file,char mode);
extern int mini_fread(void *buffer,int size_element, int number_element, MYFILE* file);
extern int mini_fwrite(void* buffer,int size_element, int number_element, MYFILE* file);
extern int mini_fflush(MYFILE *file);
extern int mini_fclose(MYFILE *file);
extern int mini_fgetc(MYFILE *file);
extern int mini_fputc(MYFILE *file,char c);
extern void mini_exit_io();

#endif