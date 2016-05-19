#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/token.h"
#include "../include/station.h"
#define LENGTH_MSG 50
//#define OUT(N) N"="## #LENGTH_MSG

void change(struct token * ptr_token, int id){
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


void reception_(struct token * ptr_token, int id){
    char cmd[LENGTH_MSG];
    memset(cmd, 0, LENGTH_MSG-1);
    FILE * fout;
      switch(ptr_token->status){
        case FREE:
            fprintf(stderr, "la station doit-elle envoyer un message? yes / no\n");
            fout = fopen("/dev/tty", "a+");
            fscanf(fout, "%s", cmd);
            fclose(fout);  
            
            if (!strcmp(cmd, "yes")){
                ptr_token->status = BUSY;
                change(ptr_token, id);
            }
        break;
        
        case ACK:
            if (ptr_token->expediteur == id){
                fprintf(stderr, "station %d a reçu l'accusé !\n", id);
                ptr_token->status = FREE;
            }
             break;
        
        case BUSY:
            if (ptr_token->recepteur == id){
                fprintf(stderr, " station %d a bien reçu le paquet %s! envoie de l'accusé\n", id, ptr_token->msg);
                ptr_token->status = ACK;
            }
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
      struct token  test = { BUSY, id,4, "blabla"};
      write (1, &test, SIZE_TOKEN);
    }
    
  struct token reception;  
  while (1)
    {
      count = read (0, &reception, SIZE_TOKEN);
      fprintf(stderr, "station : %d recoit : %s de %d\n", id, reception.msg, reception.expediteur);
      reception_(&reception, id);
        sleep (1);
        write (1, &reception, count);
    }
  return 0;
}