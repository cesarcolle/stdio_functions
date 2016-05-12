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
      printf("false\n");
      return 0;
    }
    printf("true\n");
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
affic_environ_several (char *values)
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
    char * PATH = affic_environ_several("PATH");
    PATH = PATH + strlen("PATH=");
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
        memset(tmp, 0, strlen(tmp));
        tok = NULL;
        
    }
    ERROR(0);
    fprintf(stderr, "not the file\n");
    exit(1);
}
/**
* We assume the cd commande is on two part : cd + the path
* @command : the command given by user
* @buffer the path buffer update.
**/
int manage_cd(char * command, char * buffer){
    char * copy = calloc(strlen(command), sizeof(char));
    strcpy(copy, command);
    
    char * tok = copy;
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
                int i = 0;
                while (i < strlen(tok)){
                
                    *(buffer+i) = tok[i];
                    i++;
                }
                free(copy);
                printf("buffer %s : %s\n", buffer, __FUNCTION__);
                return 1;
            }
            else{
                throw_exception("cd");
            }
        }
        else{
        free(copy);
            return 0;
        }

    }
    return 0;
}

void new_command(char ** command, char *path){
    command = command +1 ;
    char * tmp;
    int i =0;
    while (*command){
        if ((*command)[0] != '-'){
            tmp = calloc(strlen(path)+strlen(*command), sizeof(char));
            strcat(tmp, path);
            strcat(tmp, *command);
            *command = strdup(tmp);
            free(tmp);
            return;
        }
        i++;
        printf("%s\n", *command);
        command++;
    }
    command[i-1] = strdup(path);
    
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count +1);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    *(result + count) = NULL;
    return result;
}




void shell (char * path, char * command){
    char c;
    int i = 0;
    int status;
    reset(command);
    char * tok;
    
    while ( ((c = getchar()) != EOF) && i < MAX){
        if (c == '\n' && strlen(command) > 1){
            if (! manage_cd(command, path)){
                printf("before fork : %s\n", command);
                int pid = fork();
                if (pid == 0){
                        char ** tab = str_split(command, ' ');
                        printf("\n");
                        new_command(tab, path);
                        printf("tab[0] = %s\n", tab[0]);
                        
                        char * cmd = find_path(tab[0]);
                        tab[0] = strdup(cmd);
                        strcpy(tab[0], cmd);
                        execv(cmd, tab );
                }
                else{
                    wait(&status);
                }
            }
            reset(command);
            i =0;
        }
        else{
            command[i++] = c;
        }
    
    }


}




int
main (int argc, char *argv[])
{
    char * command = calloc(MAX, sizeof(char));
    char * path = calloc(MAX, sizeof(char));

    shell(path, command);
    free(command);
    free(path);
    return 0;
}
