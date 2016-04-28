#ifndef ASSERT_H
#define ASSERT_H
static int test_ok = 0;
static int test_false = 0;

#define stringize(s) #s
#define XSTR(s) stringize(s)
#if !defined NDEBUG
#define ERROR(a) \
do { \
if (0 == (a)) { \
fprintf(stderr, \
"\e[1;31m function failed:\e[0;31m %s, " \
"%d at line : \'%s\' function '\%s\'\n\e[0;29m", \
__FILE__, \
__LINE__, \
__FUNCTION__,\
XSTR(a)); \
test_false++;\
} \
else {\
fprintf(stdout,"\e[0;32m function : %s \e[1;36mpassed\n\e[0;29m", __FUNCTION__);\
test_ok++;}\
} while (0)
#endif
#endif
