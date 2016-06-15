#ifndef ARRAY_LIST
#define ARRAY_LIST

typedef struct array_list{
    void * argument;
    void (*display)(struct array_list *);
    void (*add)(struct array_list **);
    struct array_list *next;
} array;

#endif
