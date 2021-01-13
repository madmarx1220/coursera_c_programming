#include <stdlib.h>
#include <stdio.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if(expected_ans != power(x, y)) {
    printf("This function does not pass the test case for x=%u, y=%u\n", x, y);
    exit(EXIT_FAILURE);
  }
}

int main () {
  run_check(1,0,1);
  run_check(0,0,1);
  run_check(0,1,0);
  run_check(5,5,3125);
  run_check(2.2,2.2,4);
  run_check(2.0,1.0,2);
  run_check(10,1, 10);
  run_check(10,5,100000);
	    
  return EXIT_SUCCESS;
}
