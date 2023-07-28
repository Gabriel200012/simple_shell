#include "shell.h"

/**
   create the main functiom
   @argc-
   @argv-
   loop the main function and print and prompt
 */


int main(int argc, char **argv)
{
(void)argc;
(void)argv;

loop();

    
return (0);
}


void loop(void)
{
char *line;
int status;

do
{
        /* Print the prompt */
printf(PROMPT);

        /* Read a line from stdin */
 line = read_line();

        /* Execute the line */
 status = execute(&line);

        /* Free the line */
free(line);
}
while (status); /* Repeat until status is zero */
}
