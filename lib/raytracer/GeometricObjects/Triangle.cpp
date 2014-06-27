#include "Triangle.h"

Triangle::Triangle () :
  GeometricObject(),
  v0(0, 0, 0),
  v1(0,0,1),
  v2(1,0,0),
  normal(0, 1, 0)
{}

Triangle::Triangle (const Vector3d& a, const Vector3d& b, const Vector3d& c) :
  GeometricObject(),
  v0(a),
  v1(b),
  v2(c)
{
  compute_normal();
}


Triangle* Triangle::clone() const {
  return new Triangle(*this);
}


Triangle::Triangle (const Triangle& triangle) :
  GeometricObject(triangle),
  v0(triangle.v0),
  v1(triangle.v1),
  v2(triangle.v2),
  normal(triangle.normal)
{}


Triangle& Triangle::operator= (const Triangle& rhs) {
  if (this != &rhs) {
    GeometricObject::operator=(rhs);
    v0        = rhs.v0;
    v1        = rhs.v1;
    v2        = rhs.v2;
    normal    = rhs.normal;
  }

  return *this;
}


Triangle::~Triangle () {}



void Triangle::compute_normal() {
  normal = (v1 - v0).cross(v2 - v0);
  normal.normalize();
}


// BBox Triangle::get_bounding_box() {
//   double delta = 0.000001;

//   return (BBox(min(min(v0(0), v1(0)), v2(0)) - delta, max(max(v0(0), v1(0)), v2(0)) + delta,
//                min(min(v0(1), v1(1)), v2(1)) - delta, max(max(v0(1), v1(1)), v2(1)) + delta,
//                min(min(v0(2), v1(2)), v2(2)) - delta, max(max(v0(2), v1(2)), v2(2)) + delta));
// }


bool Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  double a = v0(0) - v1(0), b = v0(0) - v2(0), c = ray.d(0), d = v0(0) - ray.o(0);
  double e = v0(1) - v1(1), f = v0(1) - v2(1), g = ray.d(1), h = v0(1) - ray.o(1);
  double i = v0(2) - v1(2), j = v0(2) - v2(2), k = ray.d(2), l = v0(2) - ray.o(2);

  double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
  double q = g * i - e * k, s = e * j - f * i;
  double inv_denom  = 1.0 / (a * m + b * q + c * s);

  double e1 = d * m - b * n - c * p;
  double beta = e1 * inv_denom;

  if (beta < 0.0)
    return false;

  double r = r = e * l - h * i;
  double e2 = a * n + d * q + c * r;
  double gamma = e2 * inv_denom;

  if (gamma < 0.0)
    return false;

  if (beta + gamma > 1.0)
    return false;

  double e3 = a * p - b * r + d * s;
  double t = e3 * inv_denom;

  if (t < kEpsilonShadows)
    return false;

  tmin              = t;
  sr.normal             = normal;
  sr.local_hit_point    = ray.o + t * ray.d;
  return true;
}


bool Triangle::shadow_hit(const Ray& ray, double& tmin) const {
  if(!shadows)
    return false;

  double a = v0(0) - v1(0), b = v0(0) - v2(0), c = ray.d(0), d = v0(0) - ray.o(0);
  double e = v0(1) - v1(1), f = v0(1) - v2(1), g = ray.d(1), h = v0(1) - ray.o(1);
  double i = v0(2) - v1(2), j = v0(2) - v2(2), k = ray.d(2), l = v0(2) - ray.o(2);

  double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
  double q = g * i - e * k, s = e * j - f * i;
  double inv_denom  = 1.0 / (a * m + b * q + c * s);

  double e1 = d * m - b * n - c * p;
  double beta = e1 * inv_denom;

  if (beta < 0.0)
    return false;

  double r = e * l - h * i;
  double e2 = a * n + d * q + c * r;
  double gamma = e2 * inv_denom;

  if (gamma < 0.0)
    return false;

  if (beta + gamma > 1.0)
    return false;

  double e3 = a * p - b * r + d * s;
  double t = e3 * inv_denom;

  if (t < kEpsilonShadows)
    return false;

  tmin = t;
  return true;
}
