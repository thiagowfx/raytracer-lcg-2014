#include "Ray.h"

Ray::Ray () {}


Ray::~Ray () {}


Ray::Ray (const Vector3d& origin, const Vector3d& dir) :
  o(origin),
  d(dir)
{}


Ray::Ray (const Ray& ray) :
  o(ray.o),
  d(ray.d)
{}


Ray& Ray::operator= (const Ray& rhs) {
  if (this != &rhs) {
    o = rhs.o;
    d = rhs.d;
  }
  return *this;
}
