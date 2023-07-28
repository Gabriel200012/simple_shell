#include "shell.h"

#include "environ.h"


/* Main function */
int main(int argc, char **argv)
{
    /* Ignore the arguments */
    (void)argc;
    (void)argv;

    /* Start the main loop */
    loop();

    /* Exit successfully */
    return (0);
}

/* Main loop function */
void loop(void)
{
    char *line;
    int status;

    do {
        /* Print the prompt */
        printf(PROMPT);

        /* Read a line from stdin */
        line = read_line();

        /* Execute the line */
        status = execute(&line);

        /* Free the line */
        free(line);

    } while (status); /* Repeat until status is zero */
}

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

/* Execute a line function */
int execute(char **line)
{
    pid_t pid;
    int status;
    char **args;
    char *token;
    int i;

    /* Split the line into an array of arguments using strtok_r */
    args = malloc(sizeof(char *) * 64); /* Allocate memory for 64 pointers */
    if (args == NULL) /* Check if allocation was successful */
    {
        perror("malloc");
        exit(1);
    }
    
    token = strtok_r(*line, " \t\r\n\a", line); /* Get the first token */
    i = 0; /* Initialize index for args array */

    while (token != NULL) /* Loop until no more tokens */
    {
        args[i] = token; /* Store the token in args array */
        i++; /* Increment index */
        token = strtok_r(NULL, " \t\r\n\a", line); /* Get the next token */
    }

    args[i] = NULL; /* Terminate args array with NULL */

    /* If the line is empty or a comment, do nothing and return 1 */
    if (args[0] == NULL || args[0][0] == '#')
        return (1);

    /* Fork a child process */
    pid = fork();

    /* Check for errors */
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    /* If child process, execute the program with execve */
    if (pid == 0)
    {
        char **environ; /* Declare a pointer for environment */

        /* Use getenv or get_environ to get the current environment in a portable way */
        environ = get_environ();

        /* Try to execute the program */
        if (execve(args[0], args, environ) == -1)
        {
            /* If failed, print an error and exit */
            perror(args[0]);
            exit(1);
        }
        
        free(environ); /* Free the environment array */
    }

    /* If parent process, wait for the child to finish */
    else
    {
        /* Wait for the child process to terminate */
        if (wait(&status) == -1)
        {
            perror("wait");
            exit(1);
        }

        /* Check the exit status of the child process */
        if (WIFEXITED(status))
        {
            /* If exited normally, return the exit status */
            return (WEXITSTATUS(status));
        }
        else
        {
            /* If exited abnormally, print an error and return 1 */
            fprintf(stderr, "Child process terminated abnormally\n");
            return (1);
        }
        
    }

    free(args); /* Free the args array */
    return(0);
}
