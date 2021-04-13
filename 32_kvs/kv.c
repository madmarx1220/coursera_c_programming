#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * split(char * line) {
  char * ptr;
  char * ptr1;
  kvpair_t * pair = malloc(sizeof(*pair));
  if((ptr = strchr(line, '=')) == NULL) {
    fprintf(stderr, "No = in the input file!");
    exit(EXIT_FAILURE);
  }
  pair->key = malloc((ptr-line+1)*sizeof(*pair->key));
  strncpy(pair->key, line, (ptr-line+1));
  pair->key[ptr-line] = '\0';
  ptr++;
  ptr1 = strchr(line, '\n');
  *ptr1 = '\0';
  pair->value = malloc((ptr1-ptr+1)*sizeof(*pair->value));
  strncpy(pair->value, ptr, (ptr1-ptr+1));
  return pair;
}
  
void addToArray(kvpair_t * pair, kvarray_t * array) {
  array->num_of_kvpairs++;
  array->kvpairs = realloc(array->kvpairs, array->num_of_kvpairs * sizeof(*array->kvpairs));
  array->kvpairs[array->num_of_kvpairs - 1] = pair;
}

kvarray_t * readKVs(const char * fname) {
  char * line = NULL;
  size_t sz;
  kvpair_t * kvpair;
  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  kvarray->num_of_kvpairs = 0;
  kvarray->kvpairs = NULL;
  FILE * f = fopen(fname, "r");
  if(f == NULL) {
    perror("could not open the file");
    exit(EXIT_FAILURE);
  }
  while(getline(&line, &sz, f) >= 0) {
    kvpair = split(line);
    addToArray(kvpair, kvarray);
  }
  free(line);
  if(fclose(f) != 0) {
    perror("file can not be closed");
    exit(EXIT_FAILURE);
  }
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  for(int i=0; i<pairs->num_of_kvpairs; i++) {
    free((pairs->kvpairs[i])->key);
    free((pairs->kvpairs[i])->value);
    free(pairs->kvpairs[i]);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for(int i=0; i<pairs->num_of_kvpairs; i++) {
    printf("key = '%s' value = '%s'\n", (pairs->kvpairs[i])->key, (pairs->kvpairs[i])->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for(int i=0; i<pairs->num_of_kvpairs; i++) {
    if(strcmp((pairs->kvpairs[i])->key, key) == 0) {
      return (pairs->kvpairs[i])->key;
    }
  }
  return NULL;
}
