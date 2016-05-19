#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "token.h"
#include "station.h"
#define LENGTH_MSG 50
#define OUT(N) "##N = MAX_MACHINE "

void change(struct token * ptr_token, int id){
    char c;
    char cmd[LENGTH_MSG];
    int i =0;
    int state = 1;
    fprintf(stderr, "quelle station ?"OUT(MAX_MACHINE));

    ptr_token->recepteur =  atoi(cmd);
    ptr_token->expediteur = id;
    

}


void reception_(struct token * ptr_token, int id){
    char cmd[LENGTH_MSG];
    int destinataire;
    memset(cmd, 0, LENGTH_MSG-1);
    FILE * fout;
    FILE * fin;
      switch(ptr_token->status){
        case FREE:
            fprintf(stderr, "la station envoie un message? yes / no\n");
            fout = freopen("/dev/tty", "r", stdout);
            //fscanf(fout, "%s", cmd);
            scanf("%s", cmd);
            fclose(fout);  
            
            if (!strcmp(cmd, "yes")){
                fprintf(stderr, "you say yes !\n");
            }
        break;
        
        case ACK:
             break;
        
        case BUSY:
            break;
        
        DEFAULT
      }

}


int
main (int argc, char *argv[])
{
  int count;
  char buff[LENGTH_MSG];
  int id = atoi(argv[1]);
  memset (buff, 0, LENGTH_MSG - 1);

  //Test d'envoie
  if (!strcmp (argv[1], "0"))
    {
      fprintf (stderr, "ecriture\n");
      struct token  test = { FREE, 0,4, "blabla"};
      write (1, &test, SIZE_TOKEN);
    }
    
  struct token reception;  
  while (1)
    {
      count = read (0, &reception, SIZE_TOKEN);
      fprintf (stderr, "fils num %s a recu : %s \n", argv[1], reception.msg);
      if (reception.recepteur == id){
            fprintf(stderr, "package reçu sur fils : %d\n", id);
            reception_(&reception, id);
        }

    sleep (1);
    write (1, &reception, count);
    }
  return 0;
}
