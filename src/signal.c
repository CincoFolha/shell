#include <signal.h>
#include <stdio.h>

#include "../include/shell.h"

static void lsh_handle_sigint(int sig) {
  (void)sig;
  printf("\n");
  fflush(stdout);
}

void lsh_setup_signals(void) {
  signal(SIGINT, lsh_handle_sigint);
}
