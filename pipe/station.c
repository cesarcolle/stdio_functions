#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define LENGTH_MSG 50


int
main (int argc, char *argv[])
{
    int count;   
    char buff[LENGTH_MSG];
    memset(buff, 0, LENGTH_MSG-1);
    fprintf(stderr, "argv1 %s\n", argv[1]);
    if (!strcmp(argv[1], "0")){
        fprintf(stderr,"ecriture\n");
        write(1, "bonjour\n", 8);
    }
    while (1){
        count = read(0, buff, LENGTH_MSG);
        fprintf(stderr, "fils num %s a recu : %s \n", argv[1], buff);
        sleep(1);
        write(1, buff, count);
    }
    return 0;
}
