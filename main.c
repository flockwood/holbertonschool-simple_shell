#include "main.h"

/**
 * main - Entry point for the simple shell program
 *
 * Description:
 * This function implements a basic UNIX command-line interpreter.
 * It displays a prompt (only in interactive mode), reads input from the user,
 * trims any extra whitespace, tokenizes the input, checks for built-in commands,
 * and if not a built-in, it forks a child process to execute the command.
 * The program exits cleanly when it receives EOF (Ctrl+D).
 *
 * Return: The exit status of the last executed command
 */
int main(void)
{
	char *line = NULL;
	char *trimmed_line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[64];

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

		/* Remove trailing newline from getline */
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Trim whitespace without altering original pointer */
		trimmed_line = trim_spaces(line);
		if (*trimmed_line == '\0')
			continue;

		/* Tokenize command */
		if (tokenize_input(trimmed_line, argv) == 0)
			continue;

		/* Check for built-in commands */
		if (handle_builtins(trimmed_line, argv))
			continue;

		/* Fork and execute */
		_fork(argv);
	}

	free(line);
	return (0);
}

