/*
 * Written by John Hardy
 * A basic rendition of the mv command that:
 * 1) moves a given file to a given directory
 * 2) overwrites the second file if two files are given
 * 3) moves the first directory into the second if two directories are given
 */
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <libgen.h>

static const int BUFFER_SIZE = 100;
static char* pathOne;
static char* pathTwo;

int isFile(char* path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

int isDir(char* path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISDIR(path_stat.st_mode);
}

int linkFileTo(char* filePath, char* newPath) {
  if (link(filePath, newPath) == -1) {
    printf("There was a problem linking the file to the given path.\n");
    exit(-1);
  }
  return 0;
}

int unlinkFileFrom(char* filePath) {
  if (unlink(filePath) == -1) {
    printf("There was a problem removing the second file.\n");
    exit(-1);
  }
  return 0;
}

int moveDir(char* s, char* d) {
  char* tempS = malloc(sizeof(char) * BUFFER_SIZE);
  char* tempD = malloc(sizeof(char) * BUFFER_SIZE);
  strncpy(tempS, s, BUFFER_SIZE);
  strncpy(tempD, d, BUFFER_SIZE);
  tempD = strcat(tempD, "/");//Setup destination for new directory
  tempD = strcat(tempD, basename(tempS));
  //printf("%s\n", tempD);
  if (mkdir(tempD, 0777) == -1) {
    printf("New directory could not be created.\n");
    exit(-1);
  }

  DIR* src = opendir(tempS);
  if (src == NULL) {
    printf("Source directory could not be opened.\n");
    exit(-1);
  }

  struct dirent* currItem;
  while ((currItem = readdir(src)) != NULL) {
    strncpy(tempS, s, BUFFER_SIZE);
    strncpy(tempD, d, BUFFER_SIZE);
    tempD = strcat(tempD, "/");
    tempD = strcat(tempD, basename(tempS));
    char* name = currItem->d_name;
    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
      continue;
    }
    char* currPath = strcat(tempS, "/");
    currPath = strcat(currPath, name);
    if (isFile(currPath)) {
      char* newPath = strcat(tempD, "/");
      newPath = strcat(newPath, name);
      //printf("Found file: %s\n", currPath);
      //printf("Linking to dir: %s\n", newPath);
      linkFileTo(currPath, newPath);
      unlinkFileFrom(currPath);
    } else if (isDir(currPath)){//Otherwise repeat on the sub-directory
      //printf("Found directory: %s\n", currPath);
      moveDir(currPath, tempD);
    }
  }

  rmdir(s);//All files moved, delete old folder

  if (closedir(src) == -1) {
    printf("Source directory could not be closed.\n");
    return -1;
  }
  free(tempS);
  free(tempD);
  return 0;
}

int main(int argc, char** argv) {
  if (argc < 3) {
    printf("Not enough args given.\n");
    exit(-1);
  }

  pathOne = malloc(sizeof(char) * BUFFER_SIZE);
  pathTwo = malloc(sizeof(char) * BUFFER_SIZE);
  if (realpath(argv[1], pathOne) == NULL) {
    printf("First argument was not a path.\n");
    exit(-1);
  }
  if (realpath(argv[2], pathTwo) == NULL) {
    printf("Second argument was not a path.\n");
    exit(-1);
  }

  if (isFile(pathOne)) {
    if (isFile(pathTwo)) {//Remove file that is being overwritten
      unlinkFileFrom(pathTwo);
    } else if (isDir(pathTwo)) {//update the directory so that it has the file name
      pathTwo = strcat(pathTwo, "/");
      pathTwo = strcat(pathTwo, basename(pathOne));
    }
    linkFileTo(pathOne, pathTwo);
    unlinkFileFrom(pathOne);
  } else if (isDir(pathOne)) {
    if (isFile(pathTwo)) {//update the directory so that it has the file name
      pathOne = strcat(pathOne, "/");
      pathOne = strcat(pathOne, basename(pathTwo));
      linkFileTo(pathTwo, pathOne);
      unlinkFileFrom(pathTwo);
    } else if (isDir(pathTwo)) {//both are directories, transfer files inside
      moveDir(pathOne, pathTwo);
    }
  }
  //printf("%s\n", pathOne);
  //printf("%s\n", pathTwo);

  free(pathOne);
  free(pathTwo);
  return 0;
}
