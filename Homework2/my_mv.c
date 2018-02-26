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
#include <string.h>
#include <sys/stat.h>
#include <libgen.h>

static int BUFFER_SIZE = 100;

int isFile(char* path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

int linkFileTo(char* filePath, char* newPath) {
  if (link(filePath, newPath) == -1) {
    printf("There was a problem linking the file to the given path.\n");
    return -1;
  }
  return 0;
}

int unlinkFileFrom(char* filePath) {
  if (unlink(filePath) == -1) {
    printf("There was a problem removing the second file.\n");
    return -1;
  }
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

  if (isFile(pathOne)) {
    if (isFile(pathTwo)) {//Remove file that is being overwritten
      unlinkFileFrom(pathTwo);
    } else {//update the directory so that it has the file name
      char* fileName = basename(pathOne);
      pathTwo = strcat(pathTwo, "/");
      pathTwo = strcat(pathTwo, basename(pathOne));
    }
    linkFileTo(pathOne, pathTwo);
    unlinkFileFrom(pathOne);
  } else {

  }
  printf("%s\n", pathOne);
  printf("%s\n", pathTwo);

  free(pathOne);
  free(pathTwo);
  return 0;
}
