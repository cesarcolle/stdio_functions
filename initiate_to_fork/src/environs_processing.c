#include <stdio.h>
extern char **environ;

/**
* Process to return the $ENVIRON value 
* to fully use the POSIX environement.
* NOTE : find_path(char *) function use the specify $PATH variable.
*author : @CéarCollé
*
*Wed 18 May 2016 03:50:41 PM CEST 
*version : 1.0
*/

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
environ_several (const char *values)
{
  while (*environ)
    {
      if (start_with (*environ, values))
	{

	  return *environ;
	}
      environ++;
    }
  fprintf (stderr, "%s is not a part of Environ\n", values);
  return NULL;
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




