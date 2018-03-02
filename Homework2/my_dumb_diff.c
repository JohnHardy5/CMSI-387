/*
 * Written by John Hardy
 * A basic rendition of the diff command that compares two text files and
 * prints to stdout the lines containing differences between them.
 */
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <stdio.h>//TODO: Remove printfs and stdio library

#define BUFFER_SIZE 2
#define FILE_PATH_SIZE 1024

static char buffOne[BUFFER_SIZE];
static char buffTwo[BUFFER_SIZE];

int isFile(char* path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

int loadBuffer(FILE* file, char* buff) {
  return read(fileno(file), buff, BUFFER_SIZE);
}

FILE* loadFile(char* p) {
  char* fullPath = malloc(sizeof(char) * FILE_PATH_SIZE);
  realpath(p, fullPath);
  FILE* file = fopen(fullPath, "r");
  free(fullPath);
  if (!file) {
    return NULL;
  }
  return file;
}

int compareFiles(char* pathOne, char* pathTwo) {
  return 0;
}

int main(int argc, char** argv) {
  if (argc < 3) {
    write(2, "Not enough args given.\n", 23);
    exit(-1);
  }

  FILE* fileOne = fopen(argv[1], "r");
  if (!fileOne) {
    write(2, "Could not open first file.\n", 27);
    exit(-1);
  }

  FILE* fileTwo = fopen(argv[2], "r");
  if (!fileTwo) {
    write(2, "Could not open second file.\n", 28);
    exit(-1);
  }

  int charsRead = loadBuffer(fileOne, buffOne);
  write(1, buffOne, charsRead);
  charsRead = loadBuffer(fileTwo, buffTwo);
  write(1, buffTwo, charsRead);

  fclose(fileOne);
  fclose(fileTwo);
  return 0;
}
