#include "main.h"

/**
 * buscarCmd - Busca si el comando existe directamente o en el PATH
 * @cmd: Comando que escribió el usuario
 * Return: Ruta al comando si se encuentra, NULL si no
 */

char *buscarCmd(char *cmd)
{
char *full_path;

if (access(cmd, X_OK) == 0)
return (cmd);

full_path = find_command_in_path(cmd);

if (!full_path)
{
return (NULL);
}

return (full_path);
}
/**
 * obtener_ruta_cmd - decide la ruta del comando a ejecutar
 * @argv: argumentos del comando
 * Return: ruta del ejecutable o NULL si no se encuentra
 */

char *obtener_ruta_cmd(char **argv)
{
char *full_path = NULL;

if (strchr(argv[0], '/'))
{
if (access(argv[0], X_OK) == 0)
return (argv[0]);
else
{
fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
return (NULL);
}
}
else
{
full_path = buscarCmd(argv[0]);
if (!full_path)
{
fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
return (NULL);
}
return (full_path);
}
return (NULL);
}

/**
 * _fork - Ejecuta un comando usando fork y execve
 * @argv: comando y sus argumentos
 * Return: codigo de salida
 */
int _fork(char **argv)
{
pid_t pid;
int status;
char *full_path;

full_path = obtener_ruta_cmd(argv);
if (!full_path)
return (127);

pid = fork();
if (pid == -1)
{
perror("fork");
if (full_path != argv[0])
free(full_path);
return (-1);
}
else if (pid == 0)
{
if (execve(full_path, argv, environ) == -1)
{
perror("execve");
exit(1);
}
}
else
{
waitpid(pid, &status, 0);
}

if (full_path != argv[0])
free(full_path);

if (WIFEXITED(status))
return (WEXITSTATUS(status));

return (-1);
}
