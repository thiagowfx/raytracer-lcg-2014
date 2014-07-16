#include "PartOpenCylinder.h"

namespace Raytracer {
  PartOpenCylinder::PartOpenCylinder(const double ybottom, const double ytop, const double radius, const double min_angle, const double max_angle) :
    OpenCylinder(ybottom, ytop, radius),
    min_angle(min_angle),
    max_angle(max_angle)
  {}


  PartOpenCylinder::PartOpenCylinder(const PartOpenCylinder& p) :
    OpenCylinder(p),
    min_angle(p.min_angle),
    max_angle(p.max_angle)
  {}


  PartOpenCylinder* PartOpenCylinder::clone() const {
    return new PartOpenCylinder (*this);
  }


  PartOpenCylinder::~PartOpenCylinder() {}


  bool PartOpenCylinder::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

    double t;
    double ox = ray.origin(0);
    double oy = ray.origin(1);
    double oz = ray.origin(2);
    double dx = ray.direction(0);
    double dy = ray.direction(1);
    double dz = ray.direction(2);
    double a = dx * dx + dz * dz;
    double b = 2.0 * (ox * dx + oz * dz);
    double c = ox * ox + oz * oz - radius * radius;
    double disc = b * b - 4.0 * a * c;
    Vector3d local_hit_point;
    double phi_hit_point;

    if (disc < 0.0)
      return false;
    else {
      double e = sqrt(disc);
      double denom = 2.0 * a;
      /* Smaller root. */
      t = (-b - e) / denom;

      if (t > kEpsilon) {
        double yhit = oy + t * dy;
        local_hit_point = ray.origin + t * ray.direction;
        phi_hit_point = get_azimuth_angle(local_hit_point);

        if (yhit > ybottom && yhit < ytop && min_angle <= phi_hit_point && phi_hit_point <= max_angle) {
          tmin = t;

          if (type == PRIMARY_RAY) {
            sr.normal = Vector3d((ox + t * dx) / radius, 0.0, (oz + t * dz) / radius);
            /* Test for hitting from inside. */
            if (-ray.direction.dot(sr.normal) < 0.0) {
              sr.normal = -sr.normal;
            }
            sr.local_hit_point = local_hit_point;
          }
          return true;
        }
      }

      /* Larger root. */
      t = (-b + e) / denom;

      if (t > kEpsilon) {
        double yhit = oy + t * dy;
        local_hit_point = ray.origin + t * ray.direction;
        phi_hit_point = get_azimuth_angle(local_hit_point);

	if (yhit > ybottom && yhit < ytop && min_angle <= phi_hit_point && phi_hit_point <= max_angle) {
          tmin = t;

          if (type == PRIMARY_RAY) {
            sr.normal = Vector3d((ox + t * dx) / radius, 0.0, (oz + t * dz) / radius);
            /* Test for hitting inside surface. */
            if (-ray.direction.dot(sr.normal) < 0.0)
              sr.normal = -sr.normal;
            sr.local_hit_point = local_hit_point;
          }
          return true;
        }
      }
    }

    return false;
  }


  double PartOpenCylinder::get_azimuth_angle(const Vector3d& p) const {
    double phi = atan2(p(0),p(2));
    if (phi < 0.0) {
      phi += 2 * M_PI;
    }
    return phi;
  }
}
