#include "PartSphere.h"

namespace Raytracer {
  PartSphere::PartSphere(const double radius, const double min_polar_angle, double max_polar_angle, double min_azimuth_angle, double max_azimuth_angle) :
    GeometricObject(),
    radius(radius),
    min_polar_angle(min_polar_angle),
    max_polar_angle(max_polar_angle),
    min_azimuth_angle(min_azimuth_angle),
    max_azimuth_angle(max_azimuth_angle)
  {}


  PartSphere::PartSphere (const PartSphere& sphere) :
    GeometricObject(sphere),
    radius(sphere.radius),
    min_polar_angle(sphere.min_polar_angle),
    max_polar_angle(sphere.max_polar_angle),
    min_azimuth_angle(sphere.min_azimuth_angle),
    max_azimuth_angle(sphere.max_azimuth_angle)
  {}


  PartSphere::~PartSphere() {}


  PartSphere* PartSphere::clone() const {
    return new PartSphere(*this);
  }


  bool PartSphere::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

    double t;
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * ray.origin.dot(ray.direction);
    double c = ray.origin.dot(ray.origin) - radius * radius;
    double disc = b * b - 4.0 * a * c;
    Vector3d local_hit_point;
    double azimuth_hit_angle;

    if (disc < 0.0) {
      return false;
    }

    else {
      double e = sqrt(disc);
      double denom = 2.0 * a;
      /* Smaller root. */
      t = (-b - e) / denom;

      if (t > kEpsilonShadows) {
        local_hit_point = ray.origin + t * ray.direction;
        azimuth_hit_angle = get_azimuth_angle(local_hit_point);

        if (min_azimuth_angle <= azimuth_hit_angle && azimuth_hit_angle <= max_azimuth_angle) {
	  // if (min_azimuth_angle <= azimuth_hit_angle && azimuth_hit_angle <= max_azimuth_angle && (radius * cos(min_polar_angle)) <= local_hit_point(1) && local_hit_point(1) <= (radius * cos(max_polar_angle))) {
          tmin = t;
          if (type == PRIMARY_RAY) {
            sr.normal = (ray.origin + t * ray.direction) / radius;
            sr.local_hit_point = local_hit_point;
          }
          return true;
        }
      }

      /* Larger root. */
      t = (-b + e) / denom;

      if (t > kEpsilonShadows) {
        local_hit_point = ray.origin + t * ray.direction;
        azimuth_hit_angle = get_azimuth_angle(local_hit_point);

        if (min_azimuth_angle <= azimuth_hit_angle && azimuth_hit_angle <= max_azimuth_angle) {
	  // if (min_azimuth_angle <= azimuth_hit_angle && azimuth_hit_angle <= max_azimuth_angle && (radius * cos(min_polar_angle)) <= local_hit_point(1) && local_hit_point(1) <= (radius * cos(max_polar_angle))) {
          tmin = t;
          if (type == PRIMARY_RAY) {
            sr.normal = (ray.origin + t * ray.direction) / radius;
            sr.local_hit_point = local_hit_point;
          }
          return true;
        }
      }
    }
    return false;
  }


  double PartSphere::get_azimuth_angle(const Vector3d& p) const {
    double phi = atan2(p(0),p(2));
    if (phi < 0.0) {
      phi += 2 * M_PI;
    }
    return phi;
  }
}
