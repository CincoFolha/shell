#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "../include/shell.h"

void *lsh_malloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "lsh: malloc failed: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  return ptr;
}

void *lsh_realloc(void *ptr, size_t size) {
  void *new_ptr =  realloc(ptr, size);
  if (new_ptr == NULL) {
    free(ptr);
    fprintf(stderr, "lsh: realloc failed: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  return new_ptr;
}
