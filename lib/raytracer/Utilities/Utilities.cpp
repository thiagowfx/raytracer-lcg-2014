#include "Utilities.h"

void set_rand_seed(int seed) {
  srand(seed);
}

int rand_int() {
  return rand();
}

int rand_int(int begin, int end) {
  return begin + ( rand_int() % (end - begin + 1) );
}

double rand_double() {
  return double(rand()) / double(RAND_MAX);
}

double rand_double(double begin, double end) {
  return begin + ( rand_double() * (end - begin) );
}
