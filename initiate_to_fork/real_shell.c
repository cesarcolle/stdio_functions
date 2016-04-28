#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../erreur.h"
#define MAX 50
extern char **environ;

/**
*Recreate a shell interface. with posix function. and parsing command given by user.
*TODO : clean with the environ element in other directory
*
**/
int file_exist(char * path){
    int fdin;
    if ((fdin=open(path,O_RDONLY))==-1){
      perror("open fdin \n");
      fprintf(stderr,"%s\n",path);
      return 0;
    }
    return 1;
}



/*
*Decide if id start with ptr value
**/
int
start_with (const char *id, char *ptr)
{
  if (strlen (id) < strlen (ptr))
    {
      return 0;
    }
  while (*ptr)
    {
      if (*ptr++ != *id++)
	{
	  return 0;
	}
    }
  return 1;
}


char *
affic_environ_several (const char *values)
{
  while (*environ)
    {
      if (start_with (*environ, values))
	{
	  
	  return *environ;
	}
      environ++;
    }
    fprintf(stderr, "%s is not a part of Environ\n", values);
    exit(0);
}




int isRep(char *rep){
  struct stat sbuf;

  if (stat(rep,&sbuf)>=0){
      return S_ISDIR(sbuf.st_mode);
  }
  return 0;
}






void throw_exception(char * value){
    fprintf(stderr, "erreur saisie de la commande : %s\n", value);
    exit(0);
}

void reset_path(char * ptr){
    void * ptr_memset;
    if ( (ptr_memset = memset(ptr, 0, MAX)) == NULL){
        fprintf(stderr, "erreur memset \n");
    }
    strcpy(ptr, ".");
}

void reset (char * ptr){
    memset(ptr, 0, MAX);
}

int not_opt(char * ptr){
    if (ptr == NULL){
        throw_exception("option");
        
    }
    return ptr[0] == '-';
}
/**
*find in the $PATH variable if the @file given by user exist.
*
**/


char * find_path(char * file){
    char * PATH = affic_environ_several("$PATH");
    char * tok = PATH;
    int size = strlen(file);
    char * tmp;
    while ((tok = strtok(tok, ":")) != NULL){
        tmp = calloc(strlen(tok)+ size + 1, sizeof(char));
        strcat(tmp, tok);
        strcat(tmp, "/");
        strcat(tmp, file);
        if (file_exist(tmp)){
            return tmp;   
        }
        free(tmp);
    }
    ERROR(0);
    return NULL;
}
/**
* We assume the cd commande is on two part : cd + the path
* @command : the command given by user
*@buffer the path buffer update.
**/
int manage_cd(char * command, char * buffer){
    char * tok = command;
    printf("command : %s\n", command);
    if ((tok = strtok(tok, " ")) != NULL){
        if ( strcmp (tok, "cd") == 0){
            tok = NULL;
            if ( (tok = strtok(tok, " ")) != NULL ){
                reset_path(buffer);
                if (!isRep(tok)){
                    ERROR(0);
                    exit(1);
                }

                strcpy(buffer, tok);
                printf("buffer %s : %s\n", buffer, __FUNCTION__);
                return 1;
            }
            else{
                throw_exception("cd");
            }
        }
        else{
            return 0;
        }

    }
    return 0;
}





void shell (){
    char c;
    int i = 0;
    int status;
    char * command= calloc(MAX, sizeof(char));
    char *path = calloc(MAX, sizeof(char));
    reset(command);
    reset_path(path);
    char * tok;
    while ( ((c = getchar()) != EOF) && i < MAX){
        if (c == '\n'){
            printf("COMMAND before fork : %s\n", command);
            printf("path : %p\n");
            switch(fork()){
                case 0:
                    if (!manage_cd(command, path)){
                        printf("not manage cd \n");
                        tok = command;
                        if ((tok = strtok(tok, " ")) != NULL){
                            char * tmp = find_path(tok);
                            printf("PATH : %s\n", tmp);
                        }

                    }
                    printf("fils : paths = %s\n", path);
                    return;
                    break;
                default:
                    printf("pere waiting ...\n");
                    wait(&status);
                    printf("Pere ; path = %s\n", path);
                    printf("RESET !\n");
                    reset(command);
                    i= 0;
                    break;
            }
        }
        else{
            printf("command : %s\n", command);
            command[i++] = c;
        }
    
    }


}




int
main (int argc, char *argv[])
{
    shell();
    return 0;
}
