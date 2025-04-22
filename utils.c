#include "main.h"

/**
 * trim_spaces - Removes leading and trailing spaces from a string
 * @line: The input string
 * Return: A pointer to the trimmed string
 */
char *trim_spaces(char *line)
{
	char *end;

	/* Skip leading spaces */
	while (*line == ' ' || *line == '\t' || *line == '\n')
		line++;

	if (*line == '\0')
		return (line);

	/* Move to the end of the string */
	end = line + strlen(line) - 1;

	/* Skip trailing spaces */
	while (end > line && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	/* Null-terminate the string after the last non-space */
	*(end + 1) = '\0';

	return (line);
}

/**
 * tokenize_input - Splits the input line into tokens
 * @line: The input string to tokenize
 * @argv: Array to store the tokens
 * Return: The number of tokens found
 */

int tokenize_input(char *line, char **argv)
{
	int count = 0;
	char *token;

	token = strtok(line, " \t\n");
	while (token != NULL && count < 63)
	{
		argv[count++] = token;
		token = strtok(NULL, " \t\n");
	}
	argv[count] = NULL; /* NULL -terminate the array */

	return (count);
}
