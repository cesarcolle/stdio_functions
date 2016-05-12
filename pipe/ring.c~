
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h> 

#define N 5

void close_pipe(int tab[2]){
    close(tab[0]);
    close(tab[1]);
}

void ring(){   
    
    int i = 0;
    int pid = getpid();
    
    while ( i < N && pid != 0){
        pid = fork(); 
        i++;  
    }
    if (pid ==0){
        printf("fils : %d\n", i);
    }
    else{
        for (i = 0; i < N; i += 1)
        {
            wait(NULL);
        }
    }
    
    

}

int
main (int argc, char *argv[])
{
    ring();
    return 0;
}
