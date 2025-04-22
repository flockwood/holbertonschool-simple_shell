#include "main.h"

/**
 * _fork - Forks a child process to run a command
 * @argv: Array of command and its arguments
 * Return: Exit status of the command
 */

int _fork(char **argv)
{
	pid_t pid;
	int status;
	char *full_path;

	/* check if the command is an absolute or relative path */
	if (access(argv[0], X_OK) == 0)
	{
		full_path = argv[0];
	}
	else
	{
		full_path = find_command_in_path(argv[0]);
		if (!full_path)
		{
			write(STDERR_FILENO, argv[0], strlen(argv[0]));
			write(STDERR_FILENO, ": command not found\n", 21);
			return (127);
		}
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(full_path != argv[0] ? full_path : NULL);
		return (-1);
	}
	else if (pid == 0)
	{
		/* In child */

		/* DEBUG */
		write(STDOUT_FILENO, "[DEBUG] full_path: ", 19);
		write(STDOUT_FILENO, full_path, strlen(full_path));
		write(STDOUT_FILENO, "\n", 1);
		/* END DEBUG */

		if (execve(full_path, argv, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		/* In parent */
		waitpid(pid, &status, 0);
	}

	if (full_path != argv[0])
		free(full_path);

	if (WIFEXITED(status))
		return WEXITSTATUS(status);

	return (-1);

}
