#include <string.h>
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

#define MAX 50

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
* We assume the cd commande is on two part : cd + the path
* @command : the command given by user
* @buffer the path buffer update.
**/
int manage_cd(char * command, char * buffer){
    char * copy = calloc(strlen(command), sizeof(char));
    strcpy(copy, command);
    char * tok = copy;
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
        command++;
    }
    command[i-1] = strdup(path);
    
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
                int pid = fork();
                if (pid == 0){
                        char ** tab = str_split(command, ' ');
                        new_command(tab, path);                        
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
    while (1){
        switch(fork()){
            case 0:
                shell(path, command);
                break;
            default:
                wait(NULL);
                break;
        }
    }
    free(command);
    free(path);
    return 0;
}
