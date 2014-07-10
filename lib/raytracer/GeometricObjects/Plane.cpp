#include "Plane.h"

namespace Raytracer {
  Plane::Plane(const Vector3d& point, Vector3d normal) :
    GeometricObject(),
    point(point),
    normal(normal) {
    normal.normalize();
  }


  Plane::Plane(const Plane& plane) :
    GeometricObject(plane),
    point(plane.point),
    normal(plane.normal) {
  }


  Plane::~Plane() {}


  Plane *Plane::clone() const {
    return new Plane(*this);
  }


  bool Plane::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

    double t = (point - ray.origin).dot(normal) / ray.direction.dot(normal);

    if (t > kEpsilonShadows) {
      tmin = t;

      if (type == PRIMARY_RAY) {
        sr.normal = normal;
        sr.local_hit_point = ray.origin + t * ray.direction;
      }
      return true;
    }
    return false;
  }
}
