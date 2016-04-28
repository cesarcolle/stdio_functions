#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/my_printenv.h"
/*
*author: @CésarCollé
*version : 1.0
*	support :
*
*last update : 24 / 03 / 2016
*Printenv is a function who will display some information on the Linux Systeme of user.
*/
extern char **environ;

void
affic_environ ()
{
  while (*environ)
    {
      printf ("%s\n", *environ);
      (environ)++;
    }
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


void
affic_environ_several (const char *values)
{
  while (*environ)
    {
      if (start_with (*environ, values))
	{
	  printf ("%s\n", *environ);
	  return;
	}
      environ++;
    }
    fprintf(stderr, "%s is not a part of Environ\n", values);
}
