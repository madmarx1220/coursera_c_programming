#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void rotate(char matrix[10][10]);

int main(int argc, char ** argv) {
  if(argc != 2) {
    fprintf(stderr, "Wrong command line argument count");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    perror("Could not open the file:");
    return EXIT_FAILURE;
  }
  char matrix[10][10];
  char line[12] = {0}; 
  char * ptr;
  for(int i=0; i < 10; i++) {
    if(fgets(line, 12, f) == NULL) {
      fprintf(stderr, "The line is too short");
      return EXIT_FAILURE;
    }
    if((ptr = strchr(line, '\n')) == NULL) {
      fprintf(stderr, "The line is too long");
      return EXIT_FAILURE;
    }
    else if(ptr != &line[10]) {
      fprintf(stderr, "The line is too short");
      return EXIT_FAILURE;
    }
    else {
      strncpy(matrix[i], line, 10);
    }
  }
  if(fgetc(f) != EOF) {
    fprintf(stderr, "The file has more too many lines");
    return EXIT_FAILURE;
  }
  rotate(matrix);
  for(int i=0; i < 10; i++) {
    for(int y=0; y < 10; y++) {
      printf("%c", matrix[i][y]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}


void rotate(char matrix[10][10]) {
  char tempMatrix[10][10];
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      tempMatrix[i][j] = matrix[9-j][i];
    }
  }
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++) {
      matrix[i][j] = tempMatrix[i][j];
    }
  }
}
