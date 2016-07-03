#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "../inc/file_processing.h"
#include <sys/types.h>
#include <fcntl.h>
#define MAXBUFF 50
#define USER_PERM (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

/**
* File_processing contains some functions able to :
*
* - say if the file is a driectory or not 
* - open it properly
* - write on it
* - ....
**/

/**
* Return True/False if the file exist.
*
**/
int
file_exist (char *path)
{
  int fdin;
  if ((fdin = open (path, O_RDONLY)) == -1)
    {
      return 0;
    }
  return 1;
}



int
isRep (char *rep)
{
  struct stat sbuf;

  if (stat (rep, &sbuf) >= 0)
    {
      return S_ISDIR (sbuf.st_mode);
    }
  return 0;
}

/**
*write the @buff to @path file . 
**/
void
write_file (char *buffer, char *path, int size)
{
  int fdout;
  if ((fdout = open (path, O_WRONLY | O_CREAT | O_TRUNC, USER_PERM)) == -1)
    {
      perror ("erreur open fdout \n");

    }
  write (fdout, buffer, size);
}

/**
*Open and read a file with the path given by user.
* @path : path to the file openning
* @dest : path to the destination
**/

int
open_and_read (char *path, char *dest)
{
  int fdin;
  struct stat statbufsour;
  if ((fdin = open (path, O_RDONLY)) == -1)
    {
      perror ("open fdin \n");
      fprintf (stderr, "%s\n", path);
      return -1;
    }

  if (stat (path, &statbufsour) == -1)
    {
      perror ("stat\n");
      close (fdin);
      return -1;
    }
	char * res = calloc(MAX, sizeof(char));
    #ifdef DEBUG
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
	#endif 
	/*bugged : free corruption ==> memory leek...*/
	//free(res);
	return 1;
}
