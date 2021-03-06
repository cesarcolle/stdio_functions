#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
* BUT : créé une chaine de structure chainé, elles seront reliés chacunes par un pointeur qui pointera sur une autre structure,
* STRUCT 1.NEXT ----> STRUCT 2 ;  STRUCT 2.NEXT -----> STRUCT 3, ect ....
* permet une allocation dynamique moins couteuse en réallocation.
* peut etre associé a une pile / file 
 */

typedef struct caractere
{
  char caract;
  int occurrence;
  struct caractere *next;
} *chaine;

chaine Schaine;


void
occurrences (int c, chaine * Schaine)
{
  while (*Schaine != NULL)
    {
      if ((*Schaine)->caract == c)
	{
	  (*Schaine)->occurrence = (*Schaine)->occurrence + 1;
	  return;
	}
      else
	{
	  Schaine = &(*Schaine)->next;	// la subtilité !

	}
    }
  // allocation
  printf ("allocation struct \n");
  *Schaine = calloc (1, sizeof (struct caractere));
  (*Schaine)->occurrence = 1;
  (*Schaine)->caract = (char) c;
  return;
}

void
Affic (chaine Schaine)
{
  while (Schaine != NULL)
    {
      printf ("MOT = %c occurrence = %d \n", (*Schaine).caract,
	      (*Schaine).occurrence);
      (Schaine) = (*Schaine).next;
    }
  return;
}


void
running_parse (chaine * Schaine)
{
  int c;

  printf ("tape un truc :");

  while ((c = getchar ()) != EOF)
    {
      printf ("\n\n\n");
      printf ("values memory of Schaine in RUNNING : %p \n", Schaine);
      if (c == '\n')
	{
	  Affic (*Schaine);
	  free (*Schaine);
	}
      occurrences (c, Schaine);
    }
  return;
}




int
main (void)
{
  printf ("values memory of Schaine in MAIN : %p \n", &Schaine);
  running_parse (&Schaine);


  free (Schaine);
  return 0;
}
