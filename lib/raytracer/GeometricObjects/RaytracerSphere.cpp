#include "RaytracerSphere.h"

RaytracerSphere::RaytracerSphere(Vector3d c, double r) :
  GeometricObject(),
  center(c),
  radius(r)
{}


RaytracerSphere::RaytracerSphere (const RaytracerSphere& sphere) :
  GeometricObject(sphere),
  center(sphere.center),
  radius(sphere.radius)
{}


RaytracerSphere& RaytracerSphere::operator= (const RaytracerSphere& rhs) {
  if (this != &rhs) {
    GeometricObject::operator=(rhs);
    center = rhs.center;
    radius = rhs.radius;
  }
  return *this;
}


RaytracerSphere::~RaytracerSphere() {}


RaytracerSphere* RaytracerSphere::clone() const {
  return new RaytracerSphere(*this);
}


bool RaytracerSphere::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
  if (type == SHADOW_RAY && !shadows)
    return false;

  double   t;
  Vector3d temp = ray.o - center;
  double   a    = ray.d.dot(ray.d);
  double   b    = 2.0 * temp.dot(ray.d);
  double   c    = temp.dot(temp) - radius * radius;
  double   disc = b * b - 4.0 * a * c;

  if (disc < 0.0) {
    return false;
  }

  else {
    double e = sqrt(disc);
    double denom = 2.0 * a;
    t = (-b - e) / denom; /* smaller root */

    if (t > kEpsilonShadows) {
      tmin = t;
      if (type == PRIMARY_RAY) {
	sr.normal 	 = (temp + t * ray.d) / radius;
	sr.local_hit_point = ray.o + t * ray.d;
      }
      return true;
    }

    t = (-b + e) / denom; /* larger root */

    if (t > kEpsilonShadows) {
      tmin = t;
      if (type == PRIMARY_RAY) {
	sr.normal   = (temp + t * ray.d) / radius;
	sr.local_hit_point = ray.o + t * ray.d;
      }
      return true;
    }
  }
  return false;
}
