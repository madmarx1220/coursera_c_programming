#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int largestNum(const int * array, int n) {
  int largst = 0;
  int index;
  for(int i=0; i<n; i++) {
    if(largst < array[i]) {
      largst = array[i];
      index = i;
    }
  }
  if(largst == 0) {
    fprintf(stderr, "No character found in the file\n");
    exit(EXIT_FAILURE);
  }
  return index;
}


char frequencyCounting(FILE * f) {
  int c;
  int array[26] = {0};
  while((c = fgetc(f)) != EOF) {
    if(isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      array[c]++;
    }
  }
  c = largestNum(array, 26);
  return c += 'a';
}

int main(int argc, char ** argv) {
  if(argc != 2) {
    fprintf(stderr, "Command line arguments incorrect\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if(f == NULL) {
    perror("Could not open the file\n");
    return EXIT_FAILURE;
  }
  char keyLetter = frequencyCounting(f);
  if(keyLetter < 'e') {
    printf("%d\n", 26 - ('e' - keyLetter));
  }
  else {
    printf("%d\n", keyLetter - 'e');
  }
  return EXIT_SUCCESS;
}
