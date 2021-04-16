#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  counts->countArray = NULL;
  counts->size = 0;
  counts->num_of_unknown = 0;
  return counts;
}

int isFound(counts_t * c, const char * name) {
  for(size_t i=0; i<c->size; i++) {
    if(strcmp((c->countArray[i])->string, name) == 0) {
      (c->countArray[i])->num_of_times++;
      return 1;
    }
  }
  return 0;
}

void addCount(counts_t * c, const char * name) {
  if(name == NULL) {
    c->num_of_unknown++;
  }
  else if (!isFound(c, name)) {
    c->size++;
    c->countArray = realloc(c->countArray, c->size * sizeof(*c->countArray));
    c->countArray[c->size-1] = malloc(sizeof(*(c->countArray[c->size-1])));
    (c->countArray[c->size-1])->num_of_times = 1;
    size_t len = strlen(name);
    (c->countArray[c->size-1])->string = malloc((len+1) * sizeof(*name));
    strcpy((c->countArray[c->size-1])->string, name);
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  for(size_t i=0; i<c->size; i++) {
    fprintf(outFile, "%s: %lu\n", (c->countArray[i])->string, (c->countArray[i])->num_of_times);
  }
  if(c->num_of_unknown > 0) {
    fprintf(outFile, "<unknown> : %lu\n", c->num_of_unknown);
  }
}

void freeCounts(counts_t * c) {
  for(size_t i=0; i<c->size; i++) {
    free((c->countArray[i])->string);
    free(c->countArray[i]);
  }
  free(c->countArray);
  free(c);
}
