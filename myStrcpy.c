#include <stdio.h>
#include <stdlib.h>

/*
* *author : @CésarCollé
* copy src to dest parameter
* Thu 19 May 2016 10:38:17 PM CEST 
* version 1.0
*/

char *myStrcpy(char *dest, const char *src){
	char *p = dest;
	for(;*src!='\0'; src++, dest++){
	*dest=*src;
	}

return p;
}
