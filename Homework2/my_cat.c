/*
 * Written by John Hardy
 * A basic rendition of the cat command line argument that quickly spits out the
 * contents of a file into the terminal.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int readFile(char* filePath) {
  int currChar;
  FILE *file;
  file = fopen(filePath, "r");
  if (file) {
    while ((currChar = getc(file)) != EOF) {
        putchar(currChar);
    }
    fclose(file);
  } else {
    printf("There was a problem opening the file. Make sure the correct path is given.\n");
    return -1;
  }
  return 0;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    printf("Not enough arguments provided.\n");
    return -1;
  } else if(argc == 2) {
     return readFile(argv[1]);
  }
  return 0;
}
