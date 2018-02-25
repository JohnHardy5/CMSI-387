/*
 * Written by John Hardy
 * A basic rendition of the cat command line argument that quickly spits out the
 * contents of a file into the terminal.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
 * Reads the file at a given path and prints it to stdout.
 * Returns an error if file could not be found or opened.
 */
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
    printf("There was a problem opening the file, ensure the correct path is given.\n");
    return -1;
  }
  return 0;
}

int main(int argc, char** argv) {
  if (argc == 1) { //Need at least one argument
    printf("No files provided.\n");
    return -1;
  } else if(argc == 2) { //Single file was given, so just print it out
    return readFile(argv[1]);
  } else { //More than one file given, read each file and concatenate them together
    for (int i = 1; i < argc; i++) {
      if (readFile(argv[i]) == -1) {
        return -1;
      }
    }
  }
  return 0;
}
