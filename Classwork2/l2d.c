/*
 * Jackson Watkins, John Hardy, J Goocher, Joey Martinez
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static char* NEW_LINK_DIRECTORY = "/home/john/Desktop\0";

int findLastSlashPos(int sizeOfPath, char* targetFilePath) {
  int lastKnownSlash = 0;
  for (int i = 0; i < sizeOfPath; i++) {
    if (targetFilePath[i] == '/') {
      lastKnownSlash = i;
    }
  }
  return lastKnownSlash;
}

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("Not enough arguments provided.\n");
    return -1;
  }
  char* targetFilePath = argv[1];
  int sizeOfTargetFilePath = strlen(targetFilePath);
  int fileNamePos = findLastSlashPos(sizeOfTargetFilePath, targetFilePath);
  int fileNameSize = sizeOfTargetFilePath - fileNamePos + 1; // Leave space for first /
  int sizeOfNewLinkDirectory = strlen(NEW_LINK_DIRECTORY);
  int sizeOfNewPath = sizeOfNewLinkDirectory + fileNameSize;
  char* newPath = malloc(sizeOfNewPath * sizeof(char));
  int offset = 0;
  for (int i = 0; i < sizeOfNewPath; i++) {
    if (i < sizeOfNewLinkDirectory) {
      newPath[i] = NEW_LINK_DIRECTORY[i];
    } else {
      newPath[i] = targetFilePath[fileNamePos + offset];
      offset++;
    }
  }
  int errorVal = symlink(targetFilePath, newPath);
  if (errorVal == -1) {
    printf("ERROR, link not created.\n");
  }
  free(newPath);
  return errorVal;
}
