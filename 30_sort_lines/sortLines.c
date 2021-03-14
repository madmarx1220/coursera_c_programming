#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void print(char ** data, size_t size) {
  for(size_t i=0; i<size; i++) {
    printf("%s", data[i]);
    free(data[i]);
  }
}

void readFile(FILE * f) {
  char ** data = NULL;
  char * line = NULL;
  size_t size = 0;
  int len = 0;
  size_t idx = 0;
  while((len = getline(&line, &size, f)) >= 0) {
    data = realloc(data, (idx+1)*sizeof(*data));
    data[idx] = malloc((len+1) * sizeof(*data[idx]));
    strcpy(data[idx], line);
    idx++;
  }
  free(line);
  sortData(data, idx);
  print(data, idx);
  free(data);
}


int main(int argc, char ** argv) {
  if(argc == 1) {
    readFile(stdin);
  }
  else {
    char ** ptr = argv+1;
    while(*ptr != NULL) {
      FILE * f = fopen(*ptr, "r");
      if(f == NULL) {
	perror("could not open the file");
	return EXIT_FAILURE;
      }
      readFile(f);
      fclose(f);
      ptr++;
    }
  }
  return EXIT_SUCCESS;
}
