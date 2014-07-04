#ifndef __UTILITIES__
#define __UTILITIES__

#include <cstdlib>
#include <time.h>

const double kEpsilonShadows = 1.0e-3; /**< Small constant for shadows. */
const double kEpsilon        = 1.0e-5; /**< Small constant. */
const double kHugeValue      = 1.0e10; /**< Huge constant. */

const double kKa = 0.20;  /**< Ambient Constant. */
const double kKd = 0.80;  /**< Diffuse Constant. */
const double kKs = 0.12;  /**< Specular Constant. */
const double kExp = 10.0; /**< Specular Exponent. */
const double kKr = 0.75;  /**< Reflective Constant. */

enum Ray_t { PRIMARY_RAY, SHADOW_RAY };

void generate_random_seed(); /**< Generate a new seed for randomness. */
int get_random_int(int begin = 0, int end = RAND_MAX); /**< Return a random integer from begin to end, or from 0 to RAND_MAX. */
double get_random_double(double begin = 0.0, double end = 1.0); /**< Return a random double from begin to end, or from 0.0 to 1.0. */

#endif
