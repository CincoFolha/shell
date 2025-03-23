#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void lsh_loop(void);
char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_execute(char **args);

int main(int argc, char **argv) {
  lsh_loop();
  return EXIT_SUCCESS;
}

void lsh_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  } while (status);
}

char *lsh_read_line(void) {
  return (char *) malloc(16 * sizeof(char));
}

char **lsh_split_line(char *line) {
  char **args = (char **) malloc(2 * sizeof(char *));
  args[0] = line;
  return args;
}

int lsh_execute(char **args) {
  args[0] = NULL;
  return 1;
}
