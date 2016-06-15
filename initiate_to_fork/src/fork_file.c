#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <assert.h>
#include <dirent.h>

void
info_fork ()
{
  printf ("pid = %d\n", getpid ());
  printf ("pere = %d \n", getppid ());
}



void
write_fork ()
{
  int dentry;
  char *current = "../td3/";
  FILE *f = fopen ("ici.txt", "a");
  DIR *dirp = opendir (".");
  switch (fork ())
    {
    case 0:
      fputs ("toto ", f);
      dentry = dirfd (dirp);
      info_fork ();
      break;

    default:
      fputs ("tata ", f);
      dentry = dirfd (dirp);
      info_fork ();
      break;
    }
  sleep (3);

}


void
multiple_fork ()
{
  int occ = 0;
  pid_t pid;
  int status;
  int N = 10;
  while (((pid = fork ()) != 0) && (occ++ < 9))
    {
    }

  while (N--)
    {
      printf ("%d\n", occ);
    }
  wait (&status);
}

void
exec ()
{
  printf ("stdout :%p\n", stdout);
  switch (fork ())
    {
    case 0:
      printf ("fils: stdout: %p, %d\n", stdout, getpid ());
      execlp ("./affic_pid.exe", "affic_pid.exe", NULL);
      break;
    default:
      printf ("je suis le père\n");
      break;


    }



}




int
main (int argc, char *argv[])
{

  write_fork ();
  return 0;
}
