#ifndef __UTILITIES__
#define __UTILITIES__

#include <cstdlib>
#include <time.h>
#include <Eigen/Dense>
using Eigen::Vector3d;

/** Small constant for shadows. */
const double kEpsilonShadows = 1.0e-3;

/** Small constant. */
const double kEpsilon = 1.0e-5;

/** Huge constant. */
const double kHugeValue = 1.0e10;

/** Ambient Constant. Should be from 0.0 to 1.0. */
const double kKa = 0.20;

/** Diffuse Constant. Should be from 0.0 to 1.0. */
const double kKd = 0.70;

/** Specular Constant. Should be from 0.0 to 1.0. */
const double kKs = 0.10;

/** Specular Exponent from cosine. A reasonable number is from 1.0 to 20.0. */
const double kExp = 10.0;

/** Reflective Constant. */
const double kKr = 0.75; 

/** Generate a new seed for randomness. */
void generate_random_seed();

/** Return a random integer from begin to end, or from 0 to RAND_MAX. */
int get_random_int(int begin = 0, int end = RAND_MAX);

/** Return a random double from begin to end, or from 0.0 to 1.0. */
double get_random_double(double begin = 0.0, double end = 1.0);

/** Convert from carthesian coordinates to spherical coordinates. */
Vector3d carthesian_to_spherical(Vector3d);

/** Convert from spherical coordinates to carthesian coordinates. */
Vector3d spherical_to_carthesian(Vector3d);

#endif
