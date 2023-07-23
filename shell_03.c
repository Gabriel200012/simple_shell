#include "shell.h"

/* Function prototypes */
void loop(void);
char *read_line(void);
int execute(char *line);
char *find_path(char *command); //added this prototype

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
 *  

 */ //added this function
char *find_path(char *command)
{
char *path; 
char **dirs; 
char *full_path; 
int i; 

    
path = getenv("PATH");
if (path == NULL)
{
perror("getenv");
exit(1);
}

    //split the path into directories using : as delimiter
dirs = split_line(path);

    //allocate memory for full_path with enough space for / and \0
full_path = malloc(strlen(command) + 2);
if (full_path == NULL)
{
perror("malloc");
exit(1);
}

    //loop through the directories and check if command exists in any of them
for (i = 0; dirs[i] != NULL; i++)
{
        //copy the directory to full_path
strcpy(full_path, dirs[i]);
        //append a / to full_path
strcat(full_path, "/");
        //append the command to full_path
strcat(full_path, command);

        //check if full_path is an executable file using access function
if (access(full_path, X_OK) == 0)
{
            //found the command, free dirs and return full_path
free(dirs);
return full_path;
}
}

    //did not find the command, free dirs and full_path and return NULL
free(dirs);
free(full_path);
return NULL;
}



/** Main -  Execute a line function
 *  @line - a pointer to a line
 *  Return the exit status of the child process
 */
int execute(char *line)
{
char **args;
char *path; 

args = split_line(line); 


int num = atoi(args[1]); //convert char to int
printf("Int version of 1st arg: %d\n", num); //print it for testing


path = find_path(args[0]);
if (path == NULL)
{
    //did not find the command, print error and exit
fprintf(stderr, "%s: command not found\n", args[0]);
exit(1);
}
else
{
    //found the command, replace args[0] with path
free(args[0]);
args[0] = path;
}

//remove this part to avoid forking
//pid_t pid;
//int status;

//pid = fork();

//if (pid == -1)
//{
//perror("fork");
//exit(1);
//}


//if (pid == 0)
//{
 
if (execve(args[0], args, NULL) == -1)
{
     
perror(args[0]);
exit(1);
}
//}


//else
//{
 
//if (wait(&status) == -1)
//{
//perror("wait");
//exit(1);
//}

//return (WEXITSTATUS(status));
//}
}
