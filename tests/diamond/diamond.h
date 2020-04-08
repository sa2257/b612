//Standard Libraries
#include <stdio.h>
#include <stdlib.h>

//Define compute data type
#define TYPE double

//Define the input range to operate over
#define MIN 0.
#define MAX 1.0

//Set number of iterations to execute
#define MAX_ITERATION 1

void diamond(TYPE *in1, TYPE *in2, TYPE *out);
////////////////////////////////////////////////////////////////////////////////
// Test harness interface code.

struct bench_args_t {
  TYPE* in1;
  TYPE* in2;
  TYPE* out;
};
