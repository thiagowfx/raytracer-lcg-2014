#include "Disk.h"

namespace Raytracer {
  Disk::Disk(const Vector3d& center, double radius, const Vector3d& normal) :
    GeometricObject(),
    center(center),
    radius(radius),
    normal(normal) {
    this->normal.normalize();
  }


  Disk::Disk(const Disk& disk) :
    GeometricObject(disk),
    center(disk.center),
    radius(disk.radius),
    normal(disk.normal)
  {}


  Disk::~Disk() {}


  Disk* Disk::clone() const {
    return new Disk(*this);
  }


  bool Disk::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

    double t = (center - ray.origin).dot(normal) / ray.direction.dot(normal);
    Vector3d p = ray.origin + t * ray.direction;

    if ( (p - center).norm() < radius) {
      tmin = t;

      if (type == PRIMARY_RAY) {
        sr.normal = normal;
        sr.local_hit_point = p;
      }
      return true;
    }
    else {
      return false;
    }
  }
}
