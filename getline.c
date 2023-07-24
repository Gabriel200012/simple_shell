#include "shell.h"



/* Function prototypes */
void loop(void);
char *read_line(void);
int execute(char *line);

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

/** Main -  Execute a line function
 *  @line - a pointer to a line
 *  Return the exit status of the child process
 */
int execute(char *line)
{
char *args[2];
pid_t pid;
int status;

args[0] = strtok(line, "\n");
args[1] = NULL;

pid = fork();

if (pid == -1)
{
perror("fork");
exit(1);
}


if (pid == 0)
{
 
if (execve(args[0], args, NULL) == -1)
{
     
perror(args[0]);
exit(1);
}
}


else
{
 
if (wait(&status) == -1)
{
perror("wait");
exit(1);
}

return (WEXITSTATUS(status));
}
}


// return EOF, 0 (not all line was read) or 1 (all the line was read)
int getstring(char **lineptr, size_t *n, int fd) {
  // check for invalid arguments
  if (lineptr == NULL || n == NULL || fd < 0) {
    return -1;
  }

  // initialize static buffer
  static char *buffer = NULL;
  static size_t size = 0;
  static size_t start = 0;
  static size_t end = 0;

  // allocate or reallocate line buffer if needed
  if (*lineptr == NULL || *n == 0) {
    *n = BUFSIZ;
    *lineptr = malloc(*n);
    if (*lineptr == NULL) {
      return -1;
    }
  }

  // initialize line length
  size_t len = 0;

  // loop until newline or EOF is found
  while (1) {
    // check if buffer is empty
    if (start == end) {
      // fill buffer with data from file
      ssize_t bytes_read = read(fd, buffer, size);
      if (bytes_read == -1) {
        // handle error
        return -1;
      }
      if (bytes_read == 0) {
        // handle EOF
        if (len == 0) {
          return -1;
        }
        break;
      }
      // reset buffer indices
      start = 0;
      end = bytes_read;
    }

    // copy character from buffer to line
    (*lineptr)[len] = buffer[start];
    len++;
    start++;

    // check if newline is found
    if ((*lineptr)[len - 1] == '\n') {
      break;
    }

    // check if line buffer is full
    if (len == *n) {
      // reallocate line buffer with double size
      *n *= 2;
      char *temp = realloc(*lineptr, *n);
      if (temp == NULL) {
        // handle error
        return -1;
      }
      *lineptr = temp;
    }
  }

  // null-terminate the line
  (*lineptr)[len] = '\0';

  // return the number of characters read or -1 on error or EOF
  return len;
}
