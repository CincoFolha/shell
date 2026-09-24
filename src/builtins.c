#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "../include/shell.h"

#define DEFAULT_HOME "/root"

static const char *get_home_dir(void) {
  const char *home = getenv("HOME");
  return (home != NULL && home[0] != '\0') ? home : DEFAULT_HOME;
}

int lsh_cd(char **args) {
  if (args[1] != NULL && args[2] != NULL) {
    fprintf(stderr, "lsh: cd: too many arguments\n");
    return LSH_SUCCESS;
  }

  const char *target_dir = args[1];
  
  if (target_dir == NULL) {
    target_dir = get_home_dir();
  }

  if (chdir(target_dir) != 0) {
    fprintf(stderr, "lsh: cd: cannot change to '%s': %s\n", 
            target_dir, strerror(errno));
  }

  return LSH_SUCCESS;
}

int lsh_pwd(char **args) {
  (void)args;
  
  char *cwd = getcwd(NULL, 0);
  
  if (cwd == NULL) {
    fprintf(stderr, "lsh: pwd: %s\n", strerror(errno));
    return LSH_SUCCESS;
  }

  printf("%s\n", cwd);
  free(cwd);
  return LSH_SUCCESS;
}

int lsh_help(char **args) {
  (void)args;
  
  printf("LSH Shell - Available Commands:\n");
  printf("================================\n\n");
  printf("Built-in commands:\n");
  
  for (size_t i = 0; i < g_builtin_count; i++) {
    printf(" %-10s - %s\n", 
        g_builtin_commands[i].name,
        g_builtin_commands[i].description);
  }

  printf("\nYou can also run any external program by typing its name.\n");
  printf("Use Ctrl+C to interrupt a running program.\n");
  printf("Use Ctrl+D or 'exit' to quit the shell.\n\n");

  return LSH_SUCCESS;
}

int lsh_exit(char **args) {
  (void)args;
  g_shell_state.running = 0;
  return LSH_EXIT;
}
