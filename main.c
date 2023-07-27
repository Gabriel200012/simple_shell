
#include "shell.h"

/**
   Main- entry null
   create a function that read line
 */
char *read_line(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;

nread = getline(&line, &len, stdin);
if (nread == -1)
{  
free(line);
exit(EXIT_SUCCESS);
}
return line;
}

/**
   main: entry
   create a function that splits a line into an arrays of argument
 */

char **split_line(char *line) {
char **args = malloc(MAX_ARGS * sizeof(char *));
char *token;
int index = 0;

token = strtok(line, " \t\r\n\a");
while (token != NULL) {
args[index] = token;
index++;
token = strtok(NULL, " \t\r\n\a");
}
args[index] = NULL;
return args;
}

int execute(char **args)
{
pid_t pid;
int status;

if (args[0] == NULL)
{
   
return 1;
}

pid = fork();
if (pid == 0)
{
    
if (execve(args[0], args, environ) == -1)
{
perror(args[0]);
}
exit(EXIT_FAILURE);
}
else if (pid < 0)
{
   
perror("fork");
}
else
{
do
{
waitpid(pid, &status, WUNTRACED);
}
while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

return 1;
}


void loop(void)
{
char *line;
char **args;
int status;

do
{
printf("> ");
line = read_line();
args = split_line(line);
status = execute(args);

free(line);
free(args);
} while (status);
}


int main(void)
{
  
loop();

  

return EXIT_SUCCESS;
}
