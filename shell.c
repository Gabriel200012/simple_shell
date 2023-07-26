
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *command;
    char *path;
    size_t bufsize = 32;
    ssize_t nread;

    while (1) {
        printf("$ ");
        command = (char *)malloc(bufsize * sizeof(char));
        if (command == NULL) {
            perror("malloc error");
            exit(EXIT_FAILURE);
        }

        nread = getline(&command, &bufsize, stdin); // Read user input

        if (nread == -1) {  // Handle EOF (Ctrl+D)
            printf("\n");
            break;
        }
        if (nread > 0 && command[nread-1] == '\n') {
            command[nread-1] = '\0';  // Remove trailing newline
        }

        path = getenv("PATH"); // Get the PATH variable
        char *token, *prev, *path_copy;
        path_copy = strdup(path);

        token = strtok_r(path_copy, ":", &prev);
        while (token != NULL) { // Iterate over PATH directories
            char *command_path = (char *)malloc((strlen(token) + strlen(command) + 2) * sizeof(char)); // Allocate memory for the path to the executable
            if (command_path == NULL) {
                perror("malloc error");
                exit(EXIT_FAILURE);
            }

            sprintf(command_path, "%s/%s", token, command); // Construct the path to the executable
            if (access(command_path, X_OK) == 0) { // Check if the executable exists and is executable
                pid_t pid = fork();
                if (pid < 0) {
                    perror("fork error");
                    exit(EXIT_FAILURE);
                }
                else if (pid == 0) { // Child process
                    execve(command_path, NULL, environ); // Execute the command
                    perror("execve error");
                    free(command_path);
                    exit(EXIT_FAILURE);
                }
                else { // Parent process
                    wait(NULL); // Wait for the child process to complete
                    free(command_path);
                    break; // Stop iterating over PATH directories once the executable is found and executed
                }
            }

            free(command_path);
            token = strtok_r(NULL, ":", &prev);
        }

        free(command);
        free(path_copy);
    }

    return 0;
}
