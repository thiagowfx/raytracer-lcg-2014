#include "Utilities.h"

void generate_random_seed() {
  srand(time(NULL));
}


int get_random_int(int begin, int end) {
  return begin + (rand() % (end - begin + 1));
}


double get_random_double(double begin, double end) {
  return begin + (double(rand()/double(RAND_MAX)) * (end - begin));
}
