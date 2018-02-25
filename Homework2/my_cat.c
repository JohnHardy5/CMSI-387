/*
 * Written by John Hardy
 * A basic rendition of the cat command line argument that quickly spits out the
 * contents of a file into the terminal.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  if (argc == 0) {
    printf("Not enough arguments provided.\n");
    return -1;
  }
  char* filePath = argv[1];
  printf("%s\n", filePath);
  return 0;
}
