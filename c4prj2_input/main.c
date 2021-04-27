#include "future.h"
#include "input.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
  if(argc != 2) {
    fprintf(stderr, "please input a file\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    perror("can't open the file");
    return EXIT_FAILURE;
  }
  size_t n_hands;
  
