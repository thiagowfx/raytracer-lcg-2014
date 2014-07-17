#include "Ray.h"

namespace Raytracer {
  Ray::Ray () {}


  Ray::~Ray () {}


  Ray::Ray (const Vector3d& origin, const Vector3d& direction) :
    origin(origin),
    direction(direction)
  {}


  Ray::Ray (const Ray& ray) :
    origin(ray.origin),
    direction(ray.direction)
  {}
}
