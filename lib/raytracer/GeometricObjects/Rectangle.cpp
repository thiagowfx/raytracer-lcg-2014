#include "Rectangle.h"

namespace Raytracer {
  // this constructs the normal
  Rectangle::Rectangle(const Vector3d& p0, const Vector3d& a, const Vector3d& b) :
    GeometricObject(),
    p0(p0),
    a(a),
    b(b),
    a_len_squared(a.norm() * a.norm()),
    b_len_squared(b.norm() * b.norm()),
    area(a.norm() * b.norm()),
    inv_area(1.0 / area),
    sampler_ptr(NULL) {
    normal = -a.cross(b).normalized();
  }

  // this has the normal as an argument
  Rectangle::Rectangle(const Vector3d& p0, const Vector3d& a, const Vector3d& b, const Vector3d& n) :
    GeometricObject(),
    p0(p0),
    a(a),
    b(b),
    a_len_squared(a.norm() * a.norm()),
    b_len_squared(b.norm() * b.norm()),
    area(a.norm() * b.norm()),
    inv_area(1.0 / area),
    normal(n),
    sampler_ptr(NULL) {
    normal.normalize();
  }


  Rectangle* Rectangle::clone() const {
    return new Rectangle(*this);
  }


  Rectangle::Rectangle (const Rectangle& r) :
    GeometricObject(r),
    p0(r.p0),
    a(r.a),
    b(r.b),
    a_len_squared(r.a_len_squared),
    b_len_squared(r.b_len_squared),
    area(r.area),
    inv_area(r.inv_area),
    normal(r.normal) {
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

    if (ddota < 0.0 || ddota > a_len_squared)
      return false;

    double ddotb = d.dot(b);

    if (ddotb < 0.0 || ddotb > b_len_squared)
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
    return inv_area;
  }
}
