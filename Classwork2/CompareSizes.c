#include <stdio.h>

void compare_sizes () {
  printf("%zu\n", sizeof(int));
  printf("%zu\n", sizeof(char));
  printf("%zu\n", sizeof(double));
}



int main(int argc, char** argv) {
  compare_sizes();
  return 0;
}
