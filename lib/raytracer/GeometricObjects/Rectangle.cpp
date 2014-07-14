#include "Rectangle.h"

namespace Raytracer {
  Rectangle::Rectangle(const Vector3d& p0, const Vector3d& a, const Vector3d& b) :
    GeometricObject(),
    p0(p0),
    a(a),
    b(b),
    area(a.norm() * b.norm()),
    sampler_ptr(NULL) {
    this->normal = -a.cross(b).normalized();
  }

  Rectangle::Rectangle(const Vector3d& p0, const Vector3d& a, const Vector3d& b, const Vector3d& normal) :
    GeometricObject(),
    p0(p0),
    a(a),
    b(b),
    normal(normal),
    area(a.norm() * b.norm()),
    sampler_ptr(NULL) {
    this->normal.normalize();
  }


  Rectangle* Rectangle::clone() const {
    return new Rectangle(*this);
  }


  Rectangle::Rectangle (const Rectangle& r) :
    GeometricObject(r),
    p0(r.p0),
    a(r.a),
    b(r.b),
    normal(r.normal),
    area(r.area) {
    if(r.sampler_ptr)
      sampler_ptr = r.sampler_ptr->clone();
    else
      sampler_ptr = NULL;
  }


  Rectangle::~Rectangle () {
    if (sampler_ptr) {
      delete sampler_ptr;
      sampler_ptr = NULL;
    }
  }

  // BBox Rectangle::get_bounding_box() {
  //   double delta = 0.0001;
  //   return(BBox(min(p0(0), p0(0) + a(0) + b(0)) - delta, max(p0(0), p0(0) + a(0) + b(0)) + delta,
  //               min(p0(1), p0(1) + a(1) + b(1)) - delta, max(p0(1), p0(1) + a(1) + b(1)) + delta,
  //               min(p0(2), p0(2) + a(2) + b(2)) - delta, max(p0(2), p0(2) + a(2) + b(2)) + delta));
  // }


  bool Rectangle::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

    double t = (p0 - ray.origin).dot(normal) / (ray.direction.dot(normal));

    if (t <= kEpsilonShadows)
      return false;

    Vector3d p = ray.origin + t * ray.direction;
    Vector3d d = p - p0;

    double ddota = d.dot(a);
    if (ddota < 0.0 || ddota > a.squaredNorm())
      return false;

    double ddotb = d.dot(b);
    if (ddotb < 0.0 || ddotb > b.squaredNorm())
      return false;

    tmin = t;
    if (type == PRIMARY_RAY) {
      sr.normal = normal;
      sr.local_hit_point = p;
    }
    return true;
  }


  void Rectangle::set_sampler(Sampler* sampler) {
    sampler_ptr = sampler;
  }


  Vector3d Rectangle::sample() {
    Vector2d sample_point = sampler_ptr->sample_unit_square();
    return (p0 + sample_point(0) * a + sample_point(1) * b);
  }


  Vector3d Rectangle::get_normal(const Vector3d& p) {
    return normal;
  }


  double Rectangle::pdf(ShadeRec& sr) {
    return 1.0 / area;
  }
}
