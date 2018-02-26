/*
 * Written by John Hardy
 * A basic rendition of the mv command that moves a given file to a given
 * directory or overwrites the second file if two files are given instead.
 */
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int isFile(char* path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

int linkToDir(char* filePath, char* dirpath) {
  return 0;
}

int unlinkFromDir(char* filePath) {
  return 0;
}

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Not enough args given.\n");
    return -1;
  }
  printf("%d\n", isFile(argv[1]));
  return 0;
}
