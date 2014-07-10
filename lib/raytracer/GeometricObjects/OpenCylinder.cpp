#include "OpenCylinder.h"

namespace Raytracer {
  OpenCylinder::OpenCylinder(const double ybottom, const double ytop, const double radius) :
    GeometricObject(),
    ybottom(ybottom),
    ytop(ytop),
    radius(radius)
  {}


  OpenCylinder::OpenCylinder(const OpenCylinder& c) :
    GeometricObject(c),
    ybottom(c.ybottom),
    ytop(c.ytop),
    radius(c.radius)
  {}


  OpenCylinder* OpenCylinder::clone() const {
    return new OpenCylinder (*this);
  }


  OpenCylinder::~OpenCylinder() {}


  bool OpenCylinder::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
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

    if (disc < 0.0)
      return false;
    else {
      double e = sqrt(disc);
      double denom = 2.0 * a;
      /* Smaller root. */
      t = (-b - e) / denom;

      if (t > kEpsilon) {
        double yhit = oy + t * dy;

        if (yhit > ybottom && yhit < ytop) {
          tmin = t;

          if (type == PRIMARY_RAY) {
            sr.normal = Vector3d((ox + t * dx) / radius, 0.0, (oz + t * dz) / radius);
            /* Test for hitting from inside. */
            if (-ray.direction.dot(sr.normal) < 0.0) {
              sr.normal = -sr.normal;
            }
            sr.local_hit_point = ray.origin + tmin * ray.direction;
          }
          return true;
        }
      }

      /* Larger root. */
      t = (-b + e) / denom;

      if (t > kEpsilon) {
        double yhit = oy + t * dy;

        if (yhit > ybottom && yhit < ytop) {
          tmin = t;

          if (type == PRIMARY_RAY) {
            sr.normal = Vector3d((ox + t * dx) / radius, 0.0, (oz + t * dz) / radius);
            /* Test for hitting inside surface. */
            if (-ray.direction.dot(sr.normal) < 0.0)
              sr.normal = -sr.normal;
            sr.local_hit_point = ray.origin + tmin * ray.direction;
          }
          return true;
        }
      }
    }

    return false;
  }
}
