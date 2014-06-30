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


  Plane& Plane::operator= (const Plane& rhs) {
    if (this != &rhs) {
      GeometricObject::operator= (rhs);
      point = rhs.point;
      normal = rhs.normal;
    }
    return *this;
  }


  Plane::~Plane() {}


  Plane *Plane::clone() const {
    return new Plane(*this);
  }


  bool Plane::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

    double t = (point - ray.o).dot(normal) / ray.d.dot(normal);

    if (t > kEpsilonShadows) {
      tmin = t;
      if (type == PRIMARY_RAY) {
	sr.normal = normal;
	sr.local_hit_point = ray.o + t * ray.d;
      }
      return true;
    }
    return false;
  }
}
