#include "Rectangle.h"

Rectangle::Rectangle() :
  GeometricObject(),
  p0(-1, 0, -1),
  a(0, 0, 2), b(2, 0, 0),
  a_len_squared(4.0),
  b_len_squared(4.0),
  normal(0, 1, 0),
  area(4.0),
  inv_area(0.25),
  sampler_ptr(NULL)
{}


// this constructs the normal
Rectangle::Rectangle(const Vector3d& _p0, const Vector3d& _a, const Vector3d& _b) :
  GeometricObject(),
  p0(_p0),
  a(_a),
  b(_b),
  a_len_squared(_a.norm() * _a.norm()),
  b_len_squared(_b.norm() * _b.norm()),
  area(a.norm() * b.norm()),
  inv_area(1.0 / area),
  sampler_ptr(NULL)
{
  normal = a.cross(b);
  normal.normalize();
}

// this has the normal as an argument
Rectangle::Rectangle(const Vector3d& _p0, const Vector3d& _a, const Vector3d& _b, const Vector3d& n) :
  GeometricObject(),
  p0(_p0),
  a(_a),
  b(_b),
  a_len_squared(_a.norm() * _a.norm()),
  b_len_squared(_b.norm() * _b.norm()),
  area(a.norm() * b.norm()),
  inv_area(1.0 / area),
  normal(n),
  sampler_ptr(NULL)
{
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
  normal(r.normal),
  area(r.area),
  inv_area(r.inv_area)
{
  if(r.sampler_ptr)
    sampler_ptr = r.sampler_ptr->clone();
  else
    sampler_ptr = NULL;
}


Rectangle& Rectangle::operator= (const Rectangle& rhs) {
  if (this != &rhs) {
    GeometricObject::operator=(rhs);
    p0        = rhs.p0;
    a       = rhs.a;
    b       = rhs.b;
    a_len_squared = rhs.a_len_squared;
    b_len_squared = rhs.b_len_squared;
    area      = rhs.area;
    inv_area    = rhs.inv_area;
    normal      = rhs.normal;

    if (sampler_ptr) {
      delete sampler_ptr;
      sampler_ptr = NULL;
    }
    if (rhs.sampler_ptr)
      sampler_ptr= rhs.sampler_ptr->clone();
  }

  return *this;
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


bool Rectangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  double t = (p0 - ray.o).dot(normal) / (ray.d.dot(normal));

  if (t <= kEpsilonShadows)
    return false;

  Vector3d p = ray.o + t * ray.d;
  Vector3d d = p - p0;

  double ddota = d.dot(a);

  if (ddota < 0.0 || ddota > a_len_squared)
    return false;

  double ddotb = d.dot(b);

  if (ddotb < 0.0 || ddotb > b_len_squared)
    return false;

  tmin        = t;
  sr.normal   = normal;
  sr.local_hit_point  = p;

  return true;
}

bool Rectangle::shadow_hit(const Ray &ray, double &tmin) const {
  double t = (p0 - ray.o).dot(normal) / (ray.d.dot(normal));

  if (t <= kEpsilonShadows)
    return false;

  Vector3d p = ray.o + t * ray.d;
  Vector3d d = p - p0;

  double ddota = d.dot(a);

  if (ddota < 0.0 || ddota > a_len_squared)
    return false;

  double ddotb = d.dot(b);

  if (ddotb < 0.0 || ddotb > b_len_squared)
    return false;

  tmin = t;
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
