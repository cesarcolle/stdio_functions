
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#include "../include/ring.h"

#define N 5
#define MAX_PIPE 10




void
close_pipe (int tab[2])
{
  close (tab[0]);
  close (tab[1]);
}

void
close_all (int pip[MAX_PIPE][2])
{
  int i = 0;
  for (i = 0; i < MAX_PIPE; i += 1)
    {
      close_pipe (pip[i]);
    }

}

void
close_all_except (int pip[MAX_PIPE][2], int rank)
{
  int i = 0;
  for (i = 0; i < MAX_PIPE; i += 1)
    {
      if (i != rank)
	close_pipe (pip[i]);
    }

}

void
station (int rank)
{
  close (1);
  char buff[LENGTH_MSG];
  memset (buff, 0, LENGTH_MSG - 1);
  read (0, buff, LENGTH_MSG);
  fprintf (stderr, "fils num %d a recus : %s\n", rank, buff);
  dup2 (1, 0);
  printf ("%s\n", buff);

}


void
ring (int n)
{
  char str[3];
int other;
  int i;
  int pip[MAX_PIPE][2];
  for (i = 0; i < n; i++)
    {
      pipe (pip[i]);
    }
  for (i = 0; i < n; i++)
    {
      switch (fork ())
	{
	case 0:
	other = (i - 1) % (n);
	  dup2 (pip[i][1], 1);
	  if (i == 0)other = n-1;
	  dup2 (pip[other][0], 0);
	  sprintf (str, "%d", i);
	  close_all (pip);
	  execl ("./station.exe", "./station.exe", str, NULL);
	  perror ("erreur exec\n");
	  break;

	}

    }
  close_all (pip);
  for (i = 0; i < n; i += 1)
    {
      wait (NULL);
    }

}

int
main (int argc, char *argv[])
{
  ring (10);
  return 0;
}
