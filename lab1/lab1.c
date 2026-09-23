#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *buf = NULL;
  size_t size = 0;

  while (1) {
    printf("Please enter some text: ");
    ssize_t nread = getline(&buf, &size, stdin);
    if (nread == -1) {
      if (feof(stdin)) {
        break;
      }
      perror("getline");
      free(buf);
      exit(EXIT_FAILURE);
    }

    // remove teh trailing newline
    if (nread > 0 && buf[nread - 1] == '\n') {
      buf[nread - 1] = '\0';
    }

    printf("Tokens: \n");
    char *saveptr;
    char *token = strtok_r(buf, " ", &saveptr);
    while (token != NULL) {
      printf("%s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }
  }

  free(buf);
  return 0;
}
