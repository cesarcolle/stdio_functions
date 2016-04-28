#include "../include/my_cp.h"
#include "../include/my_cp_recc.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>



int main(int argc, char *argv[])
{   
    
    char c;
    if (argc < 2){
    fprintf(stderr, "erreur need 2 arguments \n");
    return 1;
    }
  while ((c = getopt (argc, argv, "r:")) != -1)
    switch (c)
      {
      printf("opt = %c\n", c);
      case 'r':
        printf("R case !\n");
        initialisation(argv[2], argv[3]);
        return 1;
        break;
      default:
        printf("abort\n");
        abort ();
      }
    if (argc > 2){
        return my_cp(argv[1], argv[2]);
    }
    else{
        fprintf(stderr, "not enought argument \n");
    }
    return 1;
}
