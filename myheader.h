#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

void execute_command(char *command);
void print_command(char *command);
int main(void);

#endif
