#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int load(char *data){
    data[0] = 'A';
    data[1] = 'B';
}

int ici(char *a, char *b){
    int status;
    *a = 'a';
    *b = 'b';
    printf("%c %c\n", *a, *b);
    int pid = fork();
    if (pid == 0){
        *a = 'c';
    }
    else{
        wait(&status);
        
    }
    printf("%c %c\n", *a, *b);
    return 0;

}
int
main (int argc, char *argv[])
{
/*    char *data = NULL;*/
/*    data = malloc(2*sizeof(char));*/
/*    load(data);*/
/*    printf("primary : one : %c\n", data[0]);*/
/*    fork();*/
/*    printf("one: %c\n", data[0]);*/
     char * a = malloc(1);
     char * b = malloc(1);
     ici(a, b);
    return 0;
}