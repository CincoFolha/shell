#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define LSH_PROMPT "> "

#define LSH_SUCCESS 1
#define LSH_EXIT 0
#define LSH_ERROR -1

typedef struct {
  char *name;
  int (*function)(char **);
} lsh_command;

// Protótipos das funções principais
void lsh_loop(void);
char *lsh_read_line(void);
char **lsh_split_line(char *line);
int lsh_execute(char **args);
int lsh_launch(char **args);

// Protótipos dos comandos built-in
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

// Utilitários
void *lsh_safe_malloc(size_t size);
void *lsh_safe_realloc(void *ptr, size_t size);
void lsh_print_error(char *message);
int lsh_num_builtins(void);

lsh_command builtin_functions[] = {
  {"cd", &lsh_cd},
  {"help", &lsh_help},
  {"exit", &lsh_exit}
};

int main(int argc, char **argv) {
  printf("LSH Shell v1.0 - Simple Shell Implementation\n");
  printf("Type 'help' for available commands.\n\n");

  lsh_loop();

  printf("\nGoodbye!\n");
  return EXIT_SUCCESS;
}

void lsh_loop(void) {
  char *line = NULL;
  char **args = NULL;
  int status = LSH_SUCCESS;

  do {
    printf(LSH_PROMPT);
    
    line = lsh_read_line();
    if (line == NULL) {
      printf("\n");
      break;
    }

    args = lsh_split_line(line);
    if (args != NULL && args[0] != NULL) {
      status = lsh_execute(args);
    }

    free(line);
    free(args);
    line = NULL;
    args = NULL;
  } while (status == LSH_SUCCESS);
}

char *lsh_read_line(void) {
  size_t bufsize = LSH_RL_BUFSIZE;
  size_t position = 0;
  char *buffer = lsh_safe_malloc(sizeof(char) * bufsize);
  int c;

  while (1) {
    c = getchar();
    
    if (c == EOF) {
      if (position == 0) {
        free(buffer);
        return NULL;
      }
      buffer[position] = '\0';
      return buffer;
    }

    if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    }

    buffer[position] = c;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      char *new_buffer = lsh_safe_realloc(buffer, bufsize);
      buffer = new_buffer;
    }
  }
}

char **lsh_split_line(char *line) {
  size_t bufsize = LSH_TOK_BUFSIZE;
  size_t position = 0;
  char **tokens = lsh_safe_malloc(bufsize * sizeof(char *));
  char *token = NULL;

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position++] = token;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      char **new_tokens = lsh_safe_realloc(tokens, bufsize * sizeof(char *));
      tokens = new_tokens;
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }

  tokens[position] = NULL;
  return tokens;
}

int lsh_launch(char **args) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("lsh");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    perror("lsh");
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return LSH_SUCCESS;
}

int lsh_cd(char **args) {
  if (args[1] == NULL) {
    lsh_print_error("lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return LSH_SUCCESS;
}

int lsh_help(char **args) {
  printf("LSH Shell - Available Commands:\n");
  printf("================================\n\n");
  
  printf("Built-in commands:\n");
  for (int i = 0; i < lsh_num_builtins(); i++) {
    printf(" %s\n", builtin_functions[i].name);
  }

  printf("\nYou can also run any external program by typing its name.\n");
  printf("Use Ctrl+C to interrupt a running program.\n");
  printf("Use Ctrl+D or 'exit' to quit the shell.\n\n");

  return LSH_SUCCESS;
}

int lsh_exit(char **args) {
  return LSH_EXIT;
}

int lsh_execute(char **args) {
  if (args[0] == NULL) {
    return LSH_SUCCESS;
  }

  for (int i = 0; i < lsh_num_builtins(); i++) {
    if (strcmp(args[0], builtin_functions[i].name) == 0) {
      return builtin_functions[i].function(args);
    }
  }

  return lsh_launch(args);
}

void *lsh_safe_malloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    lsh_print_error("allocation error");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

void *lsh_safe_realloc(void *ptr, size_t size) {
  void *new_ptr = realloc(ptr, size);
  if (new_ptr == NULL) {
    free(ptr);
    lsh_print_error("allocation error");
    exit(EXIT_FAILURE);
  }
  return new_ptr;
}

void lsh_print_error(char *message) {
  fprintf(stderr, message);
}

int lsh_num_builtins(void) {
  return sizeof(builtin_functions) / sizeof(lsh_command);
}
