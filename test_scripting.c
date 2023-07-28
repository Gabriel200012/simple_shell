#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Create a shell script file with some commands
  FILE *fp = fopen("test_scripting.sh", "w");
  fprintf(fp, "#!/bin/sh\n");
  fprintf(fp, "echo \"Hello from test_scripting.sh\"\n");
  fprintf(fp, "gcc -o hello hello.c\n");
  fprintf(fp, "./hello\n");
  fclose(fp);

  // Make the script executable
  system("chmod +x test_scripting.sh");

  // Run the script and get its exit status
  int status = system("./test_scripting.sh");
  printf("The script exited with status %d\n", status);

  return 0;
}
