#include "shell.h"

int execute(char **line)
{
    pid_t pid;
    int status;
    char *args[2];

    /* Split the line into two arguments: the program name and NULL */
    args[0] = strtok(*line, " \t\r\n\a");
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
