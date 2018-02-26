#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

  int main() {
    int n = 0;
    int count = 0;
    while(n < 10) {
        fork();
        int* i = malloc(1000);
        n++;
        count++;
    }
    printf("%d\n", count);
    return 0;
  }
