#include <stdio.h>
#include <string.h>

#include "../include/shell.h"

char *lsh_read_line(void) {
  size_t bufsize = LSH_RL_BUFSIZE;
  size_t position = 0;
  char *buffer = lsh_malloc(bufsize);
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
      buffer = lsh_realloc(buffer, bufsize);
    }
  }
}

char **lsh_split_line(char *line) {
  size_t bufsize = LSH_TOK_BUFSIZE;
  size_t position = 0;
  char **tokens = lsh_malloc(bufsize * sizeof(char *));
  char *line_copy = strdup(line);
  
  if (line_copy == NULL) {
    fprintf(stderr, "lsh: strdup failed\n");
    free(tokens);
    return NULL;
  }

  char *token = strtok(line_copy, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = strdup(token);
    if (tokens[position] == NULL) {
      fprintf(stderr, "lsh: strdup failed\n");
      for (size_t i = 0; i < position; i++) {
        free(tokens[i]);
      }
      free(tokens);
      free(line_copy);
      return NULL;
    }

    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = lsh_realloc(tokens, bufsize * sizeof(char *));
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }

  tokens[position] = NULL;
  free(line_copy);
  return tokens;
}

void lsh_free_tokens(char **tokens) {
  if (tokens == NULL) {
    return;
  }

  for (size_t i = 0; tokens[i] != NULL; i++) {
    free(tokens[i]);
  }
  free(tokens);
}
