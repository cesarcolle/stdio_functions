#include <stdio.h>
#include <stdlib.h>

/*
*author : @CésarCollé
* Return first rank of given char in the given string.
*/


char* strchr(const char *s, int c){
	while(*s){
		if(*s==c)
			return s;
	s++;
	}
	return NULL;

}


