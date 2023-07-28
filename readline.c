#include "shell.h"

/* Read a line from stdin function */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    /* Use getline to read a line from stdin */
    nread = getline(&line, &bufsize, stdin);

    /* Check for errors or EOF */
    if (nread == -1)
    {
        /* If EOF, return NULL */
        if (feof(stdin))
        {
            printf("\n");
            return (NULL);
        }
        /* Otherwise, print an error and exit */
        perror("getline");
        exit(1);
    }

    /* Return the line */
    return (line);
}
