#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void option_N(){
    int c;
    int nbLigne= 0;
    printf("%d", nbLigne);
    while(( c =getchar() ) != EOF){
	    printf("%c", c);
	    if (c == '\n')
		    printf("%d", nbLigne++);
    }

}
void option_h(){
printf(" taper -E pour mettre des $ a la fin de chaque phrase\n taper -n pour numéroté les lignes !\n");

}

void option_E(){
	int c;
	while( (c = getchar() ) != EOF){
		if ( c == '\n')
			printf("$");
		printf("%c", c);
	}

}


int option_courte(char * p){
	if (strlen(p) <= 1){
		printf("juste un tiret !\n");
		return 0;
	}
	*p++;
	do{
		if ( (('a'<=*p) && (*p<='z')) ){
			if (*p == 'n')
				option_N();
			if (*p == 'e')
				option_E();
		}
		else return 0;
	}while ((*p++) && (*p != '\0') );
return 1;
}

int fin(char* p, char * fin_opt){
	return ( (strcmp("--", p) == 0  ) || ( strcmp(p, fin_opt) == 0 ) );
}

int main(int argc, char** argv){
	int i = 1;
	int pass = 1;
	if (argc < 2){fprintf(stderr, "mettez des opt !\n"); exit(EXIT_FAILURE);}
	char fin_opt[7];
	strcpy(fin_opt, argv[1]);
	do{
		if ((argv[i][0] == '-') && (pass) ){
			if (strlen(argv[i]) <= 1);
			else if (option_courte(argv[i]));
			else printf("ça doit etre long : %s\n", argv[i]);
		}
		else{
			printf("c'est un argument %s\n", argv[i]);
			pass = 0;
		}
	i++;
	if ( (i < argc) && (fin(argv[i], fin_opt) ) )
		pass = 0;
	}while (i < argc );

return 0;
}
