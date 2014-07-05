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

Vector3d absolute_to_spherical(Vector3d a) {
  /* Absolute coordinates: a(0) = x, a(1) = y, a(2) = z. */

  /* Spherical coordinates. */
  Vector3d s;

  /* Radius (r). Between zero and +infinity. */
  s(0) = a.norm();

  /* phi */
  s(1) = atan2(a(2), a(0)); // y -> z

  /* theta */
  s(2) = acos(a(1) / s(0)); // z -> y

  return s;
}


Vector3d spherical_to_absolute(Vector3d s) {
  /* Spherical coordinates: s(0) = r, s(1) = phi, s(2) = theta. */

  /* Absolute coordinates. */
  Vector3d a;

  /* x */
  a(0) = s(0) * sin(s(2)) * cos(s(1));

  /* z */
  a(2) = s(0) * sin(s(2)) * sin(s(1)); // a(2) --> a(1)

  /* y */
  a(1) = s(0) * cos(s(2));  // a(1) --> a(2)

  return a;
}
