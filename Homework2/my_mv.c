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

static const int BUFFER_SIZE = 1024;


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


/*
 *WARNING: concatName changes the first char array
 */
int concatName(char* fp, char* name) {
  fp = strncat(fp, "/", BUFFER_SIZE);
  fp = strncat(fp, name, BUFFER_SIZE);
  return 0;
}


int linkFileTo(char* filePath, char* newPath) {
  if (link(filePath, newPath) == -1) {
    write(2, "Could not link file to given path.\n", 35);
    exit(-1);
  }
  return 0;
}


int unlinkFileFrom(char* filePath) {
  if (unlink(filePath) == -1) {
    write(2, "Could not remove the second file.\n", 34);
    exit(-1);
  }
  return 0;
}


int makeDir(char* path) {
  if (mkdir(path, 0777) == -1) {
    write(2, "New directory could not be created.\n", 35);
    exit(-1);
  }
  return 0;
}

int moveDir(char* src, char* dest) {
  DIR* currDir = opendir(src);
  if (currDir == NULL) {
    write(2, "Source directory could not be opened.\n", 38);
    exit(-1);
  }

  struct dirent* currItem;
  char* newDirPath = malloc(sizeof(char) * BUFFER_SIZE);
  strncpy(newDirPath, dest, BUFFER_SIZE);
  concatName(newDirPath, basename(src));//Setup destination for new directory
  makeDir(newDirPath);

  while ((currItem = readdir(currDir)) != NULL) {
    char* itemName = currItem->d_name;
    if (strcmp(itemName, ".") == 0 || strcmp(itemName, "..") == 0) {
      continue;
    }

    char* currItemPath = malloc(sizeof(char) * BUFFER_SIZE);
    char* newPath = malloc(sizeof(char) * BUFFER_SIZE);
    strncpy(currItemPath, src, BUFFER_SIZE);
    strncpy(newPath, newDirPath, BUFFER_SIZE);
    concatName(currItemPath, itemName);
    concatName(newPath, itemName);
    if (isFile(currItemPath)) {
      //printf("Found file: %s\n", currItemPath);
      //printf("Linking to dir: %s\n", newPath);
      linkFileTo(currItemPath, newPath);
      unlinkFileFrom(currItemPath);
    } else if (isDir(currItemPath)){//Otherwise repeat on the sub-directory
      //printf("Found directory: %s\n", currItemPath);
      moveDir(currItemPath, newDirPath);
    } else {
      write(2, "Item in src directory is not a file or directory.\n", 50);
      exit(-1);
    }

    free(currItemPath);
    free(newPath);
  }

  rmdir(src);//All files moved, delete old folder

  if (closedir(currDir) == -1) {
    write(2, "Source directory could not be closed.\n", 38);
    exit(-1);
  }

  free(newDirPath);
  return 0;
}


int main(int argc, char** argv) {
  if (argc < 3) {
    write(2, "Not enough args given.\n", 23);
    exit(-1);
  }

  char* pathOne = malloc(sizeof(char) * BUFFER_SIZE);
  char* pathTwo = malloc(sizeof(char) * BUFFER_SIZE);
  if (realpath(argv[1], pathOne) == NULL) {
    write(2, "First argument was not a path.\n", 31);
    exit(-1);
  }
  if (realpath(argv[2], pathTwo) == NULL) {
    write(2, "Second argument was not a path.\n", 32);
    exit(-1);
  }

  if (isFile(pathOne)) {
    if (isFile(pathTwo)) {//Remove file that is being overwritten
      unlinkFileFrom(pathTwo);
    } else if (isDir(pathTwo)) {//update the directory so that it has the file name
      concatName(pathTwo, basename(pathOne));
    } else {
      write(2, "Second path is not a file or directory.\n", 40);
      exit(-1);
    }
    linkFileTo(pathOne, pathTwo);
    unlinkFileFrom(pathOne);
  } else if (isDir(pathOne)) {
    if (isFile(pathTwo)) {//update the directory so that it has the file name
      concatName(pathOne, basename(pathTwo));
      linkFileTo(pathTwo, pathOne);
      unlinkFileFrom(pathTwo);
    } else if (isDir(pathTwo)) {//both are directories, transfer files inside
      moveDir(pathOne, pathTwo);
    } else {
      write(2, "Second path is not a file or directory.\n", 40);
      exit(-1);
    }
  } else {
    write(2, "First path is not a file or directory.\n", 39);
    exit(-1);
  }

  free(pathOne);
  free(pathTwo);
  return 0;
}
