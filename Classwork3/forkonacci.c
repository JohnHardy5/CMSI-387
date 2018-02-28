/*
 * Written mostly by John Hardy, insight provided by J Goocher. Joey Martinez
 * and Jackson Watkins kind of helped a little.
 * WARNING: THIS ONLY WORKS UP TO THE 93rd Fib Number
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Not enough args given.\n");
    return -1;
  }

  int n = atoi(argv[1]);
  if (n < 1 || n > 93) {
    printf("What are you doing? Stop that!\n");
    return -1;
  }
  long currVal = 0;
  long nextVal = 1;

  for (int i = 0; i < n; i++) {
    pid_t pid;
    pid = fork();
    wait(NULL);

    if (pid == 0) {//Child prints values
      printf(" %ld", currVal);
      if (i == n - 1) {
        printf("\n");
      }
      return 0;
    } else {//Parent produces values
      long temp = currVal;
      currVal = nextVal;
      nextVal = temp + nextVal;
    }
  }
  return 0;
}
