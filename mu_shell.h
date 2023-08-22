#ifndef mu
#define mu

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_str(char *str, char end);
void show_prompt (void);
char **tokenize(char **, char *);
char *_getenv(char **, char *);
void check_prog(char **, char *, char **);
void runexec(char **, char **, char *);
int _strlen(char *);

#endif
