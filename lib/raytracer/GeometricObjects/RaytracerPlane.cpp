#include "RaytracerPlane.h"

RaytracerPlane::RaytracerPlane(const Vector3d& point, Vector3d normal) :
  GeometricObject(),
  point(point),
  normal(normal) {
  normal.normalize();
}


RaytracerPlane::RaytracerPlane(const RaytracerPlane& plane) :
  GeometricObject(plane),
  point(plane.point),
  normal(plane.normal) {
}


RaytracerPlane& RaytracerPlane::operator= (const RaytracerPlane& rhs) {
  if (this != &rhs) {
    GeometricObject::operator= (rhs);
    point = rhs.point;
    normal = rhs.normal;
  }
  return *this;
}


RaytracerPlane::~RaytracerPlane() {}


RaytracerPlane *RaytracerPlane::clone() const {
  return new RaytracerPlane(*this);
}


bool RaytracerPlane::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
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
