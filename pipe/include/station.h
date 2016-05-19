#ifndef STATION
#define STATION

#define TERMINAL /dev/out.txt

#define DEFAULT \
    default :\
        fprintf(stderr, "imposible %s\n", __FUNCTION__);\
        exit(0);\
        break;

#endif
