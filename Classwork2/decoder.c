/*
 * Jackson Watkins, John Hardy, J Goocher, Joey Martinez
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
  int x;
  for (int i = 1; i < argc; i++) {
    printf("%c", atoi(argv[i]));
  }
  printf("\n");
}

