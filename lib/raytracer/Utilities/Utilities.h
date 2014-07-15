#ifndef _UTILITIES_MINE_
#define _UTILITIES_MINE_

#include <cstdlib>
#include <time.h>
#include <Eigen/Dense>
using Eigen::Vector3d;

/** Small constant, for shadows. */
const double kEpsilonShadows = 1.0e-3;

/** Small constant. */
const double kEpsilon = 1.0e-6;

/** Huge constant. */
const double kHugeValue = 1.0e10;

/** Ambient Constant. Should be from 0.0 to 1.0. */
const double kKa = 0.20;

/** Diffuse Constant. Should be from 0.0 to 1.0. */
const double kKd = 0.70;

/** Specular Constant. Should be from 0.0 to 1.0. */
const double kKs = 0.10;

/** Specular Exponent from cosine. A reasonable number is from 1.0 to 20.0. */
const double kExp = 12.0;

/** Reflective Constant. */
const double kKr = 0.75; 

/** Generate a new seed for randomness. */
void generate_random_seed();

/** Return a random integer from begin to end, or from 0 to RAND_MAX. */
int get_random_int(int begin = 0, int end = RAND_MAX);

/** Return a random double from begin to end, or from 0.0 to 1.0. */
double get_random_double(double begin = 0.0, double end = 1.0);

/** Return true if the argument is sufficiently near zero. */
bool is_zero(const double);

/**
 *  Utility function to find quadric roots. Coefficients are passed
 *  like this:
 *
 *  c[0] + c[1]*x + c[2]*x^2 = 0
 *
 *  The function return the number of non-complex roots and
 *  put the values into the s array.
 *
 *  Author: Jochen Schwarze <schwarze@isa.de>
 */
int solve_quadric(double c[3], double s[2]);

/**
 *  Utility function to find cubic roots. Coefficients are passed
 *  like this:
 *
 *  c[0] + c[1]*x + c[2]*x^2 + c[3]*x^3 = 0
 *
 *  The function return the number of non-complex roots and
 *  put the values into the s array.
 *
 *  Author: Jochen Schwarze <schwarze@isa.de>
 */
int solve_cubic(double c[4], double s[3]);

/**
 *  Utility function to find quartic roots. Coefficients are passed
 *  like this:
 *
 *  c[0] + c[1]*x + c[2]*x^2 + c[3]*x^3 + c[4]*x^4 = 0
 *
 *  The function return the number of non-complex roots and
 *  put the values into the s array.
 *
 *  Author: Jochen Schwarze <schwarze@isa.de>
 */
int solve_quartic(double c[5], double s[4]);

#endif // _UTILITIES_MINE_
