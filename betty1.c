#include "shell.h"

/* Function prototypes */
void loop(void);
char *read_line(void);
int execute(char *line);

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
        status = execute(line);

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
        /* If EOF, exit the loop */
        if (feof(stdin))
        {
            printf("\n");
            exit(0);
        }
        /* Otherwise, print an error and exit */
        perror("getline");
        exit(1);
    }

    /* Return the line */
    return (line);
}

/* Execute a line function */
int execute(char *line)
{
    pid_t pid;
    int status;
    char *args[2];

    /* Split the line into two arguments: the program name and NULL */
    args[0] = strtok(line, " \t\r\n\a");
    args[1] = NULL;

    /* If the line is empty or a comment, do nothing */
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
        /* Use the current environment for execve */
        extern char **environ;

        /* Try to execute the program */
        if (execve(args[0], args, environ) == -1)
        {
            /* If failed, print an error and exit */
            perror(args[0]);
            exit(1);
        }
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

}
