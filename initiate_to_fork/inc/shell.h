#ifndef SHELL
#define SHELL

#define MAX 50

int file_exist (char *path);
void reset_path (char *);
int manage_cd (char *, char *);
void new_command (char **, char *);
void shell (char *, char *);

#endif
