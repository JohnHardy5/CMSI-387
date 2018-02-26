#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Not enough args given.\n");
    return -1;
  }
  int n = atoi(argv[1]);
  printf("The Fibonacci sequence using forks is:");

  pid_t pid;
  pid = fork();

  if (pid == 0) {

  } else {

  }

  return 0;
}
