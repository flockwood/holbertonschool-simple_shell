#include "main.h"

/**
 * readNclean - lee y limpia la entrada del usuario
 * @line: puntero a la linea leida
 * @len: puntero al tamano del buffer
 * Return: lineas sin espacios extras o NULL
 */

char *readNclean(char **line, size_t *len)
{
ssize_t nread;
char *trimmed_line;

nread = getline(line, len, stdin);
if (nread == -1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n", 1);
return (NULL);
}

if (nread > 0 && (*line)[nread - 1] == '\n')
(*line)[nread - 1] = '\0';

trimmed_line = trim_spaces(*line);

return (trimmed_line);
}

/**
 * main - Entry point for the simple shell
 *
 * Return: Exit status of the last executed command
 */

int main(void)
{
char *line = NULL;
char *trimmed_line = NULL;
size_t len = 0;
ssize_t nread;
char *argv[64];
int status = 0;

while (1)
{
/* Show prompt only if in interactive mode */
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "[$] ", 2);

/* Read & Clean newlines, white spaces*/
trimmed_line = readNclean(&line, &len);
if (!trimmed_line)
break;

if (*trimmed_line == '\0')
continue;

/* Tokenize input */
if (tokenize_input(trimmed_line, argv) == 0)
continue;

/* Handle built-in commands like exit/env */
if (handle_builtins(trimmed_line, argv))
continue;

/* Execute command and store its exit status */
status = _fork(argv);
}

free(line);
return (status);
}
