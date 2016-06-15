#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <assert.h>
#include <dirent.h>




void
exec_cd ()
{
  execlp ("cd", "cd", NULL);
}

void
exec_who ()
{
  execlp ("who", "who", NULL);
  perror ("erreur WHO\n");
}


void
exec_ls ()
{
  execlp ("ls", "ls", "-l", "-s", ".", NULL);
  perror ("erreur LS\n");
}

void
exec_ls_cd ()
{
  execlp ("ls", "ls", "-l", "-s", environ_several ("HOME"), NULL);
  perror ("erreur LS\n");
}

void
execute ()
{
  pid_t pid;
  pid = fork ();
  int status;
  // execute the WHO
  if (pid == 0)
    {
      printf ("exec who \n");
      exec_who ();
    }
  wait (&status);
  pid = fork ();
  if (pid == 0)
    {
      exec_ls ();
    }
  return;
}

int
main (int argc, char *argv[])
{

  execute ();
  return 0;
}
