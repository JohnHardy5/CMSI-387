/*
 * Written by John Hardy
 * A basic rendition of the diff command that compares two text files and
 * prints to stdout the lines containing differences between them.
 */
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <stdio.h>//TODO: Remove printfs and stdio library

#define BUFFER_SIZE 42

static char buffOne[BUFFER_SIZE];
static char buffTwo[BUFFER_SIZE];

int isFile(char* path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

int loadBuffer(int fd, char* buff) {
  int charsRead = read(fd, buff, BUFFER_SIZE);
  return charsRead;
}

char* loadFilePath(char* p) {
  char* newPath = malloc(sizeof(char) * BUFFER_SIZE);
  if (realpath(p, newPath) == NULL || !isFile(newPath)) {
    return NULL;
  }
  return newPath;
}

FILE* loadFile(char* p) {
  FILE* file = fopen(p, "r");
  if (!file) {
    write(2, "Could not open file.\n", 21);
    exit(-1);
  }
  return file;
}

int compareFiles(char* pathOne, char* pathTwo) {
  FILE* fileOne = loadFile(pathOne);
  FILE* fileTwo = loadFile(pathTwo);



  fclose(fileOne);
  fclose(fileTwo);
  return 0;
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
    write(2, "Second argument was not valid.\n", 31);
    exit(-1);
  }

  FILE* fileOne = fopen(pathOne, "r");
  if (!fileOne) {
    write(2, "Could not open first file.\n", 27);
    exit(-1);
  }

  FILE* fileTwo = fopen(pathTwo, "r");
  if (!fileTwo) {
    write(2, "Could not open second file.\n", 28);
    exit(-1);
  }

  int fdOne = fileno(fileOne);
  int fdTwo = fileno(fileTwo);

  int charsRead = loadBuffer(fdOne, buffOne);
  write(1, buffOne, charsRead);
  charsRead = loadBuffer(fdTwo, buffTwo);
  write(1, buffTwo, charsRead);

  free(pathOne);
  free(pathTwo);
  fclose(fileOne);
  fclose(fileTwo);
  return 0;
}
