/*
 * Written by John Hardy
 * A basic rendition of the diff command that compares two text files and
 * prints to stdout the lines containing differences between them.
 */
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>//TODO: Remove printfs and stdio library

static const int BUFFER_SIZE = 1024;

int main(int argc, char** argv) {
  if (argc < 3) {
    write(2, "Not enough args given.\n", 23);
    exit(-1);
  }

  char* pathOne = malloc(sizeof(char) * BUFFER_SIZE);
  if (realpath(argv[1], pathOne) == NULL) {
    write(2, "First argument was not a path.\n", 31);
    exit(-1);
  }

  char* pathTwo = malloc(sizeof(char) * BUFFER_SIZE);
  if (realpath(argv[2], pathTwo) == NULL) {
    write(2, "Second argument was not a path.\n", 32);
    exit(-1);
  }

  printf("%s\n", pathOne);
  printf("%s\n", pathTwo);

  free(pathOne);
  free(pathTwo);
  return 0;
}
