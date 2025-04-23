#include "main.h"

/**
 * get_full_path - Concatenates directory and command into full path
 * @dir: Directory from PATH (e.g., /bin)
 * @command: Command name (e.g., ls)
 * Return: Full path (e.g., /bin/ls), must be freed by caller
 */
char *get_full_path(char *dir, char *command)
{
char *full_path;
size_t len = strlen(dir) + strlen(command) + 2;
/* +1 for '/' and +1 for '\0' */

full_path = malloc(len);
if (!full_path)
return (NULL);

sprintf(full_path, "%s/%s", dir, command);
return (full_path);
}

/**
 * find_command_in_path - Searches for a command in the PATH
 * @command: The name of the command (e.g., "ls")
 * Return: Full path to command if found, NULL otherwise
 */
char *find_command_in_path(char *command)
{
char *path_env, *path_copy, *token, *full_path;
struct stat st;
int i = 0;

/* Manually find PATH in environ */
while (environ[i])
{
if (strncmp(environ[i], "PATH=", 5) == 0)
{
path_env = environ[i] + 5;
break;
}
i++;
}


if (!path_env)
return (NULL);

path_copy = strdup(path_env);
if (!path_copy)
return (NULL);

token = strtok(path_copy, ":");
while (token)
{
full_path = get_full_path(token, command);
if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
{
free(path_copy);
return (full_path); /* Caller must free */
}
free(full_path);
token = strtok(NULL, ":");
}

free(path_copy);
return (NULL);
}
