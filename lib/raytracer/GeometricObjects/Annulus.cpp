#include "Annulus.h"

namespace Raytracer {
  Annulus::Annulus(const Vector3d& center, double inner_radius, double outer_radius, const Vector3d& normal) :
    GeometricObject(),
    center(center),
    inner_radius(inner_radius),
    outer_radius(outer_radius),
    normal(normal) {
    this->normal.normalize();
  }


  Annulus::Annulus(const Annulus& a) :
    GeometricObject(a),
    center(a.center),
    inner_radius(a.inner_radius),
    outer_radius(a.outer_radius),
    normal(a.normal)
  {}


  Annulus::~Annulus() {}


  Annulus* Annulus::clone() const {
    return new Annulus(*this);
  }


  bool Annulus::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

    double t = (center - ray.origin).dot(normal) / ray.direction.dot(normal);
    Vector3d p = ray.origin + t * ray.direction;
    double norm = (p - center).norm();
    
    if ( inner_radius < norm && norm < outer_radius) {
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
