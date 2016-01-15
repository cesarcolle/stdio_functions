#include <stdio.h>
#include <stdlib.h>

/*
	recherche si le motif ss[] est repere dans la string s[]
	on compare dans s[] a partir de l'indice i
*/
int issubstr(char s[], char ss[], int i){
	int j = 0;
	while(ss[j] != '\0' && s[i] == ss[j]){
		i++;
		j++;
	}
	if(ss[j] == '\0')
		return 1;
	return 0;
}
