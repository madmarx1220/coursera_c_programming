#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  char * line = NULL;
  size_t sz;
  ssize_t len;
  counts_t * counts = createCounts();
  char * value;
  FILE * f = fopen(filename, "r");
  if(f == NULL) {
    perror("can not open the key list file!");
    exit(EXIT_FAILURE);
  }
  while((len = getline(&line, &sz, f)) >= 0) {
    line[len-1] = '\0';
    value = lookupValue(kvPairs, line);
    addCount(counts, value);
  }
  free(line);
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if(argc < 3) {
    fprintf(stderr, "please input correct arguments\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  if(kv == NULL) {
    fprintf(stderr, "can't read key value pairs\n");
    return EXIT_FAILURE;
  }
 //count from 2 to argc (call the number you count i)
  for(size_t i=2; i<argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv); 
    //compute the output file name from argv[i] (call this outName)
    char * outName = malloc((strlen(argv[i])+8) * sizeof(*outName));
    strcpy(outName, argv[i]);
    strcat(outName, ".counts");
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w+");
    if(f == NULL) {
      perror("can't open .count file");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if(fclose(f) != 0) {
      fprintf(stderr, "can't write to the file\n");
    }
    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }

 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
