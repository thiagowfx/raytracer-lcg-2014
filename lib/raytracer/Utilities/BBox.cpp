#include "BBox.h"

namespace Raytracer {
  BBox::BBox (const double x0, const double x1,
              const double y0, const double y1,
              const double z0, const double z1) :
    x0(x0),
    x1(x1),
    y0(y0),
    y1(y1),
    z0(z0),
    z1(z1)
  {}


  BBox::BBox (const Vector3d p0, const Vector3d p1) :
    x0(p0(0)),
    x1(p1(0)),
    y0(p0(1)),
    y1(p1(1)),
    z0(p0(2)),
    z1(p1(2))
  {}


  BBox::BBox (const BBox& bbox) :
    x0(bbox.x0),
    x1(bbox.x1),
    y0(bbox.y0),
    y1(bbox.y1),
    z0(bbox.z0),
    z1(bbox.z1)
  {}


  BBox::~BBox () {}


  BBox* BBox::clone() const {
    return new BBox(*this);
  }


  bool BBox::hit(const Ray& ray) const {
    double ox = ray.origin(0);
    double oy = ray.origin(1);
    double oz = ray.origin(2);
    double dx = ray.direction(0);
    double dy = ray.direction(1);
    double dz = ray.direction(2);
    double tx_min, ty_min, tz_min;
    double tx_max, ty_max, tz_max;

    double a = 1.0 / dx;
    if (a >= 0) {
      tx_min = (x0 - ox) * a;
      tx_max = (x1 - ox) * a;
    }
    else {
      tx_min = (x1 - ox) * a;
      tx_max = (x0 - ox) * a;
    }

    double b = 1.0 / dy;
    if (b >= 0) {
      ty_min = (y0 - oy) * b;
      ty_max = (y1 - oy) * b;
    }
    else {
      ty_min = (y1 - oy) * b;
      ty_max = (y0 - oy) * b;
    }

    double c = 1.0 / dz;
    if (c >= 0) {
      tz_min = (z0 - oz) * c;
      tz_max = (z1 - oz) * c;
    }
    else {
      tz_min = (z1 - oz) * c;
      tz_max = (z0 - oz) * c;
    }

    double t0, t1;

    /* Find largest entering t value. */
    if (tx_min > ty_min)
      t0 = tx_min;
    else
      t0 = ty_min;

    if (tz_min > t0)
      t0 = tz_min;

    /* Find smallest exiting t value; */
    if (tx_max < ty_max)
      t1 = tx_max;
    else
      t1 = ty_max;

    if (tz_max < t1)
      t1 = tz_max;

    return (t0 < t1 && t1 > kEpsilon);
  }


  bool BBox::inside(const Vector3d& p) const {
    return (p(0) > x0 && p(0) < x1) && (p(1) > y0 && p(1) < y1) && (p(2) > z0 && p(2) < z1);
  };
}
