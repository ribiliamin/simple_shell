#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

void screenprint(const char *string_2print);
void prompt();
void cmdexe(char **argv);
char *get_location(char *cmd1);

#endif
