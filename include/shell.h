#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>

typedef struct {
  char *name;
  int (*function)(char **);
  const char *description;
} builtin_command_t;

typedef struct {
  int running;
} shell_state_t;

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#define LSH_PROMPT "> "

#define LSH_SUCCESS 1
#define LSH_EXIT 0

extern shell_state_t g_shell_state;
extern const builtin_command_t g_builtin_commands[];
extern const size_t g_builtin_count;

void *lsh_malloc(size_t size);
void *lsh_realloc(void *ptr, size_t size);

void lsh_setup_signals(void);

char *lsh_read_line(void);
char **lsh_split_line(char *line);
void lsh_free_tokens(char **tokens);

int lsh_execute(char **args);
void lsh_loop(void);

int lsh_cd(char **args);
int lsh_pwd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

#endif
