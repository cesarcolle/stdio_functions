#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
* Parsing file will provide some functions usefull to parse string.
*
* author : @CésarCollé
* Wed 18 May 2016 03:57:15 PM CEST 
* version : 1.0
**/


/**
* Split a string with delimiter given.
* @a_delim : the delimiter assume is just a char.
* @s_str : the string being process
**/
char **
str_split (char *a_str, const char a_delim, int mode)
{
  char **result = 0;
  size_t count = 0;
  char *tmp = a_str;
  char *last_comma = 0;
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
  count += last_comma < (a_str + strlen (a_str) - 1);

  /* Add space for terminating null string so caller
     knows where the list of returned strings ends. */
  count++;

  result = malloc (sizeof (char *) * count + (mode) ? 1 : 0);

  if (result)
    {
      size_t idx = 0;
      char *token = strtok (a_str, delim);

      while (token)
	{
	  assert (idx < count);
	  *(result + idx++) = strdup (token);
	  token = strtok (0, delim);
	}
      assert (idx == count - 1);
      *(result + idx) = 0;
    }
  if (mode)
    *(result + count) = NULL;
  return result;
}
