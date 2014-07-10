#include "Box.h"

namespace Raytracer {
  Box::Box (const double x0, const double x1,
            const double y0, const double y1,
            const double z0, const double z1) :
    GeometricObject(),
    x0(x0),
    x1(x1),
    y0(y0),
    y1(y1),
    z0(z0),
    z1(z1)
  {}


  Box::Box (const Vector3d p0, const Vector3d p1) :
    GeometricObject(),
    x0(p0(0)),
    x1(p1(0)),
    y0(p0(1)),
    y1(p1(1)),
    z0(p0(2)),
    z1(p1(2))
  {}

  
  Box* Box::clone() const {
    return (new Box(*this));
  }


  Box::Box (const Box& r) :
    GeometricObject(r),
    x0(r.x0),
    y0(r.y0),
    z0(r.z0),
    x1(r.x1),
    y1(r.y1),
    z1(r.z1)
  {}


  Box::~Box () {}


  BBox Box::get_bounding_box() const {
    return BBox(x0,x1,y0,y1,z0,z1);
  }


  bool Box::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

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
    int face_in, face_out;

    // find largest entering t value
    if (tx_min > ty_min) {
      t0 = tx_min;
      face_in = (a >= 0.0) ? 0 : 3;
    }
    else {
      t0 = ty_min;
      face_in = (b >= 0.0) ? 1 : 4;
    }

    if (tz_min > t0) {
      t0 = tz_min;
      face_in = (c >= 0.0) ? 2 : 5;
    }

    // find smallest exiting t value
    if (tx_max < ty_max) {
      t1 = tx_max;
      face_out = (a >= 0.0) ? 3 : 0;
    }
    else {
      t1 = ty_max;
      face_out = (b >= 0.0) ? 4 : 1;
    }

    if (tz_max < t1) {
      t1 = tz_max;
      face_out = (c >= 0.0) ? 5 : 2;
    }

    if (t0 < t1 && t1 > kEpsilon) { // condition for a hit
      if (t0 > kEpsilon) {
        tmin = t0;              // ray hits outside surface

        if (type == PRIMARY_RAY) {
          sr.normal = get_normal(face_in);
        }
      }
      else {
        tmin = t1;              // ray hits inside surface

        if (type == PRIMARY_RAY) {
          sr.normal = get_normal(face_out);
        }
      }

      if (type == PRIMARY_RAY) {
        sr.local_hit_point = ray.origin + tmin * ray.direction;
      }
      return true;
    }
    else
      return false;
  }


  Vector3d Box::get_normal(const int face_hit) const {
    switch (face_hit) {
    case 0:
      return (Vector3d(-1, 0, 0)); // -x face
    case 1:
      return (Vector3d(0, -1, 0)); // -y face
    case 2:
      return (Vector3d(0, 0, -1)); // -z face
    case 3:
      return (Vector3d(1, 0, 0)); // +x face
    case 4:
      return (Vector3d(0, 1, 0)); // +y face
    case 5:
      return (Vector3d(0, 0, 1)); // +z face
    default:
      return Vector3d(0.0, 0.0, 0.0); // shouldn't happen
    }
  }
}
