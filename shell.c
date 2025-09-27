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
int lsh_num_builtins(void);

char *builtin_str[] = {"cd", "help", "exit"};
int (*builtin_func[]) (char **) = {&lsh_cd, &lsh_help, &lsh_exit};

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

  if (buffer == NULL) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

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
      char *new_buffer = realloc(buffer, bufsize);
      if (new_buffer == NULL) {
        free(buffer);
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
      buffer = new_buffer;
    }
  }
}

char **lsh_split_line(char *line) {
  size_t bufsize = LSH_TOK_BUFSIZE;
  size_t position = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token = NULL;

  if (tokens == NULL) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position++] = token;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      char **new_tokens = realloc(tokens, bufsize * sizeof(char *));
      if (new_tokens == NULL) {
        free(tokens);
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
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
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return LSH_SUCCESS;
}

int lsh_help(char **args) {
  printf("LSH Shell\n");
  printf("Type program names and arguments, then hit enter.\n");
  printf("Built-in commands:\n");
  for (int i = 0; i < lsh_num_builtins(); i++) {
    printf(" %s\n", builtin_str[i]);
  }
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
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return lsh_launch(args);
}

void *lsh_safe_malloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    printf(stderr, "allocation error");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

int lsh_num_builtins(void) {
  return sizeof(builtin_str) / sizeof(char *);
}
