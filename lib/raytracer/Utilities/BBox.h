#ifndef __BBOX__
#define __BBOX__

#include "Utilities.h"
#include "Ray.h"

class BBox {

 public:
  double x0, x1, y0, y1, z0, z1;
  BBox();
  BBox(const double x0, const double x1,
       const double y0, const double y1,
       const double z0, const double z1);
  BBox(const Vector3d p0, const Vector3d p1);
  BBox(const BBox& bbox);
  BBox& operator= (const BBox& rhs);
  ~BBox();
  bool hit(const Ray& ray) const;
  bool inside(const Vector3d& p) const; 
};

#endif
