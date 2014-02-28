#include "Randomness.h"

void set_rand_seed(const int seed) {
  srand(seed);
}


int rand_int() {
  return rand();
}


float rand_float() {
  return float(rand()) / float(RAND_MAX) ;
}
