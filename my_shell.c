#include "shell.h"

/**
 * main - Entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
char *line;
char **args;
int status;

if (argc > 1)
{
fprintf(stderr, "Usage: %s\n", argv[0]);
return (1);
}

do {
printf("$ ");
line = read_line();
args = split_line(line);
status = execute(args);

free(line);
free(args);
} while (status);

return (0);
}
