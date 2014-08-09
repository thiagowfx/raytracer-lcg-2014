#include "Ray.h"

namespace Raytracer {
  Ray::Ray () {
    origin = Vector3d::Zero();
    direction = Vector3d::Zero();
  }


  Ray::~Ray () {}


  Ray::Ray (const Vector3d& origin, const Vector3d& direction) :
    origin(origin),
    direction(direction) {}


  Ray::Ray (const Ray& ray) :
    origin(ray.origin),
    direction(ray.direction) {}


  std::ostream& operator<<(std::ostream& os, const Ray& r) {
    os << r.origin;
    os << " ";
    os << r.direction;
    return os;
  }


  bool Ray::operator==(const Ray& o) const {
    return
      origin == o.origin &&
      direction == o.direction;
  }
}
