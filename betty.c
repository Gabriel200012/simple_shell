#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 1024 // The maximum length of a command line

// A function that displays a prompt and reads a line from the standard input
char *read_line(void) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  // Display a prompt
  printf("$ ");

  // Read a line from stdin using getline
  nread = getline(&line, &len, stdin);

  // Check if getline failed or reached end of file
  if (nread == -1) {
    // If end of file, exit the shell gracefully
    if (feof(stdin)) {
      printf("\n");
      exit(EXIT_SUCCESS);
    }
    // If other error, print an error message and return NULL
    else {
      perror("getline");
      return NULL;
    }
  }

  // Return the pointer to the input line
  return line;
}

// A function that executes a command using execve
int execute_command(char *command) {
  pid_t pid;
  int status;
  char *args[] = {command, NULL}; // Create an array of arguments with only the command name

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execve(command, args, NULL) == -1) {
      perror("execve");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("fork");
  } else {
    // Parent process
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

// A function that loops to read and execute commands
void loop(void) {
  char *line;
  int status;

  do {
    line = read_line(); // Read a line from stdin
    if (line != NULL && strlen(line) > 1) { // Check if the line is not empty or only a newline
      line[strlen(line) - 1] = '\0'; // Remove the trailing newline from the line
      status = execute_command(line); // Execute the command in the line
      free(line); // Free the memory allocated by getline
    }
  } while (status);
}

// The main function
int main(int argc, char **argv) {
  
  // Run command loop.
  loop();

  return EXIT_SUCCESS;
}
