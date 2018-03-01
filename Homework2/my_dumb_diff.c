/*
 * Written by John Hardy
 * A basic rendition of the diff command that compares two text files and
 * prints to stdout the lines containing differences between them.
 */
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <stdio.h>//TODO: Remove printfs and stdio library

static const int BUFFER_SIZE = 1024;

int isFile(char* path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

char* loadFilePath(char* p) {
  char* newPath = malloc(sizeof(char) * BUFFER_SIZE);
  if (realpath(p, newPath) == NULL || !isFile(newPath)) {
    return NULL;
  }
  return newPath;
}

int main(int argc, char** argv) {
  if (argc < 3) {
    write(2, "Not enough args given.\n", 23);
    exit(-1);
  }

  char* pathOne = loadFilePath(argv[1]);
  if (pathOne == NULL) {
    write(2, "First argument was not valid.\n", 30);
    exit(-1);
  }

  char* pathTwo = loadFilePath(argv[2]);
  if (pathTwo == NULL) {
    write(2, "Second argument was not a valid.\n", 33);
    exit(-1);
  }

  printf("%s\n", pathOne);
  printf("%s\n", pathTwo);

  free(pathOne);
  free(pathTwo);
  return 0;
}
