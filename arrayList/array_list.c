#include <stdlib.h>
#include <stdio.h>
#include "array_list.h"

/**
*   add_element on the array_list
*
**/
void add_element(array ** array_list, void * elemt){
} 


struct test {
    int a;
    int b;
};

int main (int argc, char *argv[])
{
    struct test ab = {'a', 'b'};
    void * ptr = &ab;
    struct test * ptr_ = &ab;
    while (ptr != NULL){
        printf("%d\n", ptr);
        if (ptr == ptr_){
            printf("ok\n");
            }
        ptr++;
        ptr_++;
    }
    
    return 0;
}


