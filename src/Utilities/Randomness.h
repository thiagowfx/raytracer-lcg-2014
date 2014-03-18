#include <cstdlib>

void set_rand_seed(const int seed);
/* Returns a random integer from 0 to RAND_MAX */
int rand_int();
/* Returns a random integer from begin to end */
int rand_int(const int begin, const int end);
/* Returns a random float from 0 to 1 */
float rand_float();
/* Returns a random float from begin to end */
float rand_float(const float begin, const float end);
