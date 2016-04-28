#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <assert.h>
#include <dirent.h>


int
main (int argc, char *argv[])
{
    printf("%d\n", getpid());
    return 0;
}
