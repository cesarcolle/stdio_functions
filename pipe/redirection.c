
#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

void
simple_redirection (char *cmd, char *out)
{
  int fd =
    open (out, O_WRONLY | O_CREAT | O_TRUNC,
	  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  // redirige le flux d'erreur sur stdout
  dup2 (2, 1);
  // redirige la sortie de stdout vers le fichier !
  dup2 (fd, 1);
  switch (fork ())
    {
    case 0:
      fprintf (stderr, "voilaaaaaaaa");
      execlp (cmd, cmd, NULL);
      break;
    default:
      wait (NULL);
      break;

    }
}



void
close_pipe (int tab[2])
{
  close (tab[0]);
  close (tab[1]);
}


void
pipe_process ()
{
  int pipe_1[2];
  if (pipe (pipe_1) < 0)
    {
      fprintf (stderr, "erreur init pipe 1\n");
    }
  int pipe_2[2];
  if (pipe (pipe_2) < 0)
    {
      fprintf (stderr, "erreur init pipe 1\n");
    }
  /*char msg[50]; */

  if (!fork ())
    {
      dup2 (pipe_1[1], 1);
      close_pipe (pipe_1);
      close_pipe (pipe_2);
      execlp ("ps", "ps", "aux", NULL);
    }
  if (!fork ())
    {
      dup2 (pipe_1[0], 0);
      close_pipe (pipe_1);

      dup2 (pipe_2[1], 1);
      close_pipe (pipe_2);
      execlp ("grep", "grep", "gedit", NULL);
    }


  if (!fork ())
    {

      dup2 (pipe_2[0], 0);
      close_pipe (pipe_2);
      close_pipe (pipe_1);
      execlp ("wc", "wc", "-c", NULL);
    }
  close_pipe (pipe_1);
  close_pipe (pipe_2);
  int i;
  for (i = 0; i < 3; i++)
    {
      wait (NULL);
    }
}




int
main (int argc, char *argv[])
{
  //simple_redirection(argv[1], argv[2]);
  pipe_process ();
  return 0;
}
