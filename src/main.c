#include <stdio.h>

#include "../include/shell.h"

shell_state_t g_shell_state = { .running = 1 };

const builtin_command_t g_builtin_commands[] = {
  {"cd",   lsh_cd,   "Change directory"},
  {"pwd",  lsh_pwd,  "Print current working directory"},
  {"help", lsh_help, "Show this help message"},
  {"exit", lsh_exit, "Exit the shell"}
};

const size_t g_builtin_count = sizeof(g_builtin_commands) / sizeof(builtin_command_t);

void lsh_loop(void) {
  while (g_shell_state.running) {
    printf(LSH_PROMPT);
    fflush(stdout);
    
    char *line = lsh_read_line();
    if (line == NULL) {
      printf("\n");
      break;
    }

    char **args = lsh_split_line(line);
    if (args != NULL && args[0] != NULL) {
      int status = lsh_execute(args);
      if (status == LSH_EXIT) {
        g_shell_state.running = 0;
      }
    }

    free(line);
    lsh_free_tokens(args);
  }
}

int main(void) {
  printf("LSH Shell v1.0 - Simple Shell Implementation\n");
  printf("Type 'help' for available commands.\n\n");

  lsh_setup_signals();
  lsh_loop();

  printf("\nGoodbye!\n");
  return EXIT_SUCCESS;
}
