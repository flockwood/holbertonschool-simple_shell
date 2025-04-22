#include "main.h"

/**
 * main - Entry point for the simple shell program
 *
 * Description:
 * This function implements a basic UNIX command-line interpreter.
 * It reads input from the user, trims whitespace, tokenizes the input,
 * and handles built-ins or external commands. It returns the exit status
 * of the last executed command, and exits cleanly on EOF.
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
			write(STDOUT_FILENO, "$ ", 2);

		/* Read input from user */
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove trailing newline */
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Trim whitespace without changing original pointer */
		trimmed_line = trim_spaces(line);
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

