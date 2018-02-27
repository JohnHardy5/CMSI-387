/*
 * Written by John Hardy
 * A basic rendition of the cat command line argument that quickly spits out the
 * contents of a file into the terminal. It can also concatenate multiple files
 * together.
 */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>//TODO: Remove printfs

static const int BUFFER_SIZE = 1024;

/*
 * Reads the file at a given path and prints it to stdout.
 * Returns an error if file could not be found or opened.
 */
int readFile(char* filePath) {
  FILE* file = fopen(filePath, "r");
  if (!file) {
    write(2, "Could not open file.\n", 21);
    exit(-1);
  }
  int fd = fileno(file);
  char buffer[BUFFER_SIZE];
  int charsRead;

  while ((charsRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
      write(1, buffer, charsRead);
  }

  fclose(file);
  return 0;
}

int main(int argc, char** argv) {
  if (argc == 1) {
    write(2, "No files provided.\n", 19);
    return -1;
  } else if(argc == 2) { //Single file was given, so just print it out
    readFile(argv[1]);
  } else { //More than one file given, read each file and concatenate them together
    for (int i = 1; i < argc; i++) {
      readFile(argv[i]);
    }
  }
  return 0;
}
