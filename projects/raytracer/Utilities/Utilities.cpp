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

double rand_double(const double begin, const double end) {
  return begin + ( rand_double() * (end - begin) );
}

bool compareDouble(const double a, const double b, const double eps) {
    return fabs(a - b) < eps;
}


bool compareDouble(const double a, const double b) {
    return fabs(a - b) < 1.0e-6;
}
