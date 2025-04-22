#include "main.h"

/**
 * main - Doorway to the simple shell program
 *
 * Description:
 * This function provides an infinite loop that acts as a command-line
 * interface for the user. The function reads commands from standard input,
 * removes whitespace if needed, and passes the input to '_fork' for execution.
 * Finally, the program exits when EOF (Ctrl+D) is encountered
 *
 * Return:
 * - The exit status of the last executed command
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *argv[64];

	/* Infinite Loop */
	while (1)
	{
		 /* Display prompt */
		if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

		/* Reads user input */
		nread = getline(&line, &len, stdin);
		if (nread == -1) /* EOF (Crtl+D) */
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		/* Remove unnecessary spaces */
		line = trim_spaces(line);
		if (line[0] == '\0')
			continue;

		/*Tokenize input */
		if (tokenize_input(line, argv) == 0)
			continue;

		/* Handle exit and env */
		if (handle_builtins(line, argv))
			continue;

		/* Execute command externally */
		_fork(argv);
	}

	free(line);
	return (0);
}
