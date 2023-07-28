#include <stdlib.h>
#include <string.h>

/* Get the current environment as an array of strings */
char **get_environ(void)
{
    char **environ; /* Declare a pointer for environment */
    char *var; /* Declare a pointer for each variable */
    int i, j, len; /* Declare variables for indexes and lengths */

    /* Allocate memory for 64 pointers */
    environ = malloc(sizeof(char *) * 64);
    if (environ == NULL) /* Check if allocation was successful */
    {
        perror("malloc");
        exit(1);
    }

    i = 0; /* Initialize index for environ array */

    /* Loop through all the possible environment variables */
    for (j = 0; j < 64; j++)
    {
        /* Use getenv to get the value of each variable */
        var = getenv("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_");

        /* If the variable exists and has a value */
        if (var != NULL && var[0] != '\0')
        {
            /* Get the length of the variable name and value */
            len = strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_") + strlen(var) + 1;

            /* Allocate memory for the variable name, equal sign and value */
            environ[i] = malloc(sizeof(char) * (len + 1));
            if (environ[i] == NULL) /* Check if allocation was successful */
            {
                perror("malloc");
                exit(1);
            }

            /* Copy the variable name, equal sign and value to environ array */
            strcpy(environ[i], "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_");
            strcat(environ[i], "=");
            strcat(environ[i], var);

            i++; /* Increment index */
        }
    }

    environ[i] = NULL; /* Terminate environ array with NULL */

    return (environ); /* Return the environment array */
}
