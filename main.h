#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

/* Global variable */
extern char **environ;

/* Function prototypes */
int tokenize_input(char *line, char **argv);
char *get_path_env(void);
char *find_command_in_path(char *command);
void print_env(void);
void handle_exit(char *line, int status);
int handle_builtins(char *line, char **argv, int status);
int _fork(char **argv);
char *trim_spaces(char *line);
char *get_full_path(char *dir, char *command);

#endif /* MAIN_H */
