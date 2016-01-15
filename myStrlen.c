#include <stdio.h>
#include <stdlib.h>
/*
*return length of given char *
**author : @CésarCollé
*/

int myStrlen(const char* str){
	int res=0;
	while(*(str++))res++;
return res;
}

