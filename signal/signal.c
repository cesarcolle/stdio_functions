#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/**
* SIG_IGN --> signal ignoré
* SIG_DFL --> action par défault
*
**/

void catch_signal(int sig){
    printf("signal : %d\n", sig); 
}


void init_signal(){
    void (*ptr_fct)(int);
    void (*ptr_fct1)(int);
    ptr_fct1 = signal(SIGSEGV, SIG_IGN);
    ptr_fct = signal(SIGINT, SIG_IGN);
    signal(SIGINT, catch_signal);
    
    sleep(15);
    
    signal(SIGINT, ptr_fct);
    signal(SIGSEGV, ptr_fct1);
    
    
    // using sigaction !
    
    struct sigaction tmp;
    
    sigaction
    
    

}




