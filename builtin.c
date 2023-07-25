
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
int main(int argc, char **argv, char **envp)
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
char full_path[BUFSIZE]; 
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

/** Check cd- function - 
* @directory - a pointer to a line

*A function that changes the current directory of the process
*/

void cd(char *directory)
{
if (directory == NULL)
{
directory = getenv("HOME");
}
else if (strcmp(directory, "-") == 0)
{
directory = getenv("OLDPWD");
}
    
char *oldpwd = getcwd(NULL, 0);
setenv("OLDPWD", oldpwd, 1);
free(oldpwd);
    
if (chdir(directory) == 0)
{
char *pwd = getcwd(NULL, 0);
setenv("PWD", pwd, 1);
free(pwd);
}
    
else
{
perror("cd");
}
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

if (strcmp(args[0], "cd") == 0) 
{
if (args[1] == NULL) 
{
char *home = getenv("HOME"); 
cd(home); 
}
else 
{
cd(args[1]); 
}
 
return (1); 
 
}

else if (strcmp(args[0], "env") == 0) 
{
int i = 0;
while (environ[i]) 
{
printf("%s\n", environ[i]); 
i++;
}
return (1); 
}
}


