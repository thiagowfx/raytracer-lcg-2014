#include "Ray.h"

Ray::Ray () {}


Ray::~Ray () {}


Ray::Ray (const Vector3d& origin, const Vector3d& direction) :
  o(origin),
  d(direction)
{}


Ray::Ray (const Ray& ray) :
  o(ray.o),
  d(ray.d)
{}
