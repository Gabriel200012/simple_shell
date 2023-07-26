#include "shell.h"

/**
   A struct to store an alias
   a global variable to store the head of the alias
   
 */

typedef struct alias
{
char *name; 
char *value; 
struct alias *next; 
}
alias_t;


alias_t *alias_head = NULL;

/**
   To allocate memory for the new alias
 */
void add_alias(char *name, char *value)
{
alias_t *new_alias = malloc(sizeof(alias_t));
if (new_alias == NULL) {
perror("malloc");
return;
}

new_alias->name = strdup(name);
new_alias->value = strdup(value);
if (new_alias->name == NULL || new_alias->value == NULL) {
perror("strdup");
free(new_alias);
return;
}

  // Insert the new alias at the head of the list
new_alias->next = alias_head;
alias_head = new_alias;
}

/**
   A function to find alias by name and return its value
   loop through the list of aliases
 */


char *find_alias(char *name)
{
for (alias_t *curr = alias_head; curr != NULL; curr = curr->next)
{
if (strcmp(curr->name, name) == 0) {
return curr->value;
}
}

return NULL;
}

/**
   A function to print all aliases or a specific one
 */

void print_alias(char **args)
{
if (args[1] == NULL) {
for (alias_t *curr = alias_head; curr != NULL; curr = curr->next)
{
printf("%s='%s'\n", curr->name, curr->value);
}
}
else
{
for (int i = 1; args[i] != NULL; i++)
{
      
char *value = find_alias(args[i]);
if (value == NULL)
{
fprintf(stderr, "alias: %s: not found\n", args[i]);
}
else
{
       
printf("%s='%s'\n", args[i], value);
}
}
}
}

/**
   A function to parse an argument into a name and a value for an alias
 */

int parse_alias(char *arg, char **name, char **value)
{
char *equal = strchr(arg, '=');
if (equal == NULL)
{
return -1;
}
*equal = '\0';
*name = arg;
*value = equal + 1;
return 0;
}

/**
   A function to handle the alias builtin command 
 */

void handle_alias(char **args)
{
  
if (args[1] == NULL) {
print_alias(args);
return;
}

for (int i = 1; args[i] != NULL; i++) {
   
char *name, *value;
int result = parse_alias(args[i], &name, &value);

    
if (result == -1)
{
fprintf(stderr, "alias: %s: invalid alias definition\n", args[i]);
continue;
}
add_alias(name, value);
}
}
