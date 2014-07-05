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

Vector3d carthesian_to_spherical(Vector3d c) {
  /* Carthesian coordinates: c(0) = x, c(1) = y, c(2) = z. */

  /* Spherical coordinates. */
  Vector3d s;

  /* Radius (r). Between zero and +infinity. */
  s(0) = c.norm();

  /* phi */
  s(1) = atan2(c(2), c(0)); // y -> z

  /* theta */
  s(2) = acos(c(1) / s(0)); // z -> y

  return s;
}


Vector3d spherical_to_carthesian(Vector3d s) {
  /* Spherical coordinates: s(0) = r, s(1) = phi, s(2) = theta. */

  /* Carthesian coordinates. */
  Vector3d c;

  /* x */
  c(0) = s(0) * sin(s(2)) * cos(s(1));

  /* z */
  c(2) = s(0) * sin(s(2)) * sin(s(1)); // c(2) --> c(1)

  /* y */
  c(1) = s(0) * cos(s(2));  // c(1) --> c(2)

  return c;
}
