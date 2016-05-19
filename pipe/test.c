#include <stdio.h>

#include <string.h>

int
main (int argc, char *argv[])
{
    FILE *f;
    f = fopen("/dev/tty", "r");
    printf("go\n");
    char buff[40];
    memset(buff, 0, 39);
    fscanf(f,"%s", buff);
    printf("buff : %s\n", buff);
    fclose(f);
    f = fopen("/dev/tty", "w");
    fprintf(f, "a");
    //fputs(f, "WE ARE WONG\nOR NOT");
    
    return 0;
}
