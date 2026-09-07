#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "../include/shell.h"

static int lsh_execute_builtin(char **args) {
  for (size_t i = 0; i < g_builtin_count; i++) {
    if (strcmp(args[0], g_builtin_commands[i].name) == 0) {
      return g_builtin_commands[i].function(args);
    }
  }
  return LSH_SUCCESS;
}

static int lsh_launch_program(char **args) {
  pid_t pid = fork();

  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      fprintf(stderr, "lsh: command not found: %s\n", args[0]);
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    fprintf(stderr, "lsh: fork failed: %s\n", strerror(errno));
  } else {
    int status;
    do {
      waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return LSH_SUCCESS;
}

int lsh_execute(char **args) {
  if (args == NULL || args[0] == NULL) {
    return LSH_SUCCESS;
  }

  int result = lsh_execute_builtin(args);
  if (result != LSH_SUCCESS) {
    return result;
  }

  for (size_t i = 0; i < g_builtin_count; i++) {
    if (strcmp(args[0], g_builtin_commands[i].name) == 0) {
      return result;
    }
  }

  return lsh_launch_program(args);
}
