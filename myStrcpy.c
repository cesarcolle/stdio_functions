#include <stdio.h>
#include <stdlib.h>

/*
* *author : @CésarCollé
* copy src to dest parameter
*/



char *myStrcpy(char *dest, const char *src){
	char *p = dest;
	for(;*src!='\0'; src++, dest++){
	*dest=*src;
	}

return p;
}
