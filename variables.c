#include "shell.h"

// A global variable to store the last exit status
int last_status = 0;

/**
   function that to allocate variable
   find the positin of the variable
   @str- a pointer to a string
   @var-a pointer to a variable
   @val
 */

// A function to replace a variable with its value in a string
char *replace_var(char *str, char *var, char *val)
{
  
char *pos = strstr(str, var);
if (pos == NULL) {
return str;
}
/**
   allocate memory for the new string
   copy the part of the string before the variable

 */
  
char *new_str = malloc(strlen(str) - strlen(var) + strlen(val) + 1);
if (new_str == NULL) {
perror("malloc");
return str;
}

strncpy(new_str, str, pos - str);

strcat(new_str, val);
strcat(new_str, pos + strlen(var));

  
free(str);
return new_str;
}

/**
   create a function that handle variables replacement
   replace the $? variable with the last exit status
 */


char *handle_vars(char *str)
{
  
char status[10];
sprintf(status, "%d", last_status);
str = replace_var(str, "$?", status);

  
char pid[10];
sprintf(pid, "%d", getpid());
str = replace_var(str, "$$", pid);

  
return str;
}
