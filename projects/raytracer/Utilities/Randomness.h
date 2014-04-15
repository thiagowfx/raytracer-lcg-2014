#include <cstdlib>

void set_rand_seed(const int seed);
/* Returns a random integer from 0 to RAND_MAX */
int rand_int();
/* Returns a random integer from begin to end */
int rand_int(const int begin, const int end);
/* Returns a random double from 0 to 1 */
double rand_double();
/* Returns a random double from begin to end */
double rand_double(const double begin, const double end);
