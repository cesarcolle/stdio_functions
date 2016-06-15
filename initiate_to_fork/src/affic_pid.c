#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <assert.h>
#include <dirent.h>

/**
* A little program who will just throw the current pid of the process to the stdout.
*
* author : @CésarCollé
* Wed 18 May 2016 03:47:25 PM CEST 
* version 1.0
*
**/

int
main (int argc, char *argv[])
{
  printf ("%d\n", getpid ());
  return 0;
}
