
#include "shell.h"



/* Function prototypes */
void loop(void);
char *read_line(void);
int execute(char *line);

/** Main function - create the main functions that ignore arguments
 * @argc - void
 * @argv - void
 * Run the main loop and return 0
 */
int main(int argc, char **argv)
{
(void)argc;
(void)argv;
loop();

return (0);
}


/** Main loop- create the main loop function
 *  Repeat unitl EOF or error
 *  print the prompt
 */

void loop(void)
{
char *line;
int status;

do {
 
printf(PROMPT);

line = read_line();

status = execute(line);

free(line);

} while (status);
}

/** read_line- create  a read_line function
 *  errors- check for errors or EOF
 *  return line
 */
char *read_line(void)
{
char *line = NULL;
size_t bufsize = 0;
ssize_t nread;

nread = getline(&line, &bufsize, stdin);

if (nread == -1)
{
       
if (feof(stdin))
{
printf("\n");
exit(0);
}
       
else
{
perror("getline");
exit(1);
}
}

return (line);
}


/* Split a line function */
char **split_line(char *line)
{
int bufsize = BUFSIZE;
int position = 0;
char **tokens = malloc(bufsize * sizeof(char *));
char *token;

    /* Check for allocation error */
if (!tokens)
{
perror("malloc");
exit(1);
}

    /* Get the first token from the line */
token = strtok(line, DELIM);

    /* Loop through the rest of the tokens */
while (token != NULL)
{
        /* Store the token in the array */
tokens[position] = token;
position++;

        /* Check if the array is full and resize if needed */
if (position >= bufsize)
{
bufsize += BUFSIZE;
tokens = realloc(tokens, bufsize * sizeof(char *));
            
            /* Check for allocation error */
 if (!tokens)
 {
 perror("realloc");
 exit(1);
 }
 }

        /* Get the next token from the line */
token = strtok(NULL, DELIM);
}

    /* Terminate the array with a NULL pointer */
tokens[position] = NULL;

    /* Return the array of tokens */
return (tokens);
}





/** Main -  Execute a line function
 *  @line - a pointer to a line
 *  Return the exit status of the child process
 */
int execute(char *line)
{
char *args[2];
pid_t pid;
int status;

args[0] = strtok(line, "\n");
args[1] = NULL;

pid = fork();

if (pid == -1)
{
perror("fork");
exit(1);
}


if (pid == 0)
{
 
if (execve(args[0], args, NULL) == -1)
{
     
perror(args[0]);
exit(1);
}
}


else
{
 
if (wait(&status) == -1)
{
perror("wait");
exit(1);
}

return (WEXITSTATUS(status));
}
}
