#include "Randomness.h"

void set_rand_seed(const int seed) {
  srand(seed);
}


int rand_int() {
  return rand();
}


int rand_int(int begin, int end) {
  return begin + ( rand_int() % (end - begin + 1) );
}


float rand_float() {
  return float(rand()) / float(RAND_MAX);
}


float rand_float(float begin, float end) {
  return begin + ( rand_float() * (end - begin) );
}
