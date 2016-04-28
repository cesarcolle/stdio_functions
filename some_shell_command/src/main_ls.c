
#include "../include/my_ls.h"

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

int main(int argc, char * argv[]){
    if (argc > 1){
        information_file(argv[1]);
    }
    else{
    fprintf(stderr, "entrer un répertoire a analyser");
    }


return 0;
}
