#include "Sphere.h"

namespace Raytracer {
  Sphere::Sphere(Vector3d c, double r) :
    GeometricObject(),
    center(c),
    radius(r)
  {}


  Sphere::Sphere (const Sphere& sphere) :
    GeometricObject(sphere),
    center(sphere.center),
    radius(sphere.radius)
  {}


  Sphere::~Sphere() {}


  Sphere* Sphere::clone() const {
    return new Sphere(*this);
  }


  bool Sphere::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

    double   t;
    Vector3d temp = ray.origin - center;
    double   a    = ray.direction.dot(ray.direction);
    double   b    = 2.0 * temp.dot(ray.direction);
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
    sr.normal = (temp + t * ray.direction) / radius;
    sr.local_hit_point = ray.origin + t * ray.direction;
	}
	return true;
      }

      t = (-b + e) / denom; /* larger root */

      if (t > kEpsilonShadows) {
	tmin = t;
	if (type == PRIMARY_RAY) {
    sr.normal   = (temp + t * ray.direction) / radius;
    sr.local_hit_point = ray.origin + t * ray.direction;
	}
	return true;
      }
    }
    return false;
  }
}
