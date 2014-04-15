#include "Randomness.h"

void set_rand_seed(const int seed) {
  srand(seed);
}


int rand_int() {
  return rand();
}


int rand_int(const int begin, const int end) {
  return begin + ( rand_int() % (end - begin + 1) );
}


double rand_double() {
  return double(rand()) / double(RAND_MAX);
}


double rand_double(const double begin, const double end) {
  return begin + ( rand_double() * (end - begin) );
}
