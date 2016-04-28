#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../include/my_cp.h"
#include "../include/my_cp_recc.h"
#include <assert.h>
#include <dirent.h>
#define MAX 50
/**
* Reccursif Cp , permet de créer les répertoires associer au chemin et de copier le fichier
* dans le dossier final
*author : @césarCollé
*Mon 04 Apr 2016 05:11:05 PM CEST 
*/

void create_directory(char* path){
    if (mkdir(path, S_IRWXU) == -1){
    perror("erreur creation directory \n");
    }
}
/**
*syntaxe_directory : transform ./test/ to ./test 
* juste remove the last '/' into a string given 
**/
void syntaxe_directory(char * src){
    int n = strlen(src)-1;
    if (src[n] == '/'){
        src[n] = '\0';
    }
}
/**
*create copy of ptr1 and ptr2
*
**/
void create_copy_path(char * ptr1, char * ptr2){
    char * tmp = calloc(strlen(ptr1), sizeof(char));
    strcpy(tmp, ptr1);
    ptr1 = tmp;
    
    char * tmp2 = calloc(strlen(ptr2), sizeof(char));
    strcpy(tmp2, ptr2);
    ptr2 = tmp2;

}
/**
*Initate the directory if the user give a directory to past
* else : copy the fil with the first LS version.
*
*/
void initialisation(char * source, char * dest){
    char* tmp;
    create_copy_path(source, dest);
    syntaxe_directory(source);
    struct stat ptr_stat;
    stat(source, &ptr_stat);
    if (S_ISDIR(ptr_stat.st_mode)){
        char * p = source+name_fic(source);
        tmp = calloc(strlen(p) + strlen(dest)+2, sizeof(char));    
        strcpy(tmp, dest);
        strcat(tmp, p);
        create_directory(tmp);
        strcat(tmp, "/");
        dest = tmp;
        char * ptr = calloc(strlen(source)+1, sizeof(char));
        strcpy(ptr, source);
        strcat(ptr, "/");
        my_cp_recc(ptr, tmp);
    }
    else{
        my_cp(source, dest);
    }
}


/**
* copy source into cpy and add cat to cpy ;
**/
void copy_and_cat(char *cpy, char *source, char * cat){
    strcpy(cpy, source);
    strcat(cpy, cat);
}


void my_cp_recc(char * source, char * dest){
    struct stat ptr_stat;
    struct dirent *dentry;
    char * new_dest;
    char * tmp;
  /*open the current directory*/
  DIR * dirp = opendir(source);
  //correct(dest);
  while ((dentry = readdir(dirp)) != NULL){
    if (!(!strcmp(dentry->d_name, "..")|| !strcmp(dentry->d_name, "."))){
      tmp = calloc(strlen(source)+strlen(dentry->d_name)+2, sizeof(char));
      copy_and_cat(tmp, source, dentry->d_name);
      stat(tmp, &ptr_stat);

      // appel reccusif
      if (S_ISDIR(ptr_stat.st_mode)){
        strcat(tmp, "/");
        new_dest = calloc(strlen(dest)+strlen(dentry->d_name)+2, sizeof(char));
        copy_and_cat(new_dest, dest, dentry->d_name);
        // create repository
        create_directory(new_dest);
        strcat(new_dest, "/");
        my_cp_recc(tmp, new_dest);

      }
      // je copie le fichier
      else{
        char * ptr_buff = calloc(strlen(dest)+strlen(dentry->d_name)+2,sizeof(char));
        copy_and_cat(ptr_buff, dest, dentry->d_name);
        if (open_and_read(tmp, ptr_buff) < 0){
        fprintf(stderr, "erreur ecriture");
        exit(1);
        }

      }

    }

}
free(dest);
free(source);
}
