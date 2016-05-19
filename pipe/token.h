
#ifndef TOKEN
#define TOKEN
#include <stdio.h>
#include "ring.h"

#define SIZE_TOKEN sizeof(struct token)

enum STATUS
{ FREE, ACK, BUSY };

struct token
{
    enum STATUS status;
    int expediteur;
    int recepteur;
    char msg[LENGTH_MSG];
};
#endif
