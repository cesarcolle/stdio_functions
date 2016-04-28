#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../include/my_cp.h"
#define DEBUG
/**
*my_cp will implement the cp command bash.
* i.e : this function copy the fich1 into the fic2 given by user.
*
*using posix funtion :
* ssize_t read(int fd, void *buf, size_t count);
* author @césarCollé
*Tue 05 Apr 2016 11:30:50 AM CEST 
* version 1.1
*/
#define MAX 200
#define MAXBUFF 150
#define USER_PERM (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

/**
*Open and read a file with the path given by user.
**/

int open_and_read(char * path, char * dest){
	int fdin;
	printf("PATH : %s\n", path);
    struct stat statbufsour;
    if ((fdin=open(path,O_RDONLY))==-1){
      perror("open fdin \n");
      fprintf(stderr,"%s\n",path);
      return -1;
    }

    if (stat(path,&statbufsour)==-1){
      perror("stat\n");
      close(fdin);
      return -1;
    }
	char * res = calloc(MAX, sizeof(char));
    #ifdef DEBUG
    printf("j'alloue : %p'\n", res);
	#endif 
	char buff[MAX];
	int n;
	int total = 0;
	while ((n = read(fdin, buff, MAX))!= 0){
		total+=n;
		if (!total%MAXBUFF){
			res = realloc(res, total+MAXBUFF);
		}
		strcat(res, buff);
	}
		#ifdef DEBUG
	#endif 
	write_file(res,dest,  total);
    #ifdef DEBUG
    printf("de desalloue  : %p'\n", res);
	#endif 
	/*bugged : free corruption ==> memory leek...*/
	//free(res);
	printf("apres free\n");
	return 1;
}

/**
*Return if the path given is a directory or not.
**/

int isRep(char *rep){
  struct stat sbuf;

  if (stat(rep,&sbuf)>=0){
      return S_ISDIR(sbuf.st_mode);
  }
  return 0;
}

/**
*write the @buff to @path file . 
**/
void write_file(char * buffer, char * path, int size){
    int fdout;
    printf("Try to open : %s\n", path);
    if ((fdout=open(path, O_WRONLY|O_CREAT|O_TRUNC, USER_PERM))==-1){
          perror("erreur open fdout \n");
          return;
        }
        printf("ecriture ... %p\n", buffer);
        write(fdout,buffer, size);
}


/**
*name_fic will return 
**/
int name_fic(char * parse){
    int n = strlen(parse)-1;
    while (n-- ){
        if (parse[n] == '/'){
            return n+1;
        }
    }
    return n+1;
}

int my_cp(char * path1, char* path2){
	#ifdef DEBUG
		printf("%s\n%s\n", path1, path2);
	#endif
	char name[MAX];
	if (isRep(path2)){
	    int size_name = name_fic(path1);
	    strcpy(name, path2);
	    strcat(name, "/");
	    strcat(name, path1+size_name);
	    path2 = name;
	}
	
	//read_data
	if ( open_and_read(path1, path2)< 0){
		return -1;
	}

	
	return 1;

}
