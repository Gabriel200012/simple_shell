#include "shell.h"



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
