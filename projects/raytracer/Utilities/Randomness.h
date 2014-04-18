#include <cstdlib>
#include <cmath>

void set_rand_seed(const int);

/** Return a random integer from 0 to RAND_MAX */
int rand_int();

/** Return a random integer from begin to end */
int rand_int(const int begin, const int end);

/** Return a random double from 0.0 to 1.0 */
double rand_double();

/** Return a random double from begin to end */
double rand_double(const double begin, const double end);

/** a == b? Tolerance: eps */
bool compareDouble(const double a, const double b, const double eps);

/** a == b? */
bool compareDouble(const double a, const double b);
