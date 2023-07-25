#include "shell.h"

/**
   main-handle comments
   @str

 */


char *remove_comments(char *str) {
  
char *pos = strchr(str, '#');

  
if (pos == NULL) {
return str;
}

  
char *new_str = malloc(pos - str + 1);
if (new_str == NULL) {
perror("malloc");
return str;
}

  
strncpy(new_str, str, pos - str);

  
new_str[pos - str] = '\0';

  
free(str);
return new_str;
}
