#include "shell.h"

/* Function prototypes */
void loop(void);
char *read_line(void);
int execute_line(char *line);

/**
 * main - Entry point of the shell
 * Return: 0 on success, 1 on error
 */
int main(void)
{
    /* Print a welcome message and a joke */
    printf("Welcome to my simple shell!\n");
    printf("What do you call a fish with two knees? A two-knee fish.\n");
    /* Start the main loop */
    loop();
    /* Print a goodbye message */
    printf("Goodbye!\n");
    return (0);
}

/**
 * loop - The main loop of the shell
 */
void loop(void)
{
    char *line;
    int status;
    int count = 0;

    do {
        /* Print the prompt and read a line */
        printf(PROMPT);
        line = read_line();
        if (line == NULL)
            break;
        /* Execute the line and free it */
        status = execute_line(line);
        free(line);
        /* Increment the command count */
        count++;
        /* If the count is a multiple of 5, print a random fact */
        if (count % 5 == 0)
        {
            char *facts[] = {
                "Did you know that the longest word in English is pneumonoultramicroscopicsilicovolcanoconiosis?\n",
                "Did you know that the most common letter in English is E?\n",
                "Did you know that the name of all the continents end with the same letter that they start with?\n",
                "Did you know that the only two animals that can see behind themselves without turning their heads are the rabbit and the parrot?\n",
                "Did you know that dolphins sleep with one eye open?\n"
            };
            int r = rand() % 5;
            printf(facts[r]);
        }
    } while (status);
}

/* The rest of the code is unchanged */
