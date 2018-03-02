/*
 * Written by John Hardy
 * A basic rendition of the diff command that compares two text files and
 * prints to stdout the lines containing differences between them. Note, this
 * program does not handle isolated newlines in the middle of text documents.
 */
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

#define BUFFER_SIZE 1
#define LINE_SIZE 1024
#define FILE_PATH_SIZE 1024

static char buffOne[BUFFER_SIZE];
static char buffTwo[BUFFER_SIZE];
static char lineOne[LINE_SIZE];
static char lineTwo[LINE_SIZE];

int isFile(char* path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

int printLine(char* buff) {
  char* temp = malloc(sizeof(char) * BUFFER_SIZE);
  int size = 0;
  for (char* c = buff; *c != '\n'; c++) {
    temp[size] = *c;
    size++;
  }
  write(1, temp, size);
  free(temp);
  return 0;
}

int printDiff(char* buffOne, char* buffTwo) {
  printLine(buffOne);
  write(1, "  :  ", 5);
  printLine(buffTwo);
  write(1, "\n", 1);
  return 0;
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

int compareFiles(FILE* fOne, FILE* fTwo) {
  int fOneCharsRead = loadBuffer(fOne, buffOne);
  int fTwoCharsRead = loadBuffer(fTwo, buffTwo);
  int beginOne = 0;
  int beginTwo = 0;
  int currPosOne = -1;
  int currPosTwo = -1;
  int offsetOne = 0;
  int offsetTwo = 0;
  int foundDiff = 0;
  int overflow = 0;
  int hold = 0;
  char charOne;
  char charTwo;

  while ((fOneCharsRead > 0 && fTwoCharsRead > 0) || hold != 0) {
    if (hold != 1) {
      currPosOne++;
      offsetOne++;
    }
    if (hold != 2) {
      currPosTwo++;
      offsetTwo++;
    }
    charOne = buffOne[currPosOne];
    charTwo = buffTwo[currPosTwo];
    lineOne[offsetOne] = buffOne[currPosOne];
    lineTwo[offsetTwo] = buffTwo[currPosTwo];

    if (currPosOne == fOneCharsRead - 1) {//We have reached the end of buffer one
      fOneCharsRead = loadBuffer(fOne, buffOne);
      currPosOne = -1;
      overflow = 1;
    }
    if (currPosTwo == fTwoCharsRead - 1) {//We have reached the end of buffer two
      fTwoCharsRead = loadBuffer(fTwo, buffTwo);
      currPosTwo = -1;
      overflow = 2;
    }

    if (charOne == charTwo) {
      if (charOne == '\n') {//Finished this line, start over
        if (foundDiff) {
          printDiff(lineOne, lineTwo);
        }
        offsetOne = -1;
        offsetTwo = -1;
        hold = 0;
        foundDiff = 0;
      }
    } else {
      foundDiff = 1;
      if (charOne == '\n') {//Found two words of seperate length
        hold = 1;
      } else if (charTwo == '\n') {
        hold = 2;
      }
    }
  }

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

  compareFiles(fileOne, fileTwo);

  fclose(fileOne);
  fclose(fileTwo);
  return 0;
}
