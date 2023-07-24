
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


/** Find path function
 *  @command- pointer to a command 
 */ //added this function
char *find_path(char *command)
{
char **dirs; 
char full_path[BUFSIZE]; //changed to an array instead of a pointer
int i; 

    
dirs = split_line(getenv("PATH")); //combined two lines into one

    //loop through the directories and check if command exists in any of them
for (i = 0; dirs[i] != NULL; i++)
{
        //copy the directory and command to full_path using snprintf
snprintf(full_path, BUFSIZE, "%s/%s", dirs[i], command);

        //check if full_path is an executable file using access function
if (access(full_path, X_OK) == 0)
{
            //found the command, free dirs and return full_path as a string
free(dirs);
return (strdup(full_path)); //use strdup to return a copy of full_path
}
}

    //did not find the command, free dirs and return NULL
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

if (strcmp(args[0], "exit") == 0) //compare the first argument with "exit"
{
if (args[1] == NULL) //no second argument, exit with status 0
{
free(args);
exit(0);
}
else //second argument exists, try to convert it to an integer and exit with that status
{
int status = atoi(args[1]);
free(args);
exit(status);
}
}

free(args); //not exit, free args and return 1 to continue looping
return (1);
}



/** Main -  Execute a line function
 *  @line - a pointer to a line
 *  Return the exit status of the child process
 */

extern char **environ; //declare the environ variable

int execute(char *line)
{
    char **args;
    char *path; 

    args = split_line(line); 

    if (strcmp(args[0], "env") == 0) //compare the first argument with "env"
    {
        int i = 0;
        while (environ[i]) //loop through the environ array
        {
            printf("%s\n", environ[i]); //print each string in the form of "variable=value"
            i++;
        }
        free(args); //free the args array
        return (1); //return 1 to continue looping
    }

    if (check_exit(line) == 0) //check if line is exit or exit status and handle it accordingly
        return (0); 

    //rest of the execute function
}
