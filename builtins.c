#include "main.h"

/**
 * print_env - Prints the environment variables
 */

void print_env(void)
{
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}

/**
 * handle_exit - Frees memory and exits the shell
 * @line: The input line to free before exiting
 */

void handle_exit(char *line)
{
	free(line);
	exit(0);
}

/**
 * handle_builtins - Checks and handles built-in commands
 * @line: Raw input line (for cleanup on exit)
 * @argv: Tokenized input
 * Return: 1 if a builtin command was handled, 0 otherwise
 */

int handle_builtins(char *line, char **argv)
{
	if (strcmp(argv[0], "exit") == 0)
	{
		handle_exit(line);
		return (1);
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	return (0);
}
