/*
 * Written by John Hardy
 * A basic rendition of the mv command that:
 * 1) moves a given file to a given directory
 * 2) overwrites the second file if two files are given
 * 3) moves the first directory into the second if two directories are given
 */
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

static int BUFFER_SIZE = 50;

int isFile(char* path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

int linkFileTo(char* filePath, char* dirpath) {
  return 0;
}

int unlinkFileFrom(char* filePath) {
  return 0;
}

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Not enough args given.\n");
    return -1;
  }
  char* pathOne = malloc(sizeof(char) * BUFFER_SIZE);
  char* pathTwo = malloc(sizeof(char) * BUFFER_SIZE);

  if (realpath(argv[1], pathOne) == NULL) {
    printf("First argument was not a path.\n");
    return -1;
  }
  if (realpath(argv[2], pathTwo) == NULL) {
    printf("Second argument was not a path.\n");
    return -1;
  }

  printf("%s\n", pathOne);
  printf("%s\n", pathTwo);
/*
  if (isFile(pathOne)) {
    if (isFile(pathTwo)) {
      linkFileTo(pathOne, pathTwo);
    } else {
      linkFileTo(pathOne, pathTwo);
    }
  } else {

  }*/

  free(pathOne);
  free(pathTwo);
  return 0;
}
