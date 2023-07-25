#include "shell.h"


/**
   Execute a command
   @command

 */

void execute_command(char *command) {

}


void execute_file(char *filename) {
  
FILE *file = fopen(filename, "r");
if (file == NULL) {
perror("fopen");
exit(1);
}

  
char *line = NULL;
size_t len = 0;
ssize_t nread;
while ((nread = getline(&line, &len, file)) != -1) {
    
if (line[nread - 1] == '\n') {
line[nread - 1] = '\0';
}

execute_command(line);
}

free(line);
fclose(file);
}


int main(int argc, char **argv) {
if (argc > 1)
{
    // Execute the commands from the file
execute_file(argv[1]);
    // Exit the shell
exit(0);
}

  // Otherwise, enter interactive mode
  // TODO: implement this mode
}
