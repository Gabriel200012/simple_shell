#include "shell.h"

/* Function prototypes */
void loop(void);
char *read_line(void);
int execute(char *line);
char *find_path(char *command); //added this prototype
int check_exit(char *line); //added this prototype

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


/** Split a line function
 *  @line- get token from line
 *  return line
 */
char **split_line(char *line)
{
int bufsize = BUFSIZE;
int position = 0;
char **tokens = malloc(bufsize * sizeof(char *));
char *token;

   
if (!tokens)
{
perror("malloc");
exit(1);
}

    
token = strtok(line, DELIM);

   
while (token != NULL)
{
        
tokens[position] = token;
position++;

if (position >= bufsize)
{
bufsize += BUFSIZE;
tokens = realloc(tokens, bufsize * sizeof(char *));
            
if (!tokens)
{
perror("realloc");
exit(1);
}
}
token = strtok(NULL, DELIM);
}

tokens[position] = NULL;

return (tokens);
}


/** Find path function
 *  @command- pointer to a command 
 */ //added this function
char *find_path(char *command)
{
char **dirs; 
char full_path[BUFSIZE]; //changed to an array instead of a pointer
int i; 

    
dirs = split_line(getenv("PATH")); 

for (i = 0; dirs[i] != NULL; i++)
{
snprintf(full_path, BUFSIZE, "%s/%s", dirs[i], command);

if (access(full_path, X_OK) == 0)
{
free(dirs);
return (strdup(full_path)); 
}
}
free(dirs);
return NULL;
}

/** Check exit function - check if the line is "exit" or "exit status"
* @line - a pointer to a line
* Return 0 if exit is found, otherwise return 1 
*/ //added this function

int check_exit(char *line)
{
char **args;

args = split_line(line);

if (strcmp(args[0], "exit") == 0) 
{
if (args[1] == NULL) 
{
free(args);
exit(0);
}
else 
{
int status = atoi(args[1]);
free(args);
exit(status);
}
}

free(args); 
return (1);
}

int execute_env(char **args)
{
if (strcmp(args[0], "setenv") == 0)
{
if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
{
            
fprintf(stderr, "setenv: usage: setenv name value [overwrite]\n");
return -1;
}
else
{
int overwrite = atoi(args[3]);
return setenv(args[1], args[2], overwrite);
}
}
else if (strcmp(args[0], "unsetenv") == 0)
{
if (args[1] == NULL || args[2] != NULL)
{
fprintf(stderr, "unsetenv: usage: unsetenv name\n");
return -1;
}
else
{
         
return unsetenv(args[1]);
}
}
else
{
return -1;
}
}



/** Main -  Execute a line function
 *  @line - a pointer to a line
 *  Return the exit status of the child process
 */

/* A function that executes a line */
int execute(char *line)
{
    char **args;
    char *path;

    args = split_line(line);

    /* Check if the first argument is a builtin command */
    if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "env") == 0 ||
        strcmp(args[0], "setenv") == 0 || strcmp(args[0], "unsetenv") == 0)
    {
        /* Execute the builtin command and return its result */
        return execute_builtin(args);
    }

    /* Find the path of the command */
    path = find_path(args[0]);

    /* Check if the path is valid */
    if (path == NULL)
    {
        /* Print an error message and return -1 */
        fprintf(stderr, "%s: command not found\n", args[0]);
        return -1;
    }

    /* Execute the command with the given path and arguments */
    return execute_command(path, args);
}

