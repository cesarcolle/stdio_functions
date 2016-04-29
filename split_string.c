/**
* Warning : this is not a POSIX function.
* POSIX function unable to allocate memory dynamically.
*
*author : @CésarCollé
*
*Fri 29 Apr 2016 05:13:32 PM CEST 
*
*
*version: 1.0
*
*/



/**
* str_split funciton will split the string @a_str with the @a_delim
* usefull to execute execv() posix function. 
* see the use in the @shell part of my gitHub !
* set @null to 0 il you don't want NULL at the end of the array.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char** str_split(char* a_str, const char a_delim, char null)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count + (null)?0:1);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    if (null){ *(result + count) = NULL;}
    return result;
}
/*
int
main (int argc, char *argv[])
{
    char tab[50] = "this is an example";
    char ** res = str_split(tab, ' ', 0);
    
    while (*res){
        printf("%s#", *res);
        res++;
    
    } 
    printf("\n");  
    return 0;
}
*/





