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
