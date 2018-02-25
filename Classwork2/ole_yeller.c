/*
 * Jackson Watkins, John Hardy, J Goocher, Joey Martinez
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* yell(char* whisper) {
  char* upperCase = malloc(strlen(whisper) + 1);
  for(int i = 0; i < strlen(whisper); i++) {
    upperCase[i] = whisper[i] - 32;
  }
  upperCase[strlen(upperCase)] = '!';
  return upperCase;
}

int main(int argc, char** argv){
  for (int i = 1; i < argc; i++) {
    char* upperCaseWord = yell(argv[i]);
    printf("%s ", upperCaseWord);
    free(upperCaseWord);
  }
  printf("\n");
}

