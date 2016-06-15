#include <stdio.h>
#include "../include/token.h"
#include <string.h>


/**
*Simple function able to modify a strut token value
* using /dev/tty allowing to the user to enter values.
*
* author : @CésarCollé
* version 1.0
* 05/21/2016 
**/

void vary_token(struct token * ptr_token, int id){
    char cmd[LENGTH_MSG];
    FILE * fout = fopen("/dev/tty", "a+");


    fprintf(stderr, "quelle station ?");
    fscanf(fout, "%s", cmd);
    fclose(fout);
    ptr_token->recepteur =  atoi(cmd);

    fout = fopen("/dev/tty", "a+");
    memset(cmd, 0, LENGTH_MSG -1);
    fprintf(stderr, "message : \n");
    fscanf(fout, "%s", cmd);
    strcpy(ptr_token->msg, cmd);
    ptr_token->expediteur = id;
}
