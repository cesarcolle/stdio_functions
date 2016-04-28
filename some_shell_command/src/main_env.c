#include "../include/my_printenv.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>


int
main (int argc, char *argv[])
{
    if (argc > 1){
        int i = 1;
        while (i < argc){
            affic_environ_several(argv[i]);
            i++;
        }
    }
    else{
        affic_environ();
    }
    return 0;
}
