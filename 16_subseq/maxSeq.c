#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  size_t num = 1;
  size_t largestNum = 1;
  for (int i = 1; i < n; i++) {
    if (array[i] > array[i-1]) {
      num++;
    }
    else {
      if (largestNum < num) {
	largestNum = num;
      }
      num = 1;
    }
  }
  if (largestNum < num) {
    largestNum = num;
  }
  return largestNum;
}
